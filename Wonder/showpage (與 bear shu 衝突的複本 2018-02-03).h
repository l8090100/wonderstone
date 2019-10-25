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
#include "database.h"
#include "datapage.h"
#include "motorblock.h"
#include "cuedata.h"
#include "cuedatamodel.h"
#include "currencymodel.h"
#include "customtablemodel.h"


namespace Ui {
class ShowPage;
class MotorBlock;
class DataPage;
}

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


private:
    static int cueTableSelectRow;
    static CustomTableModel *m_model;

    QSqlTableModel *cueList_Model;
    void UpdateData(const QModelIndex &indexA, const QModelIndex &indexB);


};


#endif // SHOWPAGE_H

