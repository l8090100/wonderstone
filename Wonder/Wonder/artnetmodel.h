#ifndef ARTNETMODEL_H
#define ARTNETMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/QHash>
#include <QtCore/QRect>
#include "artnetdata.h"

class ArtnetModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ArtnetModel(QObject *parent = 0);
    virtual ~ArtnetModel();
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
    QList<Artnetdata*> ArtnetList;
//    QList<Artnetdata_B*> ArtnetList;

private:
    QHash<QString, QRect> m_mapping;
    int m_columnCount;
    int m_rowCount;
};

//class Artnetdata_B :public ArtnetModel
//{
//public:
//    Artnetdata_B();
//public:
//    void set_ID(int id){ this->_ID = id;}
//    void set_function(QString func){this->_function = func;}
//    void set_channel(int chan){this->_channel = chan;}
//    void set_used(bool used){this->_used = used;}

//    int get_ID(){return this->_ID;}
//    QString get_function(){return this->_function;}
//    int get_channel(){return this->_channel;}
//    bool get_used(){return this->_used;}
//private:
//    int _ID;
//    QString _function;
//    int _channel;
//    bool _used;
//};

#endif // ARTNETMODEL_H
