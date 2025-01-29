#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <QObject>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>

#include "types.h"
#include "lists/orderslist.h"

class DataProvider : public QObject
{
    Q_OBJECT
public:
    static DataProvider* Instance();

    QVector<Driver> getDrivers(const QString& condition = "");
    QVector<Truck> getTrucks(const QString& condition = "");
    QVector<Client> getClients(const QString& condition = "");
    QVector<Refueling> getRefuelings(const QString& condition = "");
    QVector<Order> getOrders(const QString& condition = "");

    Q_INVOKABLE OrdersList* getOrdersList();

private:
    DataProvider();

private:
    QSqlDatabase _db;
};

#endif // DATAPROVIDER_H
