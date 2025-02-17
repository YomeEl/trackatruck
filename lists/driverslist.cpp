#include "driverslist.h"

DriversList::DriversList(const QVector<Driver>& list)
{
    append(list);
}

void DriversList::append(const Driver& item, bool supressUpdate)
{
	_drivers.append(item);

    if (supressUpdate) return;

    auto idx = createIndex(_drivers.count(), 0);
    emit dataChanged(idx, idx);
}

void DriversList::append(const QVector<Driver> &list)
{
    auto startIndex = createIndex(_drivers.count(), 0);
    for (auto &item : list) append(item, true);
    auto endIndex = createIndex(_drivers.count(), 0);
    emit dataChanged(startIndex, endIndex);
}

void DriversList::clear()
{
    _drivers.clear();
}

QVariant DriversList::data(const QModelIndex &index, int role) const
{
	switch (role) {
    case roles::IdRole:
        return QVariant::fromValue(_drivers[index.row()].id);
	case roles::NameRole:
		return QVariant::fromValue(_drivers[index.row()].name);
	case roles::ContractDateRole:
		return QVariant::fromValue(_drivers[index.row()].contractDate);
	default: return QVariant();
	}
}

QHash<int, QByteArray> DriversList::roleNames() const
{
	QHash<int, QByteArray> names;

    names[roles::IdRole] = "id";
	names[roles::NameRole] = "name";
	names[roles::ContractDateRole] = "contractDate";

	return names;
}
