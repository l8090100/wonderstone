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

#include "systemsettingmodel.h"
#include <QtCore/QVector>
#include <QtCore/QTime>
#include <QtCore/QRect>
#include <QtGui/QColor>
#include <QDebug>

SystemSettingModel::SystemSettingModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_columnCount = 6;
}

SystemSettingModel::~SystemSettingModel()
{
    qDeleteAll(systemSettingList);
}
bool SystemSettingModel::creatTableModel(int row)
{
    for (int i = 0; i < row; i++) {
//        QVector<qreal>* dataVec = new QVector<qreal>(m_columnCount);
            SystemSettingData* systemSetting = new SystemSettingData;
            systemSetting->set_ID(i);
            systemSetting->set_name("setting");
            systemSetting->set_ULM_used(true);
            systemSetting->set_LLM_used(true);
            systemSetting->set_Mode(2);
            systemSettingList.append(systemSetting);
    }
}

bool SystemSettingModel::importDataToModel(int row, int col,QVariant data)
{
    if(col==1){
        systemSettingList.at(row)->set_name(data.toString());
    }else if(col==2){
        systemSettingList.at(row)->set_ID(data.toInt());
    }else if(col == 3){
        systemSettingList.at(row)->set_ULM_used(data.toBool());
    }else if(col == 4){
        systemSettingList.at(row)->set_LLM_used(data.toBool());
    }else if(col == 5){
        systemSettingList.at(row)->set_Mode(data.toInt());
    }
    return true;
}

int SystemSettingModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return systemSettingList.count();
}

int SystemSettingModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}

QVariant SystemSettingModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal){
        if (section == 0){
            return QString("NO");
        }else if (section == 1)
            return QString("NAME");
        else if (section == 2)
            return QString("ID");
        else if (section == 3)
            return QString("ULM");
        else if (section == 4)
            return QString("LLM");
        else if (section == 5)
            return QString("MODE");
    }else
        return QString("%1").arg(section + 1);
}

QVariant SystemSettingModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.column() == 0){
            return index.row()+1;
        }else if (index.column() == 1){
            return systemSettingList[index.row()]->get_name();
        }else if (index.column() == 2){
             return systemSettingList[index.row()]->get_ID();
        }else if (index.column() == 3){
            return systemSettingList[index.row()]->get_ULM_used();
        }else if (index.column() == 4){
            return systemSettingList[index.row()]->get_LLM_used();
        }else if (index.column() == 5){
            return systemSettingList[index.row()]->get_Mode();
        }
    } else if (role == Qt::EditRole) {
        if (index.column() == 0){
            return index.row()+1;
        }else if (index.column() == 1){
            return systemSettingList[index.row()]->get_name();
        }else if (index.column() == 2){
             return systemSettingList[index.row()]->get_ID();
        }else if (index.column() == 3){
            return systemSettingList[index.row()]->get_ULM_used();
        }else if (index.column() == 4){
            return systemSettingList[index.row()]->get_LLM_used();
        }else if (index.column() == 5){
            return systemSettingList[index.row()]->get_Mode();
        }
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

bool SystemSettingModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();
        if (index.column() == 0){
            return index.row()+1;
        }else if (index.column() == 1){
            systemSettingList.at(row)->set_name(value.toString());
        }else if (index.column() == 2){
            systemSettingList.at(row)->set_ID(value.toInt());
        }else if (index.column() == 3){
            systemSettingList.at(row)->set_ULM_used(value.toBool());
        }else if (index.column() == 4){
            systemSettingList.at(row)->set_LLM_used(value.toBool());
        }else if (index.column() == 5){
            systemSettingList.at(row)->set_Mode(value.toInt());
        }

        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags SystemSettingModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void SystemSettingModel::addMapping(QString color, QRect area)
{
    m_mapping.insertMulti(color, area);
}
bool SystemSettingModel::insertRows(int pos, int count, const QModelIndex &parent)
{

    beginInsertRows(QModelIndex(), pos, pos + count - 1);

    endInsertRows();

    return true;
}

 bool SystemSettingModel::removeRows(int pos, int count, const QModelIndex &parent)
 {
     if(pos>=0){
        beginRemoveRows(QModelIndex(), pos, pos + count - 1);
        endRemoveRows();
        return true;
     }else{

     }

    return false;
 }



