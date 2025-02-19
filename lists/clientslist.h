#ifndef CLIENTSLIST_H
#define CLIENTSLIST_H

#include <QVector>

#include "abstractdatabaselist.h"
#include "abstractdatabaselist.cpp"
#include "..\types.h"

class ClientsList : public AbstractDatabaseList<Client>
{
    Q_OBJECT
public:
    ClientsList(QObject *parent = nullptr);

public:
	enum roles
	{
        IdRole = Qt::UserRole + 1,
        NameRole,
        AddressRole,
        SummaryRole
	};

	QVariant data(const QModelIndex &index, int role) const;
	QHash<int, QByteArray> roleNames() const;
};

#endif // CLIENTSLIST_H
