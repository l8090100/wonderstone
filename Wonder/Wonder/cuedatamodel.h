#ifndef CUEDATAMODEL_H
#define CUEDATAMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QMap>
#include <cuedata.h>

class CueDataModel:public QAbstractTableModel
{
public:
    CueDataModel(QObject *parent=0);
    ~CueDataModel();
//    void setCueList(QList<CueData> CueList);
    void setCurrencyMap(QMap<QString, double> &map);
    int rowCount(const QModelIndex &parent) const;
    bool insertRows(int position, int rows, const QModelIndex &parent);
    bool removeRows(int position, int rows, const QModelIndex &parent);
//    QList<CueData> CueList;
    QMap<QString, double> currencyMap;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index,int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index)const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
private:
    QList<CueData*> CueList;
//    QString cueListAt(int offset) const;
    QString currencyAt(int offset) const;
};


#endif // CUEDATAMODEL_H
