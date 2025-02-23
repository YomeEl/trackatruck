#ifndef TYPES_H
#define TYPES_H

#include <QObject>
#include <QString>
#include <QDateTime>

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
    QString model;
    QString number;
    float lastMileage;
    QDateTime lastMaintananceDate;

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
    float cost;

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

#endif // TYPES_H
