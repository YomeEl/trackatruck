#include "truckslist.h"

QVariant TrucksList::data(const QModelIndex &index, int role) const
{
    const Truck &item = _data[index.row()];

	switch (role) {
    case roles::IdRole:
        return QVariant::fromValue(item.id);
	case roles::ModelRole:
        return QVariant::fromValue(item.model);
	case roles::NumberRole:
        return QVariant::fromValue(item.number);
	case roles::LastMileageRole:
        return QVariant::fromValue(item.lastMileage);
	case roles::LastMaintananceDateRole:
        return QVariant::fromValue(item.lastMaintananceDate);
    default:
        return QVariant();
	}
}

QHash<int, QByteArray> TrucksList::roleNames() const
{
	QHash<int, QByteArray> names;

    names[roles::IdRole] = "id";
	names[roles::ModelRole] = "model";
	names[roles::NumberRole] = "number";
	names[roles::LastMileageRole] = "lastMileage";
	names[roles::LastMaintananceDateRole] = "lastMaintananceDate";

	return names;
}
