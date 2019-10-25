#ifndef SYSTEMPAGE_H
#define SYSTEMPAGE_H

#include <QStackedWidget>
#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QtSerialPort/QSerialPort>
#include <QtWidgets>
#include <QItemDelegate>
#include <QSpinBox>
#include "database.h"
#include <modesettingdata.h>
#include <systemsettingdata.h>
#include <modesettingmodel.h>
#include <systemsettingmodel.h>
#include <mythread.h>


namespace Ui {
class SystemPage;
}
class Console;
class SettingsDialog;


class SystemPage : public QWidget, public DataBase
{
    Q_OBJECT

public:
    explicit SystemPage(QWidget *parent = 0);
    ~SystemPage();
public:
    static SystemSettingModel *system_table_model;
    QList<SystemSettingData*> *system_Data_List;
    QSqlTableModel *system_sql_Model;

    static ModeSettingModel *mode_table_model;
    QList<SystemSettingData*> *mode_Data_List;
    QSqlTableModel *mode_sql_Model;

    static SystemSettingModel *get_system_model(){return system_table_model;}
    static ModeSettingModel *get_mode_model(){return mode_table_model;}
public slots:
    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data);
    void readData();
    void handleError(QSerialPort::SerialPortError error);
    void on_System_OpenSerial_button_clicked();
    void on_System_CloseSerial_button_clicked();
    void on_System_SettingDialog_button_clicked();
    void on_System_ClearConsole_button_clicked();

signals:
    void sendData(const QString data,int motor);
    void send_to_showPage(QByteArray data);
signals:
    void initUart(QSerialPortInfo info);//发送给子线程的串口初始化信号

private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();

public:
    Ui::SystemPage *ui;
    SettingsDialog *settings;
    static QSerialPort *serial;
    Console *console;
    QLabel *status;
    QSqlTableModel *modeSetting_Model;
    QSqlTableModel *systemSetting_Model;
    void showStatusMessage(const QString &message);

    static QByteArray *PasteData;
    QByteArray ReadData;
    static QString write_all_motor[8];
    static int request_motor_count;
    static int request_motor;
    static bool data_write_flag;

public:
    void dealClose();
    void serialDisplay(QByteArray tmp);
    MyThread *myT;//自定义对象指针--将要放入子线程

    QThread *thread;//子线程--负责串口数据的读取

    QTimer *myTimer;

};

#endif // ARTNETDATA_H
