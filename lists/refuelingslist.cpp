#include "refuelingslist.h"

RefuelingsList::RefuelingsList(const QVector<Refueling>& list)
{
    append(list);
}

void RefuelingsList::append(const Refueling& item, bool supressUpdate)
{
	_refuelings.append(item);

    if (supressUpdate) return;

    auto idx = createIndex(_refuelings.count(), 0);
    emit dataChanged(idx, idx);
}

void RefuelingsList::append(const QVector<Refueling> &list)
{
    auto startIndex = createIndex(_refuelings.count(), 0);
    for (auto &item : list) append(item, true);
    auto endIndex = createIndex(_refuelings.count(), 0);
    emit dataChanged(startIndex, endIndex);
}

void RefuelingsList::clear()
{
    _refuelings.clear();
}

QVariant RefuelingsList::data(const QModelIndex &index, int role) const
{
	switch (role) {
    case roles::IdRole:
        return QVariant::fromValue(_refuelings[index.row()].id);
	case roles::DriverNameRole:
		return QVariant::fromValue(_refuelings[index.row()].driverName);
	case roles::DriverContractDateRole:
		return QVariant::fromValue(_refuelings[index.row()].driverContractDate);
	case roles::DateRole:
		return QVariant::fromValue(_refuelings[index.row()].date);
	case roles::CostRole:
		return QVariant::fromValue(_refuelings[index.row()].cost);
	default: return QVariant();
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
