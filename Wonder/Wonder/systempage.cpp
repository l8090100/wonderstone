#include "systempage.h"
#include "ui_systempage.h"
#include "console.h"
#include "settingsdialog.h"
#include "motordata.h"
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QItemDelegate>
#include <QSpinBox>
#include <QtSql>
#include <QSqlTableModel>

SystemSettingModel *SystemPage::system_table_model = new SystemSettingModel();
ModeSettingModel *SystemPage::mode_table_model = new ModeSettingModel();
QSerialPort *SystemPage::serial = new QSerialPort();
QByteArray *SystemPage::response_data_temp = new QByteArray();
int SystemPage::write_all_motor = 0;
SystemPage::SystemPage(QWidget *parent): QWidget(parent),  ui(new Ui::SystemPage)
{
    ui->setupUi(this);
    console = new Console;
    console->setEnabled(false);
//    serial = new QSerialPort(this);
    settings = new SettingsDialog;
    status = new QLabel;
    ui->System_Console_VLayout->addWidget(console);
   // ui->statusBar->addWidget(status);
    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &SystemPage::handleError);
//! [2]
    connect(serial, &QSerialPort::readyRead, this, &SystemPage::readData);
//! [2]
    connect(console, &Console::getData, this, &SystemPage::writeData);


//   system_sql_Model = new QSqlTableModel(this);
//   system_sql_Model->setTable("systemSetting");
//   system_sql_Model->select();
//   get_system_model()->creatTableModel(system_sql_Model->rowCount());

//   systemSetting_Model = new QSqlTableModel(this);
//   systemSetting_Model->setTable("modeSetting");
//   ui->System_SystemSetting_tableView->setModel(systemSetting_Model);
//   systemSetting_Model->select();

//   ui->System_SystemSetting_tableView->verticalHeader()->setVisible(false);
//   ui->System_SystemSetting_tableView->horizontalHeader()->setStretchLastSection(true);
//   systemSetting_Model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//   ui->System_SystemSetting_tableView->setContextMenuPolicy(Qt::CustomContextMenu);

   ui->System_SystemSetting_tableView->setModel(get_system_model());
   system_sql_Model = new QSqlTableModel(this);
   system_sql_Model->setTable("systemSetting");
   system_sql_Model->select();
   system_sql_Model->setEditStrategy(QSqlTableModel::OnManualSubmit);   //设置保存策略为手动提交
   get_system_model()->creatTableModel(system_sql_Model->rowCount());
   for(int r=0;r<system_sql_Model->rowCount();r++){
       for(int c=0;c<system_sql_Model->columnCount();c++){
           get_system_model()->importDataToModel(r,c,system_sql_Model->index(r,c).data());
       }
   }
   ui->System_SystemSetting_tableView->verticalHeader()->setVisible(false);
   ui->System_SystemSetting_tableView->horizontalHeader()->setStretchLastSection(true);
//    get_mode_model()->setEditStrategy(QSqlTableModel::OnManualSubmit);
   ui->System_SystemSetting_tableView->setContextMenuPolicy(Qt::CustomContextMenu);


    ui->System_ModeSetting_tableView->setModel(get_mode_model());
    mode_sql_Model = new QSqlTableModel(this);
    mode_sql_Model->setTable("modeSetting");
    mode_sql_Model->select();
    mode_sql_Model->setEditStrategy(QSqlTableModel::OnManualSubmit);   //设置保存策略为手动提交
    get_mode_model()->creatTableModel(mode_sql_Model->rowCount());
    for(int r=0;r<mode_sql_Model->rowCount();r++){
        for(int c=0;c<mode_sql_Model->columnCount();c++){
            get_mode_model()->importDataToModel(r,c,mode_sql_Model->index(r,c).data());
        }
    }
    ui->System_ModeSetting_tableView->verticalHeader()->setVisible(false);
    ui->System_ModeSetting_tableView->horizontalHeader()->setStretchLastSection(true);
//    get_mode_model()->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->System_ModeSetting_tableView->setContextMenuPolicy(Qt::CustomContextMenu);


//    connClose();
};

SystemPage::~SystemPage()
{
    delete settings;
    delete ui;
}

void SystemPage::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        console->setEnabled(true);
        console->setLocalEchoEnabled(p.localEchoEnabled);
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));

    } else {
        serial->errorString();
        showStatusMessage(tr("Open error"));
    }
}
//! [4]


//! [5]
void SystemPage::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    console->setEnabled(false);
    showStatusMessage(tr("Disconnected"));

}

//! [6]
void SystemPage::writeData(const QByteArray &data,int motor)
{
    serial->write(data);
    write_all_motor = motor;
//    qDebug()<< write_all_motor;
}

//! [7]
void SystemPage::readData()
{
    QByteArray data = serial->readAll();

    console->putData(data);

    static QByteArray byteArray;
        byteArray = byteArray+data;

        //we want to read all message not only chunks
        if(!QString(byteArray).contains("\n"))
            return;

        //sanitize data
        QString data2 = QString( byteArray ).remove("\r").remove("\n");
        byteArray.clear();

        // Print data
//        qDebug() << "RECV: " << data2;
//    if(write_all_motor >0){
         emit sendData(data2,write_all_motor);
//    }
//    qDebug()<<"readData: "<< data;
}
//! [7]

//! [8]
void SystemPage::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        closeSerialPort();
    }
}

void SystemPage::about()
{
}
void SystemPage::showStatusMessage(const QString &message)
{
    status->setText(message);
}


void SystemPage::on_System_OpenSerial_button_clicked()
{
    openSerialPort();
}

void SystemPage::on_System_CloseSerial_button_clicked()
{
    closeSerialPort();
}

void SystemPage::on_System_SettingDialog_button_clicked()
{
    settings->show();
}

void SystemPage::on_System_ClearConsole_button_clicked()
{
    console->clear();
}


