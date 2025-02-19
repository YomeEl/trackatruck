#include "orderslist.h"

#include <QSet>

OrdersList::OrdersList(QObject *parent) : AbstractDatabaseList(parent) {}

QVariant OrdersList::data(const QModelIndex &index, int role) const
{
    const Order &item = _data[index.row()];

	switch (role) {
    case roles::IdRole:
        return QVariant::fromValue(item.id);
	case roles::DriverNameRole:
        return QVariant::fromValue(item.driverName);
	case roles::DriverContractDateRole:
        return QVariant::fromValue(item.driverContractDate);
	case roles::TruckModelRole:
        return QVariant::fromValue(item.truckModel);
	case roles::TruckNumberRole:
        return QVariant::fromValue(item.truckNumber);
	case roles::TruckLastMilageRole:
        return QVariant::fromValue(item.truckLastMilage);
	case roles::TruckLastMaintananceDateRole:
        return QVariant::fromValue(item.truckLastMaintananceDate);
	case roles::FromNameRole:
        return QVariant::fromValue(item.fromName);
	case roles::FromAddressRole:
        return QVariant::fromValue(item.fromAddress);
	case roles::ToNameRole:
        return QVariant::fromValue(item.toName);
	case roles::ToAddressRole:
        return QVariant::fromValue(item.toAddress);
	case roles::CreatedAtRole:
        return QVariant::fromValue(item.createdAt);
    case roles::CreatedAtStringRole:
        return QVariant::fromValue(item.createdAtString);
	case roles::SentAtRole:
        return QVariant::fromValue(item.sentAt);
    case roles::SentAtStringRole:
        return QVariant::fromValue(item.sentAtString);
	case roles::ReceivedAtRole:
        return QVariant::fromValue(item.receivedAt);
    case roles::ReceivedAtStringRole:
        return QVariant::fromValue(item.receivedAtString);
	case roles::FinishedRole:
        return QVariant::fromValue(item.finished);
	case roles::DistanceRole:
        return QVariant::fromValue(item.distance);
	case roles::DescriptionRole:
        return QVariant::fromValue(item.description);
	case roles::ValueRole:
        return QVariant::fromValue(item.value);
    default:
        return QVariant();
	}
}

QHash<int, QByteArray> OrdersList::roleNames() const
{
	QHash<int, QByteArray> names;

    names[roles::IdRole] = "id";
	names[roles::DriverNameRole] = "driverName";
	names[roles::DriverContractDateRole] = "driverContractDate";
	names[roles::TruckModelRole] = "truckModel";
	names[roles::TruckNumberRole] = "truckNumber";
	names[roles::TruckLastMilageRole] = "truckLastMilage";
	names[roles::TruckLastMaintananceDateRole] = "truckLastMaintananceDate";
	names[roles::FromNameRole] = "fromName";
	names[roles::FromAddressRole] = "fromAddress";
	names[roles::ToNameRole] = "toName";
	names[roles::ToAddressRole] = "toAddress";
	names[roles::CreatedAtRole] = "createdAt";
    names[roles::CreatedAtStringRole] = "createdAtString";
	names[roles::SentAtRole] = "sentAt";
    names[roles::SentAtStringRole] = "sentAtString";
	names[roles::ReceivedAtRole] = "receivedAt";
    names[roles::ReceivedAtStringRole] = "receivedAtString";
	names[roles::FinishedRole] = "finished";
	names[roles::DistanceRole] = "distance";
	names[roles::DescriptionRole] = "description";
	names[roles::ValueRole] = "value";

	return names;
}
