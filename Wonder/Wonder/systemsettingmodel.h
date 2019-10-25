#ifndef SYSTEMSETTINGMODEL_H
#define SYSTEMSETTINGMODEL_H
#include <QtCore/QAbstractTableModel>
#include <QtCore/QHash>
#include <QtCore/QRect>
#include "systemsettingdata.h"

class SystemSettingModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SystemSettingModel(QObject *parent = 0);
    virtual ~SystemSettingModel();
    bool creatTableModel(int row);
    bool importDataToModel(int row,int col,QVariant data);
    void setList();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant set_headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void addMapping(QString color, QRect area);
    void clearMapping() { m_mapping.clear(); }
    bool insertRows(int row,int count,const QModelIndex &parent);
    bool removeRows(int row,int count,const QModelIndex &parent);
public:
    QList<SystemSettingData*> systemSettingList;

private:
    QHash<QString, QRect> m_mapping;
    int m_columnCount;
    int m_rowCount;
};

#endif // SYSTEMSETTINGMODEL_H
