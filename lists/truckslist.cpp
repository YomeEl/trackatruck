#include "truckslist.h"

TrucksList::TrucksList(const QVector<Truck>& list)
{
    append(list);
}

void TrucksList::append(const Truck& item, bool supressUpdate)
{
	_trucks.append(item);

    if (supressUpdate) return;

    auto idx = createIndex(_trucks.count(), 0);
    emit dataChanged(idx, idx);
}

void TrucksList::append(const QVector<Truck> &list)
{
    auto startIndex = createIndex(_trucks.count(), 0);
    for (auto &item : list) append(item, true);
    auto endIndex = createIndex(_trucks.count(), 0);
    emit dataChanged(startIndex, endIndex);
}

void TrucksList::clear()
{
    _trucks.clear();
}

QVariant TrucksList::data(const QModelIndex &index, int role) const
{
	switch (role) {
    case roles::IdRole:
        return QVariant::fromValue(_trucks[index.row()].id);
	case roles::ModelRole:
		return QVariant::fromValue(_trucks[index.row()].model);
	case roles::NumberRole:
		return QVariant::fromValue(_trucks[index.row()].number);
	case roles::LastMileageRole:
		return QVariant::fromValue(_trucks[index.row()].lastMileage);
	case roles::LastMaintananceDateRole:
		return QVariant::fromValue(_trucks[index.row()].lastMaintananceDate);
	default: return QVariant();
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
