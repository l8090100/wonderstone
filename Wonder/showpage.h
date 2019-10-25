#ifndef SHOWPAGE_H
#define SHOWPAGE_H


#include <QWidget>
#include <QStackedWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QtSerialPort/QSerialPort>
#include <QtWidgets>
#include <QItemDelegate>
#include <QSpinBox>
#include <QHostAddress>
#include "database.h"
#include "datapage.h"
#include "motorblock.h"
#include "cuedata.h"
#include "cuedatamodel.h"
#include "currencymodel.h"
#include "customtablemodel.h"
#include "threadfromqthread.h"
#include "runcuethread.h"




QT_BEGIN_NAMESPACE
class ShowPage;
class MotorBlock;
class DataPage;
class QUdpSocket;
QT_END_NAMESPACE


class ShowPage : public QWidget
{
    Q_OBJECT
public:
    explicit ShowPage(QWidget *parent = 0);
    ~ShowPage();
public:
    Ui::ShowPage *ui;
    static QString selectIndexName;
    static QString MotorIndexName[10];
    void static make_m_model();
    void static make_MB();
    static QList<MotorBlock*> *mb;
    static CustomTableModel *get_m_model(){return m_model;}
    static int get_cueTableSelectRow();
    void select_CueTableRow(int row);
//    QList<CueData*> CueList;
    static void showMotorData();
    int getMotorBlockIndex();

    QTableView *get_cueList_table();
public:
    void set_Des_Slider(int value);
    void set_Des_spinbox(int value);
    void set_SpeedInput_Slider(int value);
    void set_SpeedInput_spinbox(int value);
    void set_AcceInput_Slider(int value);
    void set_AcceInput_spinbox(int value);
    void set_DelayInput_spinbox(int value);
    void set_ContiInput_spinBox(int value);
    void set_SetMinPos_spinBox(int value);
    void set_SetMaxPos_spinBox(int value);
    void set_ManualSpeed_slider(int value);
    void set_ManualSpeed_spinBox(int value);
    void set_HomeSpeed_slider(int value);
    void set_HomeSpeed_spinBox(int value);

    void set_ui_default();
    void set_ui_custom();

public slots:
    void on_Show_SetDes_Slider_valueChanged(int value);
    void on_Show_SetDes_spinBox_valueChanged(int arg1);
    void on_Show_SpeedInput_Slider_valueChanged(int value);
    void on_Show_SpeedInput_spinBox_valueChanged(int arg1);
    void on_Show_AcceInput_Slider_valueChanged(int value);
    void on_Show_AcceInput_spinBox_valueChanged(int arg1);
    void on_Show_DelayInput_spinBox_valueChanged(int arg1);
    void ShowPage_Mouse_Pressed(int,MotorCue*);
    void on_Show_ContiInput_spinBox_valueChanged(int arg1);
    void on_Show_SetMinPos_spinBox_valueChanged(int arg1);
    void on_Show_SetMaxPos_spinBox_valueChanged(int arg1);
    void on_Show_ManualSpeed_slider_valueChanged(int value);
    void on_Show_ManualSpeed_spinBox_valueChanged(int arg1);
    void on_Show_HomeSpeed_slider_valueChanged(int value);
    void on_Show_HomeSpeed_spinBox_valueChanged(int arg1);
    void on_Show_AddCue_button_clicked();
    void on_Show_DeleteCue_button_clicked();
    void on_Show_SelectPreviousCue_button_clicked();
    void on_Show_SelectNextCue_button_clicked();
    void on_Show_EditMode_Togglebutton_clicked(bool checked);
    void onTableClicked(const QModelIndex &index);
    void showMotorData2(const QModelIndex &);
    void read_serial_progress();
    void step_progress();
    void cue_progress(int val);

    void processPendingDatagrams();

signals:
    void write_all_motors_max(const QByteArray &data);
    void write_all_motors(const QByteArray &data);
    void generateCueBlock(QString cueName);


private slots:
    void on_Show_Go_Button_clicked();
    void on_Show_SetMaxPos_button_clicked();

    void on_Show_SetMinPos_button_clicked();
    void on_Show_AllMin_Button_clicked();

    void on_Show_AdvancedSetting_Button_clicked();

    void on_Show_Stop_Button_clicked();
    void slotContextMenu(QPoint pos);


    void on_Show_Connect_Button_clicked();
    void on_Show_Disconnect_Button_clicked();

public:
    QUdpSocket *udpSocket;
    QHostAddress groupAddress;

    static int cueTableSelectRow;
    static int delay_temp;
    static bool final_cue_flag;
    static int interval_data[8];
    static int total_finished_motor;
    static bool flag_all_motor_finished;
    static CustomTableModel *m_model;
    ThreadFromQThread* m_thread;
    RunCueThread* cue_thread;

    ThreadFromQThread *read_serial_thread;
    QTimer read_serial_timer;
    bool connect_serial_flag = false;
    int read_serial_counter = 1;

    QTimer show_heart;
    QSqlTableModel *cueList_Model;

    QMenu *popMenu;
    QAction *addToBoard_Action;

    QByteArray* datagram;

    static bool cue_flag;
    static bool cue_delay_flag;
    static bool cue_conti_flag;
    static bool motor_flag[8];
    static bool motor_delay_flag[8];
    static bool motor_request_flag[8];
    static bool  flag_arrived[8];
    static bool  destination_send[8];
    static int cue_delay_Temp;
    static int motor_delay_Temp[8];

    void UpdateData(const QModelIndex &indexA, const QModelIndex &indexB);


    void setRead_all_motor_thread(ThreadFromQThread *value);
};


#endif // SHOWPAGE_H

