#include "dataprovider.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

DataProvider *DataProvider::Instance()
{
    static DataProvider *instance = nullptr;
    if (!instance) instance = new DataProvider();
    return instance;
}

QVector<Driver> DataProvider::getDrivers(const QString &condition)
{
    const QString queryStr = "select name, contract_date from drivers " + condition;
    QVector<Driver> vec;

    _db.open();
    QSqlQuery query(queryStr);
    while (query.next()) {
        QString name = query.value(0).toString();
        QDateTime contractDate = query.value(1).toDateTime();
        vec.append({ name, contractDate });
    }
    _db.close();

    return vec;
}

QVector<Truck> DataProvider::getTrucks(const QString &condition)
{
    const QString queryStr = "select model, number, last_mileage, last_maintanance_date from drivers " + condition;
    QVector<Truck> vec;

    _db.open();
    QSqlQuery query(queryStr);
    while (query.next()) {
        QString model = query.value(0).toString();
        QString number = query.value(1).toString();
        float lastMileage = query.value(2).toFloat();
        QDateTime lastMaintananceDate = query.value(3).toDateTime();
        vec.append({ model, number, lastMileage, lastMaintananceDate });
    }
    _db.close();

    return vec;
}

QVector<Client> DataProvider::getClients(const QString &condition)
{
    const QString queryStr = "select name, address from clients " + condition;
    QVector<Client> vec;

    _db.open();
    QSqlQuery query(queryStr);
    while (query.next()) {
        QString name = query.value(0).toString();
        QString address = query.value(1).toString();
        vec.append({ name, address });
    }
    _db.close();

    return vec;
}

QVector<Refueling> DataProvider::getRefuelings(const QString &condition)
{
    const QString queryStr = "select name, contract_date, date, cost from refuelings join drivers on driver_id = drivers.id " + condition;
    QVector<Refueling> vec;

    _db.open();
    QSqlQuery query(queryStr);
    while (query.next()) {
        QString driverName = query.value(0).toString();
        QDateTime driverContractDate = query.value(1).toDateTime();
        QDateTime date = query.value(2).toDateTime();
        float cost = query.value(3).toFloat();
        vec.append({ driverName, driverContractDate, date, cost });
    }
    _db.close();

    return vec;
}

QVector<Order> DataProvider::getOrders(const QString &condition)
{
    const QString queryStr =
        QString("select  ") +
        QString("	drivers.name, drivers.contract_date,  ") +
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
    QSqlQuery query(queryStr);
    while (query.next()) {
        // driver
        QString driverName = query.value(0).toString();
        QDateTime driverContractDate = query.value(1).toDateTime();
        // truck
        QString truckModel = query.value(2).toString();
        QString truckNumber = query.value(3).toString();
        float truckLastMileage = query.value(4).toFloat();
        QDateTime truckLastMaintananceDate = query.value(5).toDateTime();
        // from
        QString fromName = query.value(6).toString();
        QString fromAddress = query.value(7).toString();
        // to
        QString toName = query.value(8).toString();
        QString toAddress = query.value(9).toString();
        // order
        QDateTime createdAt = query.value(10).toDateTime();
        QDateTime sentAt = query.value(11).toDateTime();
        QDateTime receivedAt = query.value(12).toDateTime();
        bool finished = query.value(13).toBool();
        float distance = query.value(14).toFloat();
        QString description = query.value(15).toString();
        float value = query.value(16).toFloat();

        vec.append({
            driverName, driverContractDate,
            truckModel, truckNumber, truckLastMileage, truckLastMaintananceDate,
            fromName, fromAddress,
            toName, toAddress,
            createdAt, sentAt, receivedAt, finished, distance, description, value
        });
    }
    _db.close();

    return vec;
}

OrdersList *DataProvider::getOrdersList()
{
    OrdersList *list = new OrdersList(getOrders());
    return list;
}

DataProvider::DataProvider()
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
}
