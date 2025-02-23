#include "dataprovider.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QVector>

#define str(s) "'" + s + "'"
#define toStr(n) QString::number(n)

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

void DataProvider::addDriver(QString name)
{
    const QMap<QString, QString> valueMap = {
        { "name", str(name) },
        { "contract_date", str(getCurrentDateString()) }
    };
    const QString queryStr = createInsertQuery("drivers", valueMap);

    QSqlQuery(queryStr, _db);
    update();
}

void DataProvider::updateDriverName(int id, QString name)
{
    const QString queryStr = createUpdateQuery("drivers", {{ "name", str(name) }}, "id = " + toStr(id));
    QSqlQuery(queryStr, _db);
    update();
}

void DataProvider::addTruck(QString model, QString number, float lastMilage, QDateTime lastMaintananceDate)
{
    const QMap<QString, QString> valueMap = {
        { "model", str(model) },
        { "number", str(number) },
        { "last_milage", toStr(lastMilage) },
        { "last_maintanance_date", str(convertDate(lastMaintananceDate)) }
    };
    const QString queryStr = createInsertQuery("trucks", valueMap);

    qDebug() << queryStr;

    QSqlQuery(queryStr, _db);
    update();
}

void DataProvider::updateTruckNumber(int id, QString number)
{
    const QString queryStr = createUpdateQuery("trucks", {{ "number", str(number) }}, "id = " + toStr(id));
    QSqlQuery(queryStr, _db);
    update();
}

void DataProvider::markMaintanance(int id)
{
    const QString newMilageQueryStr =
        QString("select sum(distance) from orders join trucks on truck_id = trucks.id") +
        "where truck_id = " + toStr(id) + " and trucks.last_maintanance_date <= sent_at";
    QSqlQuery newMilageQuery(newMilageQueryStr, _db);
    newMilageQuery.next();
    double newMilage = newMilageQuery.value(0).toDouble();

    const QMap<QString, QString> valueMap = {
        { "last_milage", "last_milage + " + toStr(newMilage) },
        { "last_maintanance_date", str(getCurrentDateString()) }
    };
    const QString updateQueryStr = createUpdateQuery("trucks", valueMap, "id = " + toStr(id));
    QSqlQuery(updateQueryStr, _db);
    update();
}

void DataProvider::addClient(QString name, QString address)
{
    const QMap<QString, QString> valueMap = {
        { "name", str(name) },
        { "address", str(address) },
    };
    const QString queryStr = createInsertQuery("clients", valueMap);

    QSqlQuery(queryStr, _db);
    update();
}

void DataProvider::updateClient(int id, QString name, QString address)
{
    const QMap<QString, QString> valueMap = {
        { "name", str(name) },
        { "address", str(address) }
    };
    const QString updateQueryStr = createUpdateQuery("clients", valueMap, "id = " + toStr(id));
    QSqlQuery(updateQueryStr, _db);
    update();
}

void DataProvider::addRefueling(int driverId, double cost)
{
    const QMap<QString, QString> valueMap = {
        { "driverId", toStr(driverId) },
        { "cost", toStr(cost) },
    };
    const QString queryStr = createInsertQuery("refuelings", valueMap);

    QSqlQuery(queryStr, _db);
    update();
}

void DataProvider::addOrder(int fromId, int toId, double distance, QString description, double value)
{
    QMap<QString, QString> valueMap = {
        { "from_id", toStr(fromId) },
        { "to_id", toStr(toId) },
        { "distance", toStr(distance) },
        { "description", str(description) },
        { "declared_value", toStr(value) },
        { "created_at", str(getCurrentDateString()) }
    };

    const QString queryStr = createInsertQuery("orders", valueMap);
    qDebug() << queryStr;

    QSqlQuery(queryStr, _db);
    update();
}

void DataProvider::assignTruckAndDriver(int orderId, int driverId, int truckId, QDateTime receivedAt)
{
    QMap<QString, QString> valueMap = {
        { "driver_id", toStr(driverId) },
        { "truck_id", toStr(truckId) },
        { "received_at", str(convertDate(receivedAt)) }
    };

    const QString updateQueryStr = createUpdateQuery("orders", valueMap, "id = " + toStr(orderId));
    QSqlQuery(updateQueryStr, _db);
    update();
}

void DataProvider::markAsFinished(int orderId)
{
    QMap<QString, QString> valueMap = {
        { "finished", "true" },
        { "received_at", getCurrentDateString() }
    };

    const QString updateQueryStr = createUpdateQuery("orders", valueMap, "id = " + toStr(orderId));
    QSqlQuery(updateQueryStr, _db);
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

QString DataProvider::createInsertQuery(const QString &table, const QMap<QString, QString> &values)
{
    QString columnsStr = "";
    QString valuesStr = "";
    for (auto it = values.keyValueBegin(); it != values.keyValueEnd(); it++)
    {
        columnsStr += it->first + ", ";
        valuesStr += it->second + ", ";
    }
    columnsStr.remove(columnsStr.length() - 2, 2);
    valuesStr.remove(valuesStr.length() - 2, 2);

    QString query = QString("insert into ") + table + " (" + columnsStr + ") values (" + valuesStr + ")";
    return query;
}

QString DataProvider::createUpdateQuery(const QString &table, const QMap<QString, QString> &values, const QString &condition)
{
    QString statements = "";
    for (auto it = values.keyValueBegin(); it != values.keyValueEnd(); it++)
    {
        statements += it->first + " = " + it->second + ", ";
    }
    statements.remove(statements.length() - 2, 2);

    QString query = QString("update ") + table + " set " + statements + " where " + condition;
    return query;
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
    r.cost = query.value(4).toDouble();

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

QString DataProvider::getCurrentDateString() const
{
    return convertDate(QDateTime::currentDateTime());
}

#undef str
#undef toStr
