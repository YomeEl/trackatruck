// Autogenerated

#ifndef TRUCKSLIST_H
#define TRUCKSLIST_H

#include <QAbstractListModel>
#include <QVector>

#include "..\types.h"

class TrucksList : public QAbstractListModel
{
public:
	TrucksList() {}
	TrucksList(const QVector<Truck>& list);
    void append(const Truck& item, bool supressUpdate = false);
    void append(const QVector<Truck>& list);
    void clear();

public:
	enum roles
	{
        IdRole = Qt::UserRole + 1,
        ModelRole,
		NumberRole,
		LastMileageRole,
		LastMaintananceDateRole
	};

	int rowCount(const QModelIndex &parent) const { Q_UNUSED(parent); return _trucks.count(); }
	QVariant data(const QModelIndex &index, int role) const;
	QHash<int, QByteArray> roleNames() const;

private:
	QVector<Truck> _trucks;
};

#endif // TRUCKSLIST_H
