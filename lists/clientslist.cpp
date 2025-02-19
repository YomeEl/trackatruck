#include "clientslist.h"

ClientsList::ClientsList(QObject *parent) : AbstractDatabaseList(parent) {}

QVariant ClientsList::data(const QModelIndex &index, int role) const
{
    const Client &item = _data[index.row()];

	switch (role) {
    case roles::IdRole:
        return QVariant::fromValue(item.id);
	case roles::NameRole:
        return QVariant::fromValue(item.name);
	case roles::AddressRole:
        return QVariant::fromValue(item.address);
    case roles::SummaryRole:
        return QVariant::fromValue(item.name + " (" + item.address + ")");
    default:
        return QVariant();
	}
}

QHash<int, QByteArray> ClientsList::roleNames() const
{
	QHash<int, QByteArray> names;

    names[roles::IdRole] = "id";
	names[roles::NameRole] = "name";
	names[roles::AddressRole] = "address";
    names[roles::SummaryRole] = "summary";

	return names;
}
