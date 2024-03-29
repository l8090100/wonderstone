#ifndef DATAPAGE_H
#define DATAPAGE_H

#include <QWidget>
#include "database.h"
#include "customtablemodel.h"
#include "artnetmodel.h"
#include "customtablemodel.h"
#include "motorsettingmodel.h"
#include "motorcuemodel.h"
#include "showpage.h"

namespace Ui {
class DataPage;
}

class DataPage : public QWidget, public DataBase
{
    Q_OBJECT

public:
    explicit DataPage(QWidget *parent = 0);
    ~DataPage();
public:
    Ui::DataPage *ui;
    static ArtnetModel *artnet_table_model;
    QSqlTableModel *artnet_sql_Model;
    static ArtnetModel *get_artnet_model(){return artnet_table_model;}

    static CustomTableModel *cueList_table_model;
    QSqlTableModel *cueList_sql_Model;
    static CustomTableModel *get_cueList_model(){return cueList_table_model;}

    static MotorCueModel *motorCue_table_model;
    QSqlTableModel *motorCue_sql_Model;
    static MotorCueModel *get_motorCue_model(){return motorCue_table_model;}

    static MotorSettingModel *motorSetting_table_model;
    QSqlTableModel *motorSetting_sql_Model;
    static MotorSettingModel *get_motorSetting_model(){return motorSetting_table_model;}

    QTableView *get_cueList_Table();

    void save_to_project(QSqlTableModel *sql_model,QAbstractTableModel *model,int offset);
    void save_motorCue_to_project();
signals:
   // void valueChanged(int value);
    void DATA_cueListTable_clicked(const QModelIndex &index);

private slots:
    void on_CUE_CueLower_button_clicked();
    void onTableClicked(const QModelIndex &index);

private:

//    QSqlTableModel *motorSetting_Model;
//    QSqlTableModel *cueData_Model;
//    QSqlTableModel *cueList_Model;
//    QSqlTableModel *artnet_Model;

};



#endif // DATAPAGE_H
