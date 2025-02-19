#include "driverslist.h"

DriversList::DriversList(QObject *parent) : AbstractDatabaseList(parent) {}

QVariant DriversList::data(const QModelIndex &index, int role) const
{
    const Driver &item = _data[index.row()];

	switch (role) {
    case roles::IdRole:
        return QVariant::fromValue(item.id);
	case roles::NameRole:
        return QVariant::fromValue(item.name);
	case roles::ContractDateRole:
        return QVariant::fromValue(item.contractDate);
    default:
        return QVariant();
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
