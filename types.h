#ifndef TYPES_H
#define TYPES_H

#include <QObject>
#include <QString>
#include <QDateTime>

struct Truck
{
    Q_GADGET
public:
    int id;
    QString model;
    QString number;
    float lastMileage;
    QDateTime lastMaintananceDate;
};
Q_DECLARE_METATYPE(Truck)

struct Driver
{
    Q_GADGET
public:
    int id;
    QString name;
    QDateTime contractDate;
};
Q_DECLARE_METATYPE(Driver)

struct Client
{
    Q_GADGET
public:
    int id;
    QString name;
    QString address;
};
Q_DECLARE_METATYPE(Client)

struct Refueling
{
    Q_GADGET
public:
    int id;
    QString driverName;
    QDateTime driverContractDate;
    QDateTime date;
    float cost;
};
Q_DECLARE_METATYPE(Refueling)

struct Order
{
    Q_GADGET
public:
    int id;
    QString driverName;
    QDateTime driverContractDate;

    QString truckModel;
    QString truckNumber;
    float truckLastMilage;
    QDateTime truckLastMaintananceDate;

    QString fromName;
    QString fromAddress;
    QString toName;
    QString toAddress;

    QDateTime createdAt;
    QString createdAtString;
    QDateTime sentAt;
    QString sentAtString;
    QDateTime receivedAt;
    QString receivedAtString;
    bool finished;
    float distance;
    QString description;
    double value;
};
Q_DECLARE_METATYPE(Order)

#endif // TYPES_H
