#ifndef MOTORCUEMODEL_H
#define MOTORCUEMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/QHash>
#include <QtCore/QRect>
#include "motorcue.h"

class MotorCueModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MotorCueModel(QObject *parent = 0);
    virtual ~MotorCueModel();
    bool creatTableModel(int row);
    bool importDataToModel(int row,int col,QVariant value);
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
signals:
    void set_headerData2(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    void data2(const QModelIndex &index, int role = Qt::DisplayRole) const;
public:
    QList<MotorCue*> MotorCueList;
private:
    QHash<QString, QRect> m_mapping;
    int m_columnCount;
    int m_rowCount;
};


#endif // MOTORCUEMODEL_H
