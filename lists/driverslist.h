#ifndef DRIVERSLIST_H
#define DRIVERSLIST_H

#include <QVector>

#include "abstractdatabaselist.h"
#include "abstractdatabaselist.cpp"
#include "..\types.h"

class DriversList : public AbstractDatabaseList<Driver>
{
    Q_OBJECT
public:
    DriversList(QObject *parent = nullptr);

public:
	enum roles
	{
        IdRole = Qt::UserRole + 1,
        NameRole,
        ContractDateRole,
        IsFreeRole
	};

	QVariant data(const QModelIndex &index, int role) const;
	QHash<int, QByteArray> roleNames() const;
};

#endif // DRIVERSLIST_H
