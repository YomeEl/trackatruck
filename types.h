#ifndef TYPES_H
#define TYPES_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QVariantMap>

class HasId
{
public:
    virtual int getId() const = 0;
};

struct Truck : public HasId
{
    Q_GADGET
public:
    int id;
    QString truckModel;
    QString number;
    float lastMilage;
    QDateTime lastMaintananceDate;
    bool isFree;

    int getId() const override { return id; }
};
Q_DECLARE_METATYPE(Truck)

struct Driver : public HasId
{
    Q_GADGET
public:
    int id;
    QString name;
    QDateTime contractDate;
    bool isFree;

    int getId() const override { return id; }
};
Q_DECLARE_METATYPE(Driver)

struct Client : public HasId
{
    Q_GADGET
public:
    int id;
    QString name;
    QString address;

    int getId() const override { return id; }
};
Q_DECLARE_METATYPE(Client)

struct Refueling : public HasId
{
    Q_GADGET
public:
    int id;
    QString driverName;
    QDateTime driverContractDate;
    QDateTime date;
    double cost;

    int getId() const override { return id; }
};
Q_DECLARE_METATYPE(Refueling)

struct Order : public HasId
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

    int getId() const override { return id; }
};
Q_DECLARE_METATYPE(Order)

struct DriverReportRow
{
    QString name;
    size_t ordersFinished;
    double hoursEnroute;
    double distanceTraveled;

    QVariantMap toMap() {
        QVariantMap map;
        map["name"] = name;
        map["ordersFinished"] = ordersFinished;
        map["hoursEnroute"] = hoursEnroute;
        map["distanceTraveled"] = distanceTraveled;
        return map;
    }
};

struct RefuelingReportRow
{
    QString driverName;
    double sum;

    QVariantMap toMap() {
        QVariantMap map;
        map["driverName"] = driverName;
        map["sum"] = sum;
        return map;
    }
};

#endif // TYPES_H
