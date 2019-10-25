#ifndef MODESETTINGMODEL_H
#define MODESETTINGMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/QHash>
#include <QtCore/QRect>
#include "modesettingdata.h"

class ModeSettingModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ModeSettingModel(QObject *parent = 0);
    virtual ~ModeSettingModel();
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
    QList<ModeSettingData*> modeSettingList;

private:
    QHash<QString, QRect> m_mapping;
    int m_columnCount;
    int m_rowCount;
};

#endif // MODESETTINGMODEL_H
