/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "artnetmodel.h"
#include <QtCore/QVector>
#include <QtCore/QTime>
#include <QtCore/QRect>
#include <QtGui/QColor>

ArtnetModel::ArtnetModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_columnCount = 4;
}

ArtnetModel::~ArtnetModel()
{
    qDeleteAll(ArtnetList);
}
bool ArtnetModel::creatTableModel(int row)
{
    for (int i = 0; i < row; i++) {
            Artnetdata* artnet = new Artnetdata;
            artnet->set_ID(i);
            artnet->set_function("func");
            artnet->set_channel(0);
            artnet->set_used(false);
            ArtnetList.append(artnet);
    }
}

bool ArtnetModel::importDataToModel(int row, int col,QVariant data)
{
    if(col==0){
         ArtnetList.at(row)->set_ID(data.toInt());
    }else if(col==1){
        ArtnetList.at(row)->set_function(data.toString());
    }else if(col == 2){
        ArtnetList.at(row)->set_channel(data.toInt());
    }else if(col == 3){
        ArtnetList.at(row)->set_used(data.toBool());
    }
}

int ArtnetModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ArtnetList.count();
}

int ArtnetModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}

QVariant ArtnetModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal){
        if (section == 0){
            return QString("NO");
        }else if (section == 1)
            return QString("FUNC");
        else if (section == 2)
            return QString("CHAN");
        else if (section == 3)
            return QString("USED");
        return section;
    }else
        return QString("%1").arg(section + 1);
}

QVariant ArtnetModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.column() == 0){
            return index.row()+1;
        }else if (index.column() == 1)
            return ArtnetList[index.row()]->get_function();
        else if (index.column() == 2)
            return ArtnetList[index.row()]->get_channel();
        else if (index.column() == 3)
            return ArtnetList[index.row()]->get_used();
    } else if (role == Qt::EditRole) {
        if (index.column() == 0){
            return index.row()+1;
        }else if (index.column() == 1)
            return ArtnetList[index.row()]->get_function();
        else if (index.column() == 2)
            return ArtnetList[index.row()]->get_channel();
        else if (index.column() == 3)
            return ArtnetList[index.row()]->get_used();
    } else if (role == Qt::BackgroundRole) {
        QRect rect;
        foreach (rect, m_mapping)
        if (rect.contains(index.column(), index.row()))
            return QColor(m_mapping.key(rect));

        // cell not mapped return white color
        return QColor(Qt::white);
    }
    return QVariant();
}

bool ArtnetModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();
        if (index.column() == 0)
            return index.row()+1;
        else if (index.column() == 1)
            ArtnetList.at(row)->set_function(value.toString());
        else if (index.column() == 2)
            ArtnetList.at(row)->set_channel(value.toInt());
        else if (index.column() == 3)
            ArtnetList.at(row)->set_used(value.toBool());

        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags ArtnetModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void ArtnetModel::addMapping(QString color, QRect area)
{
    m_mapping.insertMulti(color, area);
}
bool ArtnetModel::insertRows(int pos, int count, const QModelIndex &parent)
{

    beginInsertRows(QModelIndex(), pos, pos + count - 1);

    endInsertRows();

    return true;
}

 bool ArtnetModel::removeRows(int pos, int count, const QModelIndex &parent)
 {
     if(pos>=0){
        beginRemoveRows(QModelIndex(), pos, pos + count - 1);
        endRemoveRows();
        return true;
     }else{

     }

    return false;
 }



