#include "orderslist.h"

OrdersList::OrdersList(const QVector<Order>& list)
{
    append(list);
}

void OrdersList::append(const Order& item, bool supressUpdate)
{
	_orders.append(item);

    if (supressUpdate) return;

    auto idx = createIndex(_orders.count() - 1, 0);
    emit dataChanged(idx, idx);
}

void OrdersList::append(const QVector<Order> &list)
{
    auto startIndex = createIndex(_orders.count(), 0);
    for (auto &item : list) append(item, true);
    auto endIndex = createIndex(_orders.count(), 0);
    emit dataChanged(startIndex, endIndex);
}

void OrdersList::clear()
{
    _orders.clear();
}

QVariant OrdersList::data(const QModelIndex &index, int role) const
{
	switch (role) {
    case roles::IdRole:
        return QVariant::fromValue(_orders[index.row()].id);
	case roles::DriverNameRole:
		return QVariant::fromValue(_orders[index.row()].driverName);
	case roles::DriverContractDateRole:
		return QVariant::fromValue(_orders[index.row()].driverContractDate);
	case roles::TruckModelRole:
		return QVariant::fromValue(_orders[index.row()].truckModel);
	case roles::TruckNumberRole:
		return QVariant::fromValue(_orders[index.row()].truckNumber);
	case roles::TruckLastMilageRole:
		return QVariant::fromValue(_orders[index.row()].truckLastMilage);
	case roles::TruckLastMaintananceDateRole:
		return QVariant::fromValue(_orders[index.row()].truckLastMaintananceDate);
	case roles::FromNameRole:
		return QVariant::fromValue(_orders[index.row()].fromName);
	case roles::FromAddressRole:
		return QVariant::fromValue(_orders[index.row()].fromAddress);
	case roles::ToNameRole:
		return QVariant::fromValue(_orders[index.row()].toName);
	case roles::ToAddressRole:
		return QVariant::fromValue(_orders[index.row()].toAddress);
	case roles::CreatedAtRole:
		return QVariant::fromValue(_orders[index.row()].createdAt);
    case roles::CreatedAtStringRole:
        return QVariant::fromValue(_orders[index.row()].createdAtString);
	case roles::SentAtRole:
		return QVariant::fromValue(_orders[index.row()].sentAt);
    case roles::SentAtStringRole:
        return QVariant::fromValue(_orders[index.row()].sentAtString);
	case roles::ReceivedAtRole:
		return QVariant::fromValue(_orders[index.row()].receivedAt);
    case roles::ReceivedAtStringRole:
        return QVariant::fromValue(_orders[index.row()].receivedAtString);
	case roles::FinishedRole:
		return QVariant::fromValue(_orders[index.row()].finished);
	case roles::DistanceRole:
		return QVariant::fromValue(_orders[index.row()].distance);
	case roles::DescriptionRole:
		return QVariant::fromValue(_orders[index.row()].description);
	case roles::ValueRole:
		return QVariant::fromValue(_orders[index.row()].value);
	default: return QVariant();
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
