#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QtSerialPort/QSerialPort>
#include "systempage.h"
#include <QtSql>
#include <QSqlTableModel>
#include "database.h"
#include "datapage.h"
#include "boardpage.h"
#include "threadfromqthread.h"


QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
class SystemPage;
}

QT_END_NAMESPACE

class Console;
class SettingsDialog;

class MainWindow : public QMainWindow, public DataBase
{
    Q_OBJECT
public:
    QSqlDatabase mydb;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static SystemPage *systemPage;
    static ShowPage *showPage;
    static BoardPage *boardPage;
    static DataPage *dataPage;

private slots:
//    void openSerialPort();
//    void closeSerialPort();
//    void about();
//    void writeData(const QByteArray &data);
//    void readData();
//    void handleError(QSerialPort::SerialPortError error);

    void on_Show_Button_clicked();
    void on_Board_Button_clicked();
    void on_Data_Button_clicked();
    void on_System_Button_clicked();
//    void on_System_OpenSerial_button_clicked();
//    void on_System_CloseSerial_button_clicked();
//    void on_System_SettingDialog_button_clicked();
//    void on_System_ClearConsole_button_clicked();
    void on_Show_AllMin_Button_clicked();
    void on_Show_AllHome_Button_clicked();
    void on_actionOpen_Project_triggered();
//    void onQThreadFinished();
    void progress(int val);
    void receiveMessage(const QString& str);
    void heartTimeOut();

private:
    void initActionsConnections();

private:
    void showStatusMessage(const QString &message);

    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    QLabel *status;
    Console *console;
    SettingsDialog *settings;
    QSerialPort *serial;

    ThreadFromQThread* m_thread;
    QThread* m_currentRunLoaclThread;
    QTimer m_heart;
};

#endif // MAINWINDOW_H
