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

#include "motorsettingmodel.h"
#include <QtCore/QVector>
#include <QtCore/QTime>
#include <QtCore/QRect>
#include <QtGui/QColor>

MotorSettingModel::MotorSettingModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_columnCount = 13;
}

MotorSettingModel::~MotorSettingModel()
{
    qDeleteAll(MotorSettingList);
}
bool MotorSettingModel::creatTableModel(int row)
{
    for (int i = 0; i < row; i++) {
        MotorSettingData* motorSetting = new MotorSettingData;
          motorSetting->set_mode(1);
          motorSetting->set_name("motor");
          motorSetting->set_reverse(false);
          motorSetting->set_minPosition(0);
          motorSetting->set_maxPosition(10);
          motorSetting->set_minSpeed(0);
          motorSetting->set_maxSpeed(50);
          motorSetting->set_minAcce(0);
          motorSetting->set_maxAcce(20);
          motorSetting->set_autoSpeed(20);
          motorSetting->set_homeSpeed(50);
          motorSetting->set_manualSpeed(50);
          motorSetting->set_DMX_fixture(0);
          MotorSettingList.append(motorSetting);
    }
}

bool MotorSettingModel::importDataToModel(int row, int col,QVariant data)
{
    if (col == 0)MotorSettingList.at(row)->set_mode(data.toInt());
    else if (col == 1)MotorSettingList.at(row)->set_name(data.toString());
    else if (col == 2)MotorSettingList.at(row)->set_reverse(data.toBool());
    else if (col == 3)MotorSettingList.at(row)->set_minPosition(data.toInt());
    else if (col == 4)MotorSettingList.at(row)->set_maxPosition(data.toInt());
    else if (col == 5)MotorSettingList.at(row)->set_minSpeed(data.toInt());
    else if (col == 6)MotorSettingList.at(row)->set_maxSpeed(data.toInt());
    else if (col == 7)MotorSettingList.at(row)->set_minAcce(data.toInt());
    else if (col == 8)MotorSettingList.at(row)->set_maxAcce(data.toInt());
    else if (col == 9)MotorSettingList.at(row)->set_autoSpeed(data.toInt());
    else if (col == 10)MotorSettingList.at(row)->set_homeSpeed(data.toInt());
    else if (col ==11)MotorSettingList.at(row)->set_manualSpeed(data.toInt());
    else if (col == 12)MotorSettingList.at(row)->set_DMX_fixture(data.toInt());
}

int MotorSettingModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return MotorSettingList.count();
}

int MotorSettingModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}

QVariant MotorSettingModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal){
        if (section == 0)return QString("MODE");
        else if (section == 1)return QString("NAME");
        else if (section == 2)return QString("REVERSE");
        else if (section == 3)return QString("MINPOS");
        else if (section == 4)return QString("MAXPOS");
        else if (section == 5)return QString("MINS");
        else if (section == 6)return QString("MAXS");
        else if (section == 7)return QString("MINA");
        else if (section == 8)return QString("MAXA");
        else if (section == 9)return QString("ASPEED");
        else if (section == 10)return QString("HSPEED");
        else if (section == 11)return QString("MSPEED");
        else if (section == 12)return QString("DMXFT");

        return section;
    }else
        return QString("%1").arg(section + 1);
}

QVariant MotorSettingModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole||role == Qt::EditRole) {
        if (index.column() == 0)return MotorSettingList.at(index.row())->get_mode();
        else if (index.column() == 1)return MotorSettingList.at(index.row())->get_name();
        else if (index.column() == 2)return MotorSettingList.at(index.row())->get_reverse();
        else if (index.column() == 3)return MotorSettingList.at(index.row())->get_minPosition();
        else if (index.column() == 4)return MotorSettingList.at(index.row())->get_maxPosition();
        else if (index.column() == 5)return MotorSettingList.at(index.row())->get_minSpeed();
        else if (index.column() == 6)return MotorSettingList.at(index.row())->get_maxSpeed();
        else if (index.column() == 7)return MotorSettingList.at(index.row())->get_minAcce();
        else if (index.column() == 8)return MotorSettingList.at(index.row())->get_maxAcce();
        else if (index.column() == 9)return MotorSettingList.at(index.row())->get_autoSpeed();
        else if (index.column() == 10)return MotorSettingList.at(index.row())->get_homeSpeed();
        else if (index.column() == 11)return MotorSettingList.at(index.row())->get_manualSpeed();
        else if (index.column() == 12)return MotorSettingList.at(index.row())->get_DMX_fixture();
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

bool MotorSettingModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();
        if (index.column() == 0)MotorSettingList.at(row)->set_mode(value.toInt());
        else if (index.column() == 1)MotorSettingList.at(row)->set_name(value.toString());
        else if (index.column() == 2)MotorSettingList.at(row)->set_reverse(value.toBool());
        else if (index.column() == 3)MotorSettingList.at(row)->set_minPosition(value.toInt());
        else if (index.column() == 4)MotorSettingList.at(row)->set_maxPosition(value.toInt());
        else if (index.column() == 5)MotorSettingList.at(row)->set_minSpeed(value.toInt());
        else if (index.column() == 6)MotorSettingList.at(row)->set_maxSpeed(value.toInt());
        else if (index.column() == 7)MotorSettingList.at(row)->set_minAcce(value.toInt());
        else if (index.column() == 8)MotorSettingList.at(row)->set_maxAcce(value.toInt());
        else if (index.column() == 9)MotorSettingList.at(row)->set_autoSpeed(value.toInt());
        else if (index.column() == 10)MotorSettingList.at(row)->set_homeSpeed(value.toInt());
        else if (index.column() == 11)MotorSettingList.at(row)->set_manualSpeed(value.toInt());
        else if (index.column() == 12)MotorSettingList.at(row)->set_DMX_fixture(value.toInt());

        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags MotorSettingModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void MotorSettingModel::addMapping(QString color, QRect area)
{
    m_mapping.insertMulti(color, area);
}
bool MotorSettingModel::insertRows(int pos, int count, const QModelIndex &parent)
{

    beginInsertRows(QModelIndex(), pos, pos + count - 1);

    endInsertRows();

    return true;
}

 bool MotorSettingModel::removeRows(int pos, int count, const QModelIndex &parent)
 {
     if(pos>=0){
        beginRemoveRows(QModelIndex(), pos, pos + count - 1);
        endRemoveRows();
        return true;
     }else{

     }

    return false;
 }



