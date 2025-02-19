#ifndef TRUCKSLIST_H
#define TRUCKSLIST_H

#include <QVector>

#include "abstractdatabaselist.h"
#include "abstractdatabaselist.cpp"
#include "..\types.h"

class TrucksList : public AbstractDatabaseList<Truck>
{
    Q_OBJECT
public:
    TrucksList(QObject *parent = nullptr) : AbstractDatabaseList(parent){}

public:
	enum roles
	{
        IdRole = Qt::UserRole + 1,
        ModelRole,
		NumberRole,
		LastMileageRole,
		LastMaintananceDateRole
	};

	QVariant data(const QModelIndex &index, int role) const;
	QHash<int, QByteArray> roleNames() const;
};

#endif // TRUCKSLIST_H
