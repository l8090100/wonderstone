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
QByteArray *SystemPage::PasteData = new QByteArray();
//QByteArray *SystemPage::ReadData = new QByteArray();
QString SystemPage::write_all_motor[] = {"0","0","0","0","0","0","0","0"};
int SystemPage::request_motor = 1;
int SystemPage::request_motor_count = 0;
bool SystemPage::data_write_flag = false;
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


    //对于子线程的东西（将被移入子线程的自定义对象以及线程对象），最好定义为指针
      myT = new MyThread;//将被子线程处理的自定义对象不能在主线程初始化的时候指定父对象
      thread = new QThread(this);//初始化子线程线程

      myT->moveToThread(thread);//将自定义对象移交给子线程，从此子线程控制他的成员函数

      //启动子线程，但是没有启动真正的子线程处理函数，
      //只是让子线程对象开始监控移交给他的相关对象
      thread->start();

      //绑定/连接关闭应用程序窗口的信号和主线程的dealClose槽函数
      connect(this, &SystemPage::destroyed, this, &SystemPage::dealClose);

//    connClose();
};

SystemPage::~SystemPage()
{
    delete settings;
    delete ui;
    serial->close();
    delete serial;
}

void SystemPage::dealClose()
{
    if(thread->isRunning() == false)
     {
            return;
     }

    //2.如果调用的是子线程的函数（对象已被放入子线程，其成员函数均在子线程）
    //需要在子线程退出的之前调用

    myT->setFlag(true);//更新子线程的isStop标志--结束子线程的处理函数
    //3.退出子线程要显示的调用这两个函数，否则主线程退出但子线程还在运行
    thread->quit();
    //回收资源
    thread->wait();

    //4. 将要被放入子线程的对象在主线程初始化（构造）的时候不能指定父对象，且需要在子线程结束以后显示delete
    delete myT;
}

void SystemPage::serialDisplay(QByteArray tmp)
{
    //操作头部数据
    QString str_display;
    QString str = tmp.toHex().data();//转换为16进制，再转为char*

    str = str.toUpper();//转换为大写形式

    str_display.clear();
    for(int i = 0;i < str.length();i+= 2)
    {
        QString st = str.mid(i,2);//取出16进制的char*中的两个字符（就是一个完整的16进制数字）
        str_display += st;//累加到str_display
        str_display += " ";//相邻两个16进制数据之间添加一个空格，方便显示
    }

    //在接受文本编辑框接显示收到的包头数据
    qDebug()<<str_display ;

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
        serial->setDataTerminalReady(true);
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
void SystemPage::writeData(const QByteArray &data)
{
        serial->write(data);
}

//! [7]
void SystemPage::readData()
{

    QByteArray BufferData= serial->readAll();
    console->putData(BufferData);
    ReadData.append(BufferData);
    if ( ReadData.contains( "$" )&& ReadData.contains( "#" ))
    {
//         qDebug()<<ReadData.split('$').at(1);
         emit send_to_showPage(ReadData.split('$').at(1));
         ReadData.clear();
    }



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


