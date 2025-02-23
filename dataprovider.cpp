#include "dataprovider.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QVector>

#define str(s) "'" + s + "'"
#define tostr(n) QString::number(n)
#define join + ", " +

DataProvider *DataProvider::Instance()
{
    static DataProvider *instance = nullptr;
    if (!instance) instance = new DataProvider();
    return instance;
}

DataProvider::~DataProvider()
{
    _db.close();
}

QVector<Driver> DataProvider::getDrivers(const QString &condition)
{
    const QString busyDriversQueryStr = "select distinct driver_id from orders where not finished and driver_id is not null";
    QSqlQuery busyDriversQuery(busyDriversQueryStr, _db);
    QSet<int> busyDriversIds;
    while (busyDriversQuery.next()) {
        busyDriversIds.insert(busyDriversQuery.value(0).toBool());
    }

    const QString queryStr = "select id, name, contract_date from drivers " + condition;
    QVector<Driver> vec;

    QSqlQuery query(queryStr, _db);
    while (query.next()) {
        Driver d = parseDriver(query);
        d.isFree = !busyDriversIds.contains(d.id);
        vec.append(d);
    }

    return vec;
}

QVector<Truck> DataProvider::getTrucks(const QString &condition)
{
    const QString queryStr = "select id, model, number, last_mileage, last_maintanance_date from drivers " + condition;
    QVector<Truck> vec;

    QSqlQuery query(queryStr, _db);
    while (query.next()) {
        vec.append(parseTruck(query));
    }

    return vec;
}

QVector<Client> DataProvider::getClients(const QString &condition)
{
    const QString queryStr = "select id, name, address from clients " + condition;
    QVector<Client> vec;

    QSqlQuery query(queryStr, _db);
    while (query.next()) {
        vec.append(parseClient(query));
    }

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

    QSqlQuery query(queryStr, _db);
    while (query.next()) {
        vec.append(parseRefueling(query));
    }

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

    QSqlQuery query(queryStr, _db);
    while (query.next()) {
        vec.append(parseOrder(query));
    }

    return vec;
}

DriversList* DataProvider::getDriversList()
{
    return &_drivers;
}

TrucksList* DataProvider::getTrucksList()
{
    return &_trucks;
}

ClientsList* DataProvider::getClientsList()
{
    return &_clients;
}

RefuelingsList* DataProvider::getRefuelingsList()
{
    return &_refuelings;
}

OrdersList* DataProvider::getOrdersList()
{
    return &_orders;
}

void DataProvider::addOrder(int fromId, int toId, double distance, QString description, double value)
{
    const QString queryStr =
        QString("insert into orders (from_id, to_id, distance, description, declared_value, created_at) values (") +
        tostr(fromId) join tostr(toId) join
        tostr(distance) join str(description) join tostr(value) join
        str(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")) + ")";

    QSqlQuery(queryStr, _db);
    update();
}

void DataProvider::cancelOrder(int orderId)
{
    const QString queryStr = QString("delete from orders where id = ") + QString::number(orderId);
    QSqlQuery(queryStr, _db);
    update();
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
    _db.open();

    update();

    connect(&_updateTimer, &QTimer::timeout, this, &DataProvider::update);
    _updateTimer.setInterval(kUpdateInterval);
    _updateTimer.setSingleShot(false);
    _updateTimer.start();
}

void DataProvider::update()
{
    _drivers.syncData(getDrivers());
    _trucks.syncData(getTrucks());
    _clients.syncData(getClients());
    _refuelings.syncData(getRefuelings());
    _orders.syncData(getOrders());
}

QString DataProvider::convertDate(const QDateTime &date) const
{
    if (!date.isValid() || date.isNull()) return "-";
    return date.toString("dd.MM.yyyy hh:mm:ss");
}

Driver DataProvider::parseDriver(const QSqlQuery &query) const
{
    Driver d;

    d.id = query.value(0).toInt();
    d.name = query.value(1).toString();
    d.contractDate = query.value(2).toDateTime();

    return d;
}

Truck DataProvider::parseTruck(const QSqlQuery &query) const
{
    Truck t;

    t.id = query.value(0).toInt();
    t.model = query.value(1).toString();
    t.number = query.value(2).toString();
    t.lastMileage = query.value(3).toFloat();
    t.lastMaintananceDate = query.value(4).toDateTime();

    return t;
}

Client DataProvider::parseClient(const QSqlQuery &query) const
{
    Client c;

    c.id = query.value(0).toInt();
    c.name = query.value(1).toString();
    c.address = query.value(2).toString();

    return c;
}

Refueling DataProvider::parseRefueling(const QSqlQuery &query) const
{
    Refueling r;

    r.id = query.value(0).toInt();
    r.driverName = query.value(1).toString();
    r.driverContractDate = query.value(2).toDateTime();
    r.date = query.value(3).toDateTime();
    r.cost = query.value(4).toFloat();

    return r;
}

Order DataProvider::parseOrder(const QSqlQuery &query) const
{
    Order o;

    o.id = query.value(0).toInt();
    // driver
    o.driverName = query.value(1).toString();
    o.driverContractDate = query.value(2).toDateTime();
    // truck
    o.truckModel = query.value(3).toString();
    o.truckNumber = query.value(4).toString();
    o.truckLastMilage = query.value(5).toFloat();
    o.truckLastMaintananceDate = query.value(6).toDateTime();
    // from
    o.fromName = query.value(7).toString();
    o.fromAddress = query.value(8).toString();
    // to
    o.toName = query.value(9).toString();
    o.toAddress = query.value(10).toString();
    // order
    o.createdAt = query.value(11).toDateTime();
    o.createdAtString = convertDate(o.createdAt);
    o.sentAt = query.value(12).toDateTime();
    o.sentAtString = convertDate(o.sentAt);
    o.receivedAt = query.value(13).toDateTime();
    o.receivedAtString = convertDate(o.receivedAt);
    o.finished = query.value(14).toBool();
    o.distance = query.value(15).toFloat();
    o.description = query.value(16).toString();

    QString valueStr = query.value(17).toString();
    valueStr.remove(QRegExp("[^0-9,]"));
    valueStr.replace(',', '.');
    o.value = valueStr.toDouble();

    return o;
}

#undef str
#undef tostr
#undef join
