#ifndef CURRENCYMODEL_H
#define CURRENCYMODEL_H

#include <QAbstractTableModel>
#include <QMap>

class CurrencyModel : public QAbstractTableModel
{
public:
    CurrencyModel(QObject *parent = 0);
    ~CurrencyModel();
    void setCurrencyMap(const QMap<QString, double> &map);
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);
    int rowCount(const QModelIndex &parent) const;

protected:
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;


public:
    QMap<QString, double> currencyMap;
private:
    QString currencyAt(int offset) const;
};

#endif // CURRENCYMODEL_H
