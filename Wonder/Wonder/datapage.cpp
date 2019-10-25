#include "datapage.h"
#include "ui_datapage.h"
#include "ui_showpage.h"
#include <QtSql>
#include <QSqlTableModel>
#include "mainwindow.h"
#include "cuedata.h"

MotorSettingModel *DataPage::motorSetting_table_model = new MotorSettingModel();
MotorCueModel *DataPage::motorCue_table_model = new MotorCueModel();
ArtnetModel *DataPage::artnet_table_model = new ArtnetModel();
CustomTableModel *DataPage::cueList_table_model = new CustomTableModel();
DataPage::DataPage(QWidget *parent): QWidget(parent),  ui(new Ui::DataPage)
{

    ui->setupUi(this);
    QTableView *table =  ui->Data_CueList_tableView;
//    connect(table, SIGNAL(clicked(const QModelIndex &)), show, SLOT(showMotorData2()));



    //motorSettingTable
    ui->Data_MotorSetting_tableView->setModel(get_motorSetting_model());
    motorSetting_sql_Model = new QSqlTableModel(this);
    motorSetting_sql_Model->setTable("motorSetting");
    motorSetting_sql_Model->select();
    motorSetting_sql_Model->setEditStrategy(QSqlTableModel::OnManualSubmit);   //设置保存策略为手动提交
    get_motorSetting_model()->creatTableModel(motorSetting_sql_Model->rowCount());
    for(int r=0;r<motorSetting_sql_Model->rowCount();r++){
        for(int c=0;c<motorSetting_sql_Model->columnCount();c++){
            get_motorSetting_model()->importDataToModel(r,c,motorSetting_sql_Model->index(r,c).data());
        }
    }

    ui->Data_MotorSetting_tableView->verticalHeader()->setVisible(false);
    ui->Data_MotorSetting_tableView->horizontalHeader()->setStretchLastSection(true);
    ui->Data_MotorSetting_tableView->setContextMenuPolicy(Qt::CustomContextMenu);

//////    //MotorCueTable
    ui->Data_CueData_tableView->setModel(get_motorCue_model());
    motorCue_sql_Model = new QSqlTableModel(this);
    motorCue_sql_Model->setTable("motorData");
    motorCue_sql_Model->select();
    motorCue_sql_Model->setEditStrategy(QSqlTableModel::OnManualSubmit);   //设置保存策略为手动提交
    get_motorCue_model()->creatTableModel(8);
    for(int row=0;row<motorCue_sql_Model->rowCount();row++){
        for(int col=0;col<motorCue_sql_Model->columnCount();col++){
            QString data = motorCue_sql_Model->index(row,col).data().toString();
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
    }
    qDebug() << "first import";
    for(int m=0;m<8;m++){
     for(int c = 0;c<motorCue_sql_Model->columnCount();c++){
         if (c == 1){
             get_motorCue_model()->importDataToModel(m,c,ShowPage::get_m_model()->CueList.at(0)->MCue[m]->get_used());
         }
         else if (c == 2){
             get_motorCue_model()->importDataToModel(m,c,ShowPage::get_m_model()->CueList.at(0)->MCue[m]->get_name());
         }
         else if (c == 3){
             get_motorCue_model()->importDataToModel(m,c,ShowPage::get_m_model()->CueList.at(0)->MCue[m]->get_des());
         }
         else if (c == 4){
             get_motorCue_model()->importDataToModel(m,c,ShowPage::get_m_model()->CueList.at(0)->MCue[m]->get_speed());
         }
         else if (c == 5){
             get_motorCue_model()->importDataToModel(m,c,ShowPage::get_m_model()->CueList.at(0)->MCue[m]->get_acce());
         }
         else if (c == 6){
             get_motorCue_model()->importDataToModel(m,c,ShowPage::get_m_model()->CueList.at(0)->MCue[m]->get_delay());
         }
         else if (c == 7){
             get_motorCue_model()->importDataToModel(m,c,ShowPage::get_m_model()->CueList.at(0)->MCue[m]->get_conti());
         }
     }
    }



    ui->Data_CueData_tableView->verticalHeader()->setVisible(false);
    ui->Data_CueData_tableView->horizontalHeader()->setStretchLastSection(true);
    ui->Data_CueData_tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    //cueListTable
    ui->Data_CueList_tableView->setModel(get_cueList_model());
    cueList_sql_Model = new QSqlTableModel(this);
    cueList_sql_Model->setTable("cueList");
    cueList_sql_Model->select();
    cueList_sql_Model->setEditStrategy(QSqlTableModel::OnManualSubmit);   //设置保存策略为手动提交
    get_cueList_model()->creatTableModel("dd",cueList_sql_Model->rowCount());
    for(int r=0;r<cueList_sql_Model->rowCount();r++){
        for(int c=0;c<cueList_sql_Model->columnCount();c++){
            get_cueList_model()->importDataToModel("dd",r,c,cueList_sql_Model->index(r,c).data());
        }
    }

    ui->Data_CueList_tableView->verticalHeader()->setVisible(false);
    ui->Data_CueList_tableView->horizontalHeader()->setStretchLastSection(true);
    ui->Data_CueList_tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    //artnetTable
    ui->Data_Artnet_tableView->setModel(get_artnet_model());
    artnet_sql_Model = new QSqlTableModel(this);
    artnet_sql_Model->setTable("artnet");
    artnet_sql_Model->setEditStrategy(QSqlTableModel::OnManualSubmit);   //设置保存策略为手动提交
    artnet_sql_Model->select();
    get_artnet_model()->creatTableModel(artnet_sql_Model->rowCount());
    for(int r=0;r<artnet_sql_Model->rowCount();r++){
        for(int c=0;c<artnet_sql_Model->columnCount();c++){
            get_artnet_model()->importDataToModel(r,c+1,artnet_sql_Model->index(r,c).data());
        }
    }
    ui->Data_Artnet_tableView->verticalHeader()->setVisible(false);
    ui->Data_Artnet_tableView->horizontalHeader()->setStretchLastSection(true);

//    artnet_Model->setEditStrategy(QSqlTableModel::OnManualSubmit);

//     connClose();


};


DataPage::~DataPage()
{
    delete ui;
}

QTableView *DataPage::get_cueList_Table()
{
    return ui->Data_CueList_tableView;
}

void DataPage::save_to_project(QSqlTableModel *sql_model,QAbstractTableModel *model,int offset)
{
    sql_model->removeRows(0,sql_model->rowCount());
    sql_model->submitAll();
    sql_model->insertRows(0,model->rowCount());
    sql_model->submitAll();
    for(int r=0;r<model->rowCount();r++){
        for(int c=0;c<model->columnCount();c++){
//          artnet_sql_Model->insertColumn(c);
          sql_model->setData(model->index(r,c),model->data(model->index(r,c+offset),Qt::EditRole));
//        qDebug()<<model->data(model->index(r,c+offset));
        }
    }
    sql_model->submitAll();
 //   sql_model->database().transaction();
    if(sql_model->submitAll()){
//        sql_model->database().commit();
        qDebug()<<"artnet_sql_Model ok~";
    }else{
        sql_model->database().rollback();
        qDebug()<<"save error~";
    }
    //    my_db.close();
}

void DataPage::save_motorCue_to_project()
{
    motorCue_sql_Model->removeRows(0,motorCue_sql_Model->rowCount());
    motorCue_sql_Model->submitAll();
    motorCue_sql_Model->insertRows(0,cueList_table_model->rowCount());
    motorCue_sql_Model->submitAll();

    for(int row=0;row<cueList_table_model->rowCount();row++){
        for(int col=0;col<motorCue_table_model->columnCount();col++){
            QString data;
            if (col == 0){
                data = "1,2,3,4,5,6,7,8";
                motorCue_sql_Model->setData(motorCue_sql_Model->index(row,col),data,Qt::EditRole);
            }
            else if (col == 1){

                for(int m=0;m<8;m++){
                    data = data+QString::number(ShowPage::get_m_model()->CueList.at(row)->MCue[m]->get_used())+",";
                }
                motorCue_sql_Model->setData(motorCue_sql_Model->index(row,col),data,Qt::EditRole);
            }
            else if(col == 2){
                for(int m=0;m<8;m++){
                    data = data+ShowPage::get_m_model()->CueList.at(row)->MCue[m]->get_name()+",";
                }
                motorCue_sql_Model->setData(motorCue_sql_Model->index(row,col),data,Qt::EditRole);
            }
            else if(col == 3){
                for(int m=0;m<8;m++){
                    data = data+QString::number(ShowPage::get_m_model()->CueList.at(row)->MCue[m]->get_des())+",";
                }
                motorCue_sql_Model->setData(motorCue_sql_Model->index(row,col),data,Qt::EditRole);
            }
            else if(col == 4){
                for(int m=0;m<8;m++){
                    data = data+QString::number(ShowPage::get_m_model()->CueList.at(row)->MCue[m]->get_speed())+",";
                }
                motorCue_sql_Model->setData(motorCue_sql_Model->index(row,col),data,Qt::EditRole);
            }
            else if(col == 5){
                for(int m=0;m<8;m++){
                   data = data+QString::number(ShowPage::get_m_model()->CueList.at(row)->MCue[m]->get_acce())+",";
                }
                motorCue_sql_Model->setData(motorCue_sql_Model->index(row,col),data,Qt::EditRole);
            }
            else if(col == 6){
                for(int m=0;m<8;m++){
                    data = data+QString::number(ShowPage::get_m_model()->CueList.at(row)->MCue[m]->get_delay())+",";
                }
                motorCue_sql_Model->setData(motorCue_sql_Model->index(row,col),data,Qt::EditRole);
            }
            else if(col == 7){
                for(int m=0;m<8;m++){
                   data = data+QString::number(ShowPage::get_m_model()->CueList.at(row)->MCue[m]->get_conti())+",";
                }
                motorCue_sql_Model->setData(motorCue_sql_Model->index(row,col),data,Qt::EditRole);
            }

        }
    }

    motorCue_sql_Model->submitAll();
 //   sql_model->database().transaction();
    if(motorCue_sql_Model->submitAll()){
//        sql_model->database().commit();
        qDebug()<<"artnet_sql_Model ok~";
    }else{
        motorCue_sql_Model->database().rollback();
        qDebug()<<"save error~";
    }

}

void DataPage::on_CUE_CueLower_button_clicked()
{
    //artnet_Model->submitAll();
}

void DataPage::onTableClicked(const QModelIndex &index)
{
    if (index.isValid()) {
//        ShowPage::showMotorData();
        emit DATA_cueListTable_clicked(index);
        qDebug() << index.row();
    }
}

