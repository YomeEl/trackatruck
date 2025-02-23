#include "truckslist.h"

QVariant TrucksList::data(const QModelIndex &index, int role) const
{
    const Truck &item = _data[index.row()];

	switch (role) {
    case roles::IdRole:
        return QVariant::fromValue(item.id);
    case roles::TruckModelRole:
        return QVariant::fromValue(item.truckModel);
	case roles::NumberRole:
        return QVariant::fromValue(item.number);
    case roles::LastMilageRole:
        return QVariant::fromValue(item.lastMilage);
	case roles::LastMaintananceDateRole:
        return QVariant::fromValue(item.lastMaintananceDate);
    case roles::IsFreeRole:
        return QVariant::fromValue(item.isFree);
    default:
        return QVariant();
	}
}

QHash<int, QByteArray> TrucksList::roleNames() const
{
	QHash<int, QByteArray> names;

    names[roles::IdRole] = "id";
    names[roles::TruckModelRole] = "truckModel";
	names[roles::NumberRole] = "number";
    names[roles::LastMilageRole] = "lastMilage";
	names[roles::LastMaintananceDateRole] = "lastMaintananceDate";
    names[roles::IsFreeRole] = "isFree";

	return names;
}
