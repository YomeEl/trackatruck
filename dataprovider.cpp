#include "dataprovider.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QVector>

DataProvider *DataProvider::Instance()
{
    static DataProvider *instance = nullptr;
    if (!instance) instance = new DataProvider();
    return instance;
}

QVector<Driver> DataProvider::getDrivers(const QString &condition)
{
    const QString queryStr = "select id, name, contract_date from drivers " + condition;
    QVector<Driver> vec;

    _db.open();
    QSqlQuery query(queryStr, _db);
    while (query.next()) {
        vec.append(parseDriver(query));
    }
    _db.close();

    return vec;
}

QVector<Truck> DataProvider::getTrucks(const QString &condition)
{
    const QString queryStr = "select id, model, number, last_mileage, last_maintanance_date from drivers " + condition;
    QVector<Truck> vec;

    _db.open();
    QSqlQuery query(queryStr, _db);
    while (query.next()) {
        vec.append(parseTruck(query));
    }
    _db.close();

    return vec;
}

QVector<Client> DataProvider::getClients(const QString &condition)
{
    const QString queryStr = "select id, name, address from clients " + condition;
    QVector<Client> vec;

    _db.open();
    QSqlQuery query(queryStr, _db);
    while (query.next()) {
        vec.append(parseClient(query));
    }
    _db.close();

    return vec;
}

QVector<Refueling> DataProvider::getRefuelings(const QString &condition)
{
    const QString queryStr =
        QString("select ") +
        QString("   refuelings.id, name, contract_date, date, cost ") +
        QString("from refuelings ") +
        QString("join drivers on driver_id = drivers.id ") +
        condition;
    QVector<Refueling> vec;

    _db.open();
    QSqlQuery query(queryStr, _db);
    while (query.next()) {
        vec.append(parseRefueling(query));
    }
    _db.close();

    return vec;
}

QVector<Order> DataProvider::getOrders(const QString &condition)
{
    const QString queryStr =
        QString("select  ") +
        QString("	orders.id, drivers.name, drivers.contract_date, ") +
        QString("	trucks.model, trucks.number, trucks.last_milage, trucks.last_maintanance_date, ") +
        QString("	src.name, src.address,  ") +
        QString("	dst.name, dst.address, ") +
        QString("	created_at, sent_at, received_at, finished, distance, description, declared_value ") +
        QString("from orders ") +
        QString("left join drivers on orders.driver_id = drivers.id ") +
        QString("left join trucks on orders.truck_id = trucks.id ") +
        QString("left join clients as src on orders.from_id = src.id ") +
        QString("left join clients as dst on orders.to_id = dst.id ") +
        condition;
    QVector<Order> vec;

    _db.open();
    QSqlQuery query(queryStr, _db);
    while (query.next()) {
        vec.append(parseOrder(query));
    }
    _db.close();

    return vec;
}

DriversList *DataProvider::getDriversList()
{
    return &_drivers;
}

TrucksList *DataProvider::getTrucksList()
{
    return &_trucks;
}

ClientsList *DataProvider::getClientsList()
{
    return &_clients;
}

RefuelingsList *DataProvider::getRefuelingsList()
{
    return &_refuelings;
}

OrdersList* DataProvider::getOrdersList()
{
    return &_orders;
}

DataProvider::DataProvider() :
    _drivers(this), _trucks(this), _clients(this), _refuelings(this), _orders(this)
{
    QString username = "";
    QString password = "";

    QJsonDocument doc;
    QFile credFile("creds.json");
    bool isOpen = credFile.open(QIODevice::ReadOnly);
    if (isOpen)
    {
        QByteArray bytes = credFile.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(bytes);
        QJsonObject obj = doc.object();

        credFile.close();

        username = obj.value("username").toString();
        password = obj.value("password").toString();
    }
    else
    {
        QJsonObject obj;
        obj.insert("username", "");
        obj.insert("password", "");

        credFile.open(QIODevice::WriteOnly);
        doc.setObject(obj);
        credFile.write(doc.toJson());
        credFile.close();
    }

    _db = QSqlDatabase::addDatabase("QPSQL");
    _db.setHostName("localhost");
    _db.setDatabaseName("trackatruck");
    _db.setUserName(username);
    _db.setPassword(password);

    update();

    connect(&_updateTimer, &QTimer::timeout, this, &DataProvider::update);
    _updateTimer.setInterval(kUpdateInterval);
    _updateTimer.setSingleShot(false);
    _updateTimer.start();
}

void DataProvider::update()
{
    _drivers.clear();
    _trucks.clear();
    _clients.clear();
    _refuelings.clear();
    _orders.clear();

    _drivers.append(getDrivers());
    _trucks.append(getTrucks());
    _clients.append(getClients());
    _refuelings.append(getRefuelings());
    _orders.append(getOrders());
}

QString DataProvider::convertDate(const QDateTime &date) const
{
    if (!date.isValid() || date.isNull()) return "-";
    return date.toString("dd.MM.yyyy hh:mm:ss");
}

Driver DataProvider::parseDriver(const QSqlQuery &query) const
{
    int id = query.value(0).toInt();
    QString name = query.value(0).toString();
    QDateTime contractDate = query.value(1).toDateTime();
    return { id, name, contractDate };
}

Truck DataProvider::parseTruck(const QSqlQuery &query) const
{
    int id = query.value(0).toInt();
    QString model = query.value(1).toString();
    QString number = query.value(2).toString();
    float lastMileage = query.value(3).toFloat();
    QDateTime lastMaintananceDate = query.value(4).toDateTime();
    return { id, model, number, lastMileage, lastMaintananceDate };
}

Client DataProvider::parseClient(const QSqlQuery &query) const
{
    int id = query.value(0).toInt();
    QString name = query.value(1).toString();
    QString address = query.value(2).toString();
    return { id, name, address };
}

Refueling DataProvider::parseRefueling(const QSqlQuery &query) const
{
    int id = query.value(0).toInt();
    QString driverName = query.value(1).toString();
    QDateTime driverContractDate = query.value(2).toDateTime();
    QDateTime date = query.value(3).toDateTime();
    float cost = query.value(4).toFloat();
    return { id, driverName, driverContractDate, date, cost };
}

Order DataProvider::parseOrder(const QSqlQuery &query) const
{
    int id = query.value(0).toInt();
    // driver
    QString driverName = query.value(1).toString();
    QDateTime driverContractDate = query.value(2).toDateTime();
    // truck
    QString truckModel = query.value(3).toString();
    QString truckNumber = query.value(4).toString();
    float truckLastMileage = query.value(5).toFloat();
    QDateTime truckLastMaintananceDate = query.value(6).toDateTime();
    // from
    QString fromName = query.value(7).toString();
    QString fromAddress = query.value(8).toString();
    // to
    QString toName = query.value(9).toString();
    QString toAddress = query.value(10).toString();
    // order
    QDateTime createdAt = query.value(11).toDateTime();
    QString createdAtString = convertDate(createdAt);
    QDateTime sentAt = query.value(12).toDateTime();
    QString sentAtString = convertDate(sentAt);
    QDateTime receivedAt = query.value(13).toDateTime();
    QString receivedAtString = convertDate(receivedAt);
    bool finished = query.value(14).toBool();
    float distance = query.value(15).toFloat();
    QString description = query.value(16).toString();

    QString valueStr = query.value(17).toString();
    valueStr.remove(QRegExp("[^0-9,]"));
    valueStr.replace(',', '.');
    double value = valueStr.toDouble();

    return {
        id,
        driverName, driverContractDate,
        truckModel, truckNumber, truckLastMileage, truckLastMaintananceDate,
        fromName, fromAddress,
        toName, toAddress,
        createdAt, createdAtString,
        sentAt, sentAtString,
        receivedAt, receivedAtString,
        finished, distance, description, value
    };
}
