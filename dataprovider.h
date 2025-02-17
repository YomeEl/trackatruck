#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <QObject>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QTimer>

#include "types.h"
#include "lists/orderslist.h"
#include "lists/clientslist.h"
#include "lists/driverslist.h"
#include "lists/refuelingslist.h"
#include "lists/truckslist.h"

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

    Q_INVOKABLE DriversList* getDriversList();
    Q_INVOKABLE TrucksList* getTrucksList();
    Q_INVOKABLE ClientsList* getClientsList();
    Q_INVOKABLE RefuelingsList* getRefuelingsList();
    Q_INVOKABLE OrdersList* getOrdersList();

    Q_INVOKABLE void addDriver(Driver driver) {}
    Q_INVOKABLE void updateDriver(Driver driver) {}

    Q_INVOKABLE void addTruck(Truck truck) {}
    Q_INVOKABLE void updateTruck(Truck truck) {}

    Q_INVOKABLE void addClient(Client client) {}
    Q_INVOKABLE void updateClient(Client client) {}

    Q_INVOKABLE void addRefueling(Refueling refueling) {}

    Q_INVOKABLE void addOrder(Order order) {}
    Q_INVOKABLE void assignTruckAndDriver(int orderId, int driverId, int truckId, QDateTime finishedAt) {}
    Q_INVOKABLE void markAsFinished(int orderId) {}
    Q_INVOKABLE void cancelOrder(int orderId) {}

private:
    DataProvider();

    QString convertDate(const QDateTime &date) const;

    Driver parseDriver(const QSqlQuery &query) const;
    Truck parseTruck(const QSqlQuery &query) const;
    Client parseClient(const QSqlQuery &query) const;
    Refueling parseRefueling(const QSqlQuery &query) const;
    Order parseOrder(const QSqlQuery &query) const;

private slots:
    void update();

private:
    QSqlDatabase _db;

    DriversList _drivers;
    TrucksList _trucks;
    ClientsList _clients;
    RefuelingsList _refuelings;
    OrdersList _orders;

    const size_t kUpdateInterval = 1000;
    QTimer _updateTimer;
};

#endif // DATAPROVIDER_H
