#ifndef ORDERSLIST_H
#define ORDERSLIST_H

#include <QVector>

#include "abstractdatabaselist.h"
#include "abstractdatabaselist.cpp"
#include "..\types.h"

class OrdersList : public AbstractDatabaseList<Order>
{
    Q_OBJECT
public:
    OrdersList(QObject *parent = nullptr);

public:
	enum roles
	{
        IdRole = Qt::UserRole + 1,
        DriverNameRole,
		DriverContractDateRole,
		TruckModelRole,
		TruckNumberRole,
		TruckLastMilageRole,
		TruckLastMaintananceDateRole,
		FromNameRole,
		FromAddressRole,
		ToNameRole,
		ToAddressRole,
		CreatedAtRole,
        CreatedAtStringRole,
		SentAtRole,
        SentAtStringRole,
		ReceivedAtRole,
        ReceivedAtStringRole,
		FinishedRole,
		DistanceRole,
		DescriptionRole,
		ValueRole
	};

	QVariant data(const QModelIndex &index, int role) const;
	QHash<int, QByteArray> roleNames() const;
};

#endif // ORDERSLIST_H
