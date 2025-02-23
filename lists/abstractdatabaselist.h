#ifndef ABSTRACTDATABASELIST_H
#define ABSTRACTDATABASELIST_H

#include <QAbstractListModel>

template <typename T>
class AbstractDatabaseList : public QAbstractListModel
{
public:
    explicit AbstractDatabaseList(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    void syncData(const QVector<T> &newData);
    QVector<T>& data();

protected:
    QVector<T> _data;
};

#endif // ABSTRACTDATABASELIST_H
