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

#include "modesettingmodel.h"
#include <QtCore/QVector>
#include <QtCore/QTime>
#include <QtCore/QRect>
#include <QtGui/QColor>
#include <QDebug>


ModeSettingModel::ModeSettingModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_columnCount = 6;
}

ModeSettingModel::~ModeSettingModel()
{
    qDeleteAll(modeSettingList);
}
bool ModeSettingModel::creatTableModel(int row)
{
    for (int i = 0; i < row; i++) {
//        QVector<qreal>* dataVec = new QVector<qreal>(m_columnCount);
            ModeSettingData* modeSetting = new ModeSettingData;
            modeSetting->set_ID(i);
            modeSetting->set_name("MODE");
            modeSetting->set_speed(10);
            modeSetting->set_acce(100);
            modeSetting->set_ULM(10);
            modeSetting->set_LLM(1000);
            modeSettingList.append(modeSetting);
    }
}

bool ModeSettingModel::importDataToModel(int row, int col,QVariant data)
{
    if(col==0){
        modeSettingList.at(row)->set_ID(data.toInt());
    }else if(col==1){
        modeSettingList.at(row)->set_name(data.toString());
    }else if(col == 2){
        modeSettingList.at(row)->set_speed(data.toInt());
    }else if(col == 3){
        modeSettingList.at(row)->set_acce(data.toInt());
    }else if(col == 4){
        modeSettingList.at(row)->set_ULM(data.toInt());
    }else if(col == 5){
        modeSettingList.at(row)->set_LLM(data.toInt());
    }
}

int ModeSettingModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return modeSettingList.count();
}

int ModeSettingModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}

QVariant ModeSettingModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole){
        return QVariant();

    }else if (orientation == Qt::Horizontal){
        if (section == 0){
            return QString("NO");
        }else if (section == 1)
            return QString("NAME");
        else if (section == 2)
            return QString("SPEED");
        else if (section == 3)
            return QString("ACCE");
        else if (section == 4)
            return QString("ULM");
        else if (section == 5)
            return QString("LLM");
    }else
        return QString("%1").arg(section + 1);
}

QVariant ModeSettingModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.column() == 0){
            return index.row()+1;
        }else if (index.column() == 1)
            return modeSettingList[index.row()]->get_name();
        else if (index.column() == 2)
            return modeSettingList[index.row()]->get_speed();
        else if (index.column() == 3)
            return modeSettingList[index.row()]->get_acce();
        else if (index.column() == 4)
            return modeSettingList[index.row()]->get_ULM();
        else if (index.column() == 5)
            return modeSettingList[index.row()]->get_LLM();
    } else if (role == Qt::EditRole) {
        if (index.column() == 0){
            return index.row()+1;
        }else if (index.column() == 1)
            return modeSettingList[index.row()]->get_name();
        else if (index.column() == 2)
            return modeSettingList[index.row()]->get_speed();
        else if (index.column() == 3)
            return modeSettingList[index.row()]->get_acce();
        else if (index.column() == 4)
            return modeSettingList[index.row()]->get_ULM();
        else if (index.column() == 5)
            return modeSettingList[index.row()]->get_LLM();
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

bool ModeSettingModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();
        if (index.column() == 0)
            return index.row()+1;
        else if (index.column() == 1)
            modeSettingList.at(row)->set_name(value.toString());
        else if (index.column() == 2)
            modeSettingList.at(row)->set_speed(value.toInt());
        else if (index.column() == 3)
            modeSettingList.at(row)->set_acce(value.toInt());
        else if (index.column() == 4)
            modeSettingList.at(row)->set_ULM(value.toInt());
        else if (index.column() == 5)
            modeSettingList.at(row)->set_LLM(value.toInt());

        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags ModeSettingModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void ModeSettingModel::addMapping(QString color, QRect area)
{
    m_mapping.insertMulti(color, area);
}
bool ModeSettingModel::insertRows(int pos, int count, const QModelIndex &parent)
{

    beginInsertRows(QModelIndex(), pos, pos + count - 1);

    endInsertRows();

    return true;
}

 bool ModeSettingModel::removeRows(int pos, int count, const QModelIndex &parent)
 {
     if(pos>=0){
        beginRemoveRows(QModelIndex(), pos, pos + count - 1);
        endRemoveRows();
        return true;
     }else{

     }

    return false;
 }



