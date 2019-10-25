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

#include "customtablemodel.h"
#include <QtCore/QVector>
#include <QtCore/QTime>
#include <QtCore/QRect>
#include <QtGui/QColor>
#include <QDebug>

CustomTableModel::CustomTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{

    m_columnCount = 5;
    m_rowCount = 5;

    // m_data
//    for (int i = 0; i < m_rowCount; i++) {
////        QVector<qreal>* dataVec = new QVector<qreal>(m_columnCount);
//            CueData* cue = new CueData;
//            cue->set_cueUsed(true);
//            cue->set_cueName("Q");
//            cue->set_cueDelay(m_rowCount+100);
//            cue->set_cueDmxChannel(0);
//            cue->set_cueContinue(0);
//            CueList.append(cue);
//        }
}

CustomTableModel::~CustomTableModel()
{
    qDeleteAll(CueList);
}
bool CustomTableModel::creatTableModel(QString table,int row)
{

    for (int i = 0; i < row; i++) {
//        QVector<qreal>* dataVec = new QVector<qreal>(m_columnCount);
            CueData* cue = new CueData;
            cue->set_cueUsed(true);
            cue->set_cueName("Q");
            cue->set_cueDelay(m_rowCount+100);
            cue->set_cueDmxChannel(0);
            cue->set_cueContinue(0);
            CueList.append(cue);
    }
}

bool CustomTableModel::importDataToModel(QString table,int row, int col,QVariant data)
{
    if(col==5){
        CueList.at(row)->set_cueUsed(data.toBool());
    }else if(col == 1){
        CueList.at(row)->set_cueName(data.toString());
    }else if(col == 2){
        CueList.at(row)->set_cueDelay(data.toInt());
    }else if(col == 3){
        CueList.at(row)->set_cueDmxChannel(data.toInt());
    }else if(col == 4){
        CueList.at(row)->set_cueContinue(data.toInt());
    }
}

int CustomTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return CueList.count();
}

int CustomTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal){
        return section;
    }else
        return QString("%1").arg(section + 1);
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.column() == 0){
            return index.row()+1;
        }else if (index.column() == 1)
            return CueList[index.row()]->get_cueName();
        else if (index.column() == 2)
            return CueList[index.row()]->get_cueDelay();
        else if (index.column() == 3)
            return CueList[index.row()]->get_cueDmxChannel();
        else if (index.column() == 4)
            return CueList[index.row()]->get_cueContinue();
    } else if (role == Qt::EditRole) {
        if (index.column() == 0){
            return index.row()+1;
        }else if (index.column() == 1)
            return CueList[index.row()]->get_cueName();
        else if (index.column() == 2)
            return CueList[index.row()]->get_cueDelay();
        else if (index.column() == 3)
            return CueList[index.row()]->get_cueDmxChannel();
        else if (index.column() == 4)
            return CueList[index.row()]->get_cueContinue();
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

bool CustomTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();
        if (index.column() == 0)
            CueList.at(row)->set_cueUsed(value.toBool());
        else if (index.column() == 1)
            CueList.at(row)->set_cueName(value.toString());
        else if (index.column() == 2)
            CueList.at(row)->set_cueDelay(value.toInt());
        else if (index.column() == 3)
            CueList.at(row)->set_cueDmxChannel(value.toInt());
        else if (index.column() == 4)
            CueList.at(row)->set_cueContinue(value.toInt());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags CustomTableModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void CustomTableModel::addMapping(QString color, QRect area)
{
    m_mapping.insertMulti(color, area);
}
bool CustomTableModel::insertRows(int pos, int count, const QModelIndex &parent)
{

    beginInsertRows(QModelIndex(), pos, pos + count - 1);

    endInsertRows();

    return true;
}

 bool CustomTableModel::removeRows(int pos, int count, const QModelIndex &parent)
 {
     if(pos>=0){
        beginRemoveRows(QModelIndex(), pos, pos + count - 1);
        endRemoveRows();
        return true;
     }else{

     }

    return false;
 }
//QVariant CustomTableModel::artnet_data(int section){
//    if (section == 0){
//        return QString("FUNC");
//    }else if (section == 1)
//        return QString("CHAN");
//    else if (section == 2)
//        return QString("USED");
//}
//QVariant CustomTableModel::cue_data(int section){
//    if (section == 0){
//        return QString("NO");
//    }else if (section == 1)
//        return QString("NAME");
//    else if (section == 2)
//        return QString("DELAY");
//    else if (section == 3)
//        return QString("DMX");
//    else if (section == 4)
//        return QString("CONTI");
//    else if (section == 5)
//        return QString("USED");
//}
//QVariant CustomTableModel::mode_data(int section){
//    if (section == 0){
//        return QString("NO");
//    }else if (section == 1)
//        return QString("NAME");
//    else if (section == 2)
//        return QString("SPEED");
//    else if (section == 3)
//        return QString("ACCE");
//    else if (section == 4)
//        return QString("ULM");
//    else if (section == 5)
//        return QString("LLM");
//}
//QVariant CustomTableModel::motor_data(int section){
//    if (section == 0){
//        return QString("NO");
//    }else if (section == 1)
//        return QString("USED");
//    else if (section == 2)
//        return QString("NAME");
//    else if (section == 3)
//        return QString("DES");
//    else if (section == 4)
//        return QString("SPEED");
//    else if (section == 5)
//        return QString("ACCE");
//    else if (section == 6)
//        return QString("DELAY");
//    else if (section == 7)
//        return QString("CONTI");

//}
//QVariant CustomTableModel::motorSetting_data(int section){
//    if (section == 0){
//        return QString("MODE");
//    }else if (section == 1)
//        return QString("NAME");
//    else if (section == 2)
//        return QString("REVERSE");
//    else if (section == 3)
//        return QString("MINP");
//    else if (section == 4)
//        return QString("MAXP");
//    else if (section == 1)
//        return QString("MINS");
//    else if (section == 2)
//        return QString("MAXS");
//    else if (section == 3)
//        return QString("MINA");
//    else if (section == 4)
//        return QString("MAXA");
//    else if (section == 2)
//        return QString("AS");
//    else if (section == 3)
//        return QString("HS");
//    else if (section == 4)
//        return QString("MS");
//    else if (section == 4)
//        return QString("DMXFIX");

//}
//QVariant CustomTableModel::systemSetting_data(int section){
//    if (section == 0){
//        return QString("NO");
//    }else if (section == 1)
//        return QString("NAME");
//    else if (section == 2)
//        return QString("ID");
//    else if (section == 3)
//        return QString("ULM");
//    else if (section == 4)
//        return QString("MODE");

//}




