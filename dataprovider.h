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
    virtual ~DataProvider();

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

    Q_INVOKABLE void addDriver(QString name);
    Q_INVOKABLE void updateDriverName(int id, QString name);

    Q_INVOKABLE void addTruck(QString model, QString number, float lastMilage, QDateTime lastMaintananceDate);
    Q_INVOKABLE void updateTruckNumber(int id, QString number);
    Q_INVOKABLE void markMaintanance(int id);

    Q_INVOKABLE int addClient(QString name, QString address, bool returnId = false);
    Q_INVOKABLE void updateClient(int id, QString name, QString address);

    Q_INVOKABLE void addRefueling(int driverId, double cost, QDateTime date);

    Q_INVOKABLE void addOrder(int fromId, int toId, double distance, QString description, double value);
    Q_INVOKABLE void assignTruckAndDriver(int orderId, int driverId, int truckId, QDateTime sentAt, QDateTime receivedAt);
    Q_INVOKABLE void markAsFinished(int orderId);
    Q_INVOKABLE void cancelOrder(int orderId);

    Q_INVOKABLE QVariantList getDriverReportData(QDateTime begin, QDateTime end);
    Q_INVOKABLE QVariantList getRefuelingsReportData(QDateTime begin, QDateTime end);

private:
    DataProvider();

    QString convertDate(const QDateTime &date) const;

    Driver parseDriver(const QSqlQuery &query) const;
    Truck parseTruck(const QSqlQuery &query) const;
    Client parseClient(const QSqlQuery &query) const;
    Refueling parseRefueling(const QSqlQuery &query) const;
    Order parseOrder(const QSqlQuery &query) const;

    QString getCurrentDateString() const;

    QString createInsertQuery(const QString &table, const QMap<QString, QString> &values);
    QString createUpdateQuery(const QString &table, const QMap<QString, QString> &values, const QString &condition);

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
