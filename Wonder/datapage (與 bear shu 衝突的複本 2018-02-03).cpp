#include "datapage.h"
#include "ui_datapage.h"
#include "ui_showpage.h"
#include <QtSql>
#include <QSqlTableModel>
#include "mainwindow.h"
#include "cuedata.h"

MotorSettingModel *DataPage::motorSetting_table_model = new MotorSettingModel();
//MotorCueModel *DataPage::motorCue_table_model = new MotorCueModel();
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
//    ui->Data_CueData_tableView->setModel(get_motorCue_model());
//    motorCue_sql_Model = new QSqlTableModel(this);
//    motorCue_sql_Model->setTable("motorData");
//    motorCue_sql_Model->select();
//    get_motorCue_model()->creatTableModel(8);
//    for(int r=0;r<motorCue_sql_Model->rowCount();r++){
//        for(int c=0;c<motorCue_sql_Model->columnCount();c++){
//            get_motorCue_model()->importDataToModel(0,c,motorCue_sql_Model->index(r,c).data());
//        }
//    }

//    ui->Data_CueData_tableView->verticalHeader()->setVisible(false);
//    ui->Data_CueData_tableView->horizontalHeader()->setStretchLastSection(true);
//    ui->Data_CueData_tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    //cueListTable
    ui->Data_CueList_tableView->setModel(get_cueList_model());
    cueList_sql_Model = new QSqlTableModel(this);
    cueList_sql_Model->setTable("cueList");
    cueList_sql_Model->select();
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
    artnet_sql_Model->select();
    get_artnet_model()->creatTableModel(artnet_sql_Model->rowCount());
    for(int r=0;r<artnet_sql_Model->rowCount();r++){
        for(int c=0;c<artnet_sql_Model->columnCount();c++){
            get_artnet_model()->importDataToModel(r,c,artnet_sql_Model->index(r,c).data());
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

