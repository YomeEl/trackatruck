#include "clientslist.h"

ClientsList::ClientsList(const QVector<Client>& list)
{
    append(list);
}

void ClientsList::append(const Client& item, bool supressUpdate)
{
	_clients.append(item);

    if (supressUpdate) return;

    auto idx = createIndex(_clients.count(), 0);
    emit dataChanged(idx, idx);
}

void ClientsList::append(const QVector<Client> &list)
{
    auto startIndex = createIndex(_clients.count(), 0);
    for (auto &item : list) append(item, true);
    auto endIndex = createIndex(_clients.count(), 0);
    emit dataChanged(startIndex, endIndex);
}

void ClientsList::clear()
{
    _clients.clear();
}

QVariant ClientsList::data(const QModelIndex &index, int role) const
{
	switch (role) {
    case roles::IdRole:
        return QVariant::fromValue(_clients[index.row()].id);
	case roles::NameRole:
		return QVariant::fromValue(_clients[index.row()].name);
	case roles::AddressRole:
		return QVariant::fromValue(_clients[index.row()].address);
    case roles::SummaryRole:
        return QVariant::fromValue(_clients[index.row()].name + " (" + _clients[index.row()].address + ")");
	default: return QVariant();
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
