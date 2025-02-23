#ifndef ABSTRACTDATABASELIST_CPP
#define ABSTRACTDATABASELIST_CPP

#include "abstractdatabaselist.h"

#include <QSet>

template<typename T>
AbstractDatabaseList<T>::AbstractDatabaseList(QObject *parent)
    : QAbstractListModel(parent)
{}

template<typename T>
int AbstractDatabaseList<T>::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return _data.count();
}

template<typename T>
void AbstractDatabaseList<T>::syncData(const QVector<T> &newData)
{
    QSet<int> currentIds, newIds, toInsert, toDelete, toUpdate;
    for (const auto &o : _data) currentIds.insert(o.id);
    for (const auto &o : newData) newIds.insert(o.id);

    toInsert = QSet<int>(newIds).subtract(currentIds);
    toDelete = QSet<int>(currentIds).subtract(newIds);
    toUpdate = newIds.intersect(currentIds);

    if (toInsert.count() == 0) goto remove;
    beginInsertRows(QModelIndex(), _data.count(), _data.count() + toInsert.count() - 1);
    for (const auto &o : newData)
        if (toInsert.contains(o.id))
        {
            _data.append(o);
        }
    endInsertRows();

remove:
    QVector<size_t> indicesToRemove;
    if (toDelete.count() == 0) goto update;
    for (int i = 0, cnt = 0; i < _data.count(); i++)
        if (toDelete.contains(_data[i].id))
        {
            indicesToRemove.append(i - cnt++);
        }

    for (const int idx : indicesToRemove)
    {
        beginRemoveRows(QModelIndex(), idx, idx + 1);
        _data.removeAt(idx);
        endRemoveRows();
    }

update:
    QMap<size_t, size_t> indicesToUpdate;
    if (toUpdate.count() == 0) goto finish;
    for (const int id : qAsConst(toUpdate))
    {
        size_t currentIdx = -1, newIdx = -1;
        for (int i = 0; i < _data.count(); i++) if (_data[i].id == id) currentIdx = i;
        for (int i = 0; i < newData.count(); i++) if (newData[i].id == id) newIdx = i;
        indicesToUpdate[currentIdx] = newIdx;
    }
    for (const size_t &currentIdx : indicesToUpdate.keys())
    {
        _data[currentIdx] = newData[indicesToUpdate[currentIdx]];
        auto startIndex = createIndex(currentIdx, 0);
        auto endIndex = createIndex(currentIdx, 0);
        emit dataChanged(startIndex, endIndex);
    }

finish:
    return;
}

template<typename T>
QVector<T> &AbstractDatabaseList<T>::data()
{
    return _data;
}

#endif // ABSTRACTDATABASELIST_CPP
