#include "currencymodel.h"
#include <QtDebug>

CurrencyModel::CurrencyModel(QObject *parent):
QAbstractTableModel(parent)
{
}
CurrencyModel::~CurrencyModel()
{
}

void CurrencyModel::setCurrencyMap(const QMap<QString, double> &map)
{
    beginResetModel();
    currencyMap = map;
    endResetModel();
}

int CurrencyModel::rowCount(const QModelIndex &parent) const
{
    return currencyMap.count();
}

int CurrencyModel::columnCount(const QModelIndex &parent) const
{
    return currencyMap.count();
}

QVariant CurrencyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    } else if (role == Qt::DisplayRole) {
        QString rowCurrency = currencyAt(index.row());
        QString columnCurrency = currencyAt(index.column());

        if (index.column() == 1) return (currencyMap.begin() + index.row()).value(); //第二列表用来显示QComboBox选择的内容
        if (currencyMap.value(rowCurrency) == 0.0) return "####";

        double amount = currencyMap.value(columnCurrency) / currencyMap.value(rowCurrency);

        return QString("%1").arg(amount, 0, 'f', 4);
    }

    return QVariant();
}

QVariant CurrencyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();

    return currencyAt(section);
}

QString CurrencyModel::currencyAt(int offset) const
{
    return (currencyMap.begin() + offset).key();
}

bool CurrencyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        int row = index.row();
        int  col = index.column();

        currencyMap[(currencyMap.begin() + row).key()] = value.toDouble();
        return true;
    }

    return false;
}


Qt::ItemFlags CurrencyModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

bool CurrencyModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row + count - 1);

    endInsertRows();

    return true;
}

 bool CurrencyModel::removeRows(int row, int count, const QModelIndex &parent)
 {
    beginRemoveRows(QModelIndex(), row, row + count - 1);

    endRemoveRows();

    return true;
 }
