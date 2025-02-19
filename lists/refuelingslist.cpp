#include "refuelingslist.h"

RefuelingsList::RefuelingsList(QObject *parent) : AbstractDatabaseList(parent) {}

QVariant RefuelingsList::data(const QModelIndex &index, int role) const
{
    const Refueling &item = _data[index.row()];

	switch (role) {
    case roles::IdRole:
        return QVariant::fromValue(item.id);
	case roles::DriverNameRole:
        return QVariant::fromValue(item.driverName);
	case roles::DriverContractDateRole:
        return QVariant::fromValue(item.driverContractDate);
	case roles::DateRole:
        return QVariant::fromValue(item.date);
	case roles::CostRole:
        return QVariant::fromValue(item.cost);
    default:
        return QVariant();
	}
}

QHash<int, QByteArray> RefuelingsList::roleNames() const
{
	QHash<int, QByteArray> names;

    names[roles::IdRole] = "id";
	names[roles::DriverNameRole] = "driverName";
	names[roles::DriverContractDateRole] = "driverContractDate";
	names[roles::DateRole] = "date";
	names[roles::CostRole] = "cost";

	return names;
}
