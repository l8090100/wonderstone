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

#include "motorcuemodel.h"
#include <QtCore/QVector>
#include <QtCore/QTime>
#include <QtCore/QRect>
#include <QtGui/QColor>

MotorCueModel::MotorCueModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_columnCount = 8;
}

MotorCueModel::~MotorCueModel()
{
    qDeleteAll(MotorCueList);
}
bool MotorCueModel::creatTableModel(int row)
{
    for (int i = 0; i < row; i++) {
            MotorCue* motorCue = new MotorCue;
            motorCue->set_mode(false);
            motorCue->set_used(true);
            motorCue->set_name("motor");
            motorCue->set_des(1000);
            motorCue->set_speed(50);
            motorCue->set_acce(20);
            motorCue->set_delay(0);
            motorCue->set_cont(0);
            MotorCueList.append(motorCue);
    }
}

bool MotorCueModel::importDataToModel(int row, int col,QVariant value)
{
    QString data = value.toString();
    bool booling = false;

    if (col == 1){
        for(int m=0;m<8;m++){
            if(data.split(",").at(m)==1){booling = true;}else{booling = false;}
            ShowPage::get_m_model()->CueList.at(row)->MCue[m]->set_used(booling);
        }
    }
    else if(col == 2){
        for(int m=0;m<8;m++){
            ShowPage::get_m_model()->CueList.at(row)->MCue[m]->set_name(data.split(",").at(m));
        }
    }
    else if(col == 3){
        for(int m=0;m<8;m++){
            int value = data.split(",").at(m).toInt();
            ShowPage::get_m_model()->CueList.at(row)->MCue[m]->set_des(value);
        }
    }
    else if(col == 4){
        for(int m=0;m<8;m++){
            int value = data.split(",").at(m).toInt();
            ShowPage::get_m_model()->CueList.at(row)->MCue[m]->set_speed(value);
        }
    }
    else if(col == 5){
        for(int m=0;m<8;m++){
            int value = data.split(",").at(m).toInt();
            ShowPage::get_m_model()->CueList.at(row)->MCue[m]->set_acce(value);
        }
    }
    else if(col == 6){
        for(int m=0;m<8;m++){
            int value = data.split(",").at(m).toInt();
            ShowPage::get_m_model()->CueList.at(row)->MCue[m]->set_delay(value);
        }
    }
    else if(col == 7){
        for(int m=0;m<8;m++){
            int value = data.split(",").at(m).toInt();
            ShowPage::get_m_model()->CueList.at(row)->MCue[m]->set_cont(value);
        }
    }

}

int MotorCueModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return MotorCueList.count();
}

int MotorCueModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}

QVariant MotorCueModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal){
        if (section == 0){
            return QString("NO");
        }else if (section == 1)
            return QString("USED");
        else if (section == 2)
            return QString("NAME");
        else if (section == 3)
            return QString("DES");
        else if (section == 4)
            return QString("SPEED");
        else if (section == 5)
            return QString("ACCE");
        else if (section == 6)
            return QString("DELAY");
        else if (section == 7)
            return QString("CONTI");
        return section;
    }else
        return QString("%1").arg(section + 1);
}

QVariant MotorCueModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole||role == Qt::EditRole) {
        if (index.column() == 0){
            return index.row()+1;
        }
        else if (index.column() == 1){
            return ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[index.row()]->get_used();
        }
        else if (index.column() == 2){
            return ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[index.row()]->get_name();
        }
        else if (index.column() == 3){
            return ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[index.row()]->get_des();
        }
        else if (index.column() == 4){
            return ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[index.row()]->get_speed();
        }
        else if (index.column() == 5){
            return ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[index.row()]->get_acce();
        }
        else if (index.column() == 6){
            return ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[index.row()]->get_delay();
        }
        else if (index.column() == 7){
            return ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[index.row()]->get_conti();
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

bool MotorCueModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        QString data = value.toString();
        if (index.column() == 1){
            for(int m=0;m<8;m++){
                bool booling = false;
                if(data.split(",").at(m)==1){booling = true;}else{booling = false;}
                ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[m]->set_used(booling);
            }
        }
        else if(index.column() == 2){
            for(int m=0;m<8;m++){
                ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[m]->set_name(data.split(",").at(m));
            }
        }
        else if(index.column() == 3){
            for(int m=0;m<8;m++){
                int value = data.split(",").at(m).toInt();
                ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[m]->set_des(value);
            }
        }
        else if(index.column() == 4){
            for(int m=0;m<8;m++){
                int value = data.split(",").at(m).toInt();
                ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[m]->set_speed(value);
            }
        }
        else if(index.column() == 5){
            for(int m=0;m<8;m++){
                int value = data.split(",").at(m).toInt();
                ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[m]->set_acce(value);
            }
        }
        else if(index.column() == 6){
            for(int m=0;m<8;m++){
                int value = data.split(",").at(m).toInt();
                ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[m]->set_delay(value);
            }
        }
        else if(index.column() == 7){
            for(int m=0;m<8;m++){
                int value = data.split(",").at(m).toInt();
                ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[m]->set_cont(value);
            }
        }

        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags MotorCueModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void MotorCueModel::addMapping(QString color, QRect area)
{
    m_mapping.insertMulti(color, area);
}
bool MotorCueModel::insertRows(int pos, int count, const QModelIndex &parent)
{

    beginInsertRows(QModelIndex(), pos, pos + count - 1);

    endInsertRows();

    return true;
}

 bool MotorCueModel::removeRows(int pos, int count, const QModelIndex &parent)
 {
     if(pos>=0){
        beginRemoveRows(QModelIndex(), pos, pos + count - 1);
        endRemoveRows();
        return true;
     }else{

     }

    return false;
 }



