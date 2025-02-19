#ifndef REFUELINGSLIST_H
#define REFUELINGSLIST_H

#include <QVector>

#include "abstractdatabaselist.h"
#include "abstractdatabaselist.cpp"
#include "..\types.h"

class RefuelingsList : public AbstractDatabaseList<Refueling>
{
    Q_OBJECT
public:
    RefuelingsList(QObject *parent = nullptr);

public:
	enum roles
	{
        IdRole = Qt::UserRole + 1,
        DriverNameRole,
		DriverContractDateRole,
		DateRole,
		CostRole
	};

	QVariant data(const QModelIndex &index, int role) const;
	QHash<int, QByteArray> roleNames() const;
};

#endif // REFUELINGSLIST_H
