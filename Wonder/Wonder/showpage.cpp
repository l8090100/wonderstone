#include "showpage.h"
#include "ui_showpage.h"
#include "motorblock.h"
#include <QObject>
#include <QDebug>

int ShowPage::cueTableSelectRow = 0;
int ShowPage::delay_temp = 0;
bool ShowPage::final_cue_flag = false;
int ShowPage::interval_data[8] = {0,0,0,0,0,0,0,0};
int ShowPage::total_finished_motor = 0;
bool ShowPage::flag_all_motor_finished = false;

bool ShowPage::cue_flag = false;
bool ShowPage::cue_delay_flag = false;
bool ShowPage::cue_conti_flag = false;
bool ShowPage::motor_flag[8] = {false,false,false,false,false,false,false,false};
bool ShowPage::motor_delay_flag[8]= {false,false,false,false,false,false,false,false};
bool ShowPage::motor_request_flag[8]= {false,false,false,false,false,false,false,false};
bool ShowPage::flag_arrived[8]= {false,false,false,false,false,false,false,false};

CustomTableModel *ShowPage::m_model = new CustomTableModel();
QList<MotorBlock*> *ShowPage::mb = new QList<MotorBlock*>;
QString  ShowPage::selectIndexName = "";
QString  ShowPage::MotorIndexName[] = {"M1","M2","M3","M4","M5","M6","M7","M8","M9","M10"};
ShowPage::ShowPage(QWidget *parent): QWidget(parent),  ui(new Ui::ShowPage)
{
//    DataPage *DATA = new DataPage;
    ui->setupUi(this);

    QTableView *table =  ui->Show_CueListTable_tableView;
    for(int i=0;i<8;i++){
        make_MB();
        QString s = QString::number(i);
        mb->at(i)->setName("motor"+s);
        mb->at(i)->setID(i);
        ui->Show_MotorList_vBox->addWidget(mb->at(i));
        connect(mb->at(i), SIGNAL(MotorBlock_Mouse_Pressed(int,MotorCue*)), this, SLOT(ShowPage_Mouse_Pressed(int,MotorCue*)));
//        connect(DATA-, SIGNAL(DATA_cueListTable_clicked(const QModelIndex &index)), this, SLOT(showMotorData()));

    }

    connect(table, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));

       //make_m_model();
       ui->Show_CueListTable_tableView->setModel(get_m_model());

       ui->Show_CueListTable_tableView->verticalHeader()->setVisible(false);
       ui->Show_CueListTable_tableView->horizontalHeader()->setStretchLastSection(true);
       ui->Show_CueListTable_tableView->setContextMenuPolicy(Qt::CustomContextMenu);


//    for(int c=0;c<10;c++){
////        CueData *cue = new CueData(ui->Show_CueListTable_tableView);
//        cue->set_cueUsed(true);
//        cue->set_cueName("Q");
//        cue->set_cueDelay(c);
//        cue->set_cueDmxChannel(0);
//        cue->set_cueContinue(0);
//        CueList.append(cue);
       // qDebug() << CueList.at(c)->get_cueDelay();
       // CueData cue = new CueData(true,"cue",0,0,0);

//    }

//    connect(ui->Show_CueListTable_tableView->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex)),SLOT(UpdateData(QModelIndex,QModelIndex)));

    cueList_Model = new QSqlTableModel(this);
    cueList_Model->setTable("cueList");
    cueList_Model->select();
    get_m_model()->creatTableModel("cueList",cueList_Model->rowCount());

    for(int r=0;r<cueList_Model->rowCount();r++){
        for(int c=0;c<cueList_Model->columnCount();c++){
            get_m_model()->importDataToModel("cueList",r,c,cueList_Model->index(r,c).data());
        }
//        get_m_model()->importDataToModel();
//        get_m_model()->setData(get_m_model()->index(c,5),cueList_Model->index(c,5).data().toBool());
////        cue->set_cueUsed(cueList_Model->index(c,5).data().toBool());
//        get_m_model()->setData(get_m_model()->index(c,1),cueList_Model->index(c,1).data().toString());
//        get_m_model()->setData(get_m_model()->index(c,2),cueList_Model->index(c,2).data().toInt());
//        get_m_model()->setData(get_m_model()->index(c,3),cueList_Model->index(c,3).data().toInt());
//        get_m_model()->setData(get_m_model()->index(c,4),cueList_Model->index(c,4).data().toInt());
    }

   // QModelIndex index = cueList_Model->index(1,1);


    //ui->Show_CueListTable_tableView->setModel(cueList_Model);

    ui->Show_CueListTable_tableView->verticalHeader()->setVisible(false);
    ui->Show_CueListTable_tableView->horizontalHeader()->setStretchLastSection(true);
//    cueList_Model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    ui->Show_CueListTable_tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    m_thread = new ThreadFromQThread(this);
    cue_thread = new RunCueThread(this);
//    connect(m_thread,&ThreadFromQThread::progress,this,&ShowPage::progress);
//    connect(cue_thread,&RunCueThread::progress,this,&ShowPage::cue_progress);
    connect(&show_heart,&QTimer::timeout,this,&ShowPage::progress);
    show_heart.setInterval(1000);

    set_ui_default();

};

ShowPage::~ShowPage()
{
    delete ui;
}

void ShowPage::make_m_model()
{
    m_model = new CustomTableModel();
}

void ShowPage::make_MB()
{
    MotorBlock *block = new MotorBlock;
    mb->append(block);
}



void ShowPage::on_Show_SetDes_Slider_valueChanged(int value)
{
    ui->Show_SetDes_spinBox->setValue(value);
    int i= getMotorBlockIndex();
    mb->at(i)->setDestination(value);
    get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[i]->set_des(value);
}

void ShowPage::on_Show_SetDes_spinBox_valueChanged(int arg1)
{
    ui->Show_SetDes_Slider->setValue(arg1);
    int i= getMotorBlockIndex();
    mb->at(i)->setDestination(arg1);
    get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[i]->set_des(arg1);
}

void ShowPage::on_Show_SpeedInput_Slider_valueChanged(int value)
{
    ui->Show_SpeedInput_spinBox->setValue(value);
    int i= getMotorBlockIndex();
    mb->at(i)->setSpeed(value);
    get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[i]->set_speed(value);
}

void ShowPage::on_Show_SpeedInput_spinBox_valueChanged(int arg1)
{
    ui->Show_SpeedInput_Slider->setValue(arg1);
    int i= getMotorBlockIndex();
    mb->at(i)->setSpeed(arg1);
    get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[i]->set_speed(arg1);
}

void ShowPage::on_Show_AcceInput_Slider_valueChanged(int value)
{
    ui->Show_AcceInput_spinBox->setValue(value);
    int i= getMotorBlockIndex();
    mb->at(i)->setAcceleration(value);
    get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[i]->set_acce(value);
}

void ShowPage::on_Show_AcceInput_spinBox_valueChanged(int arg1)
{
    ui->Show_AcceInput_Slider->setValue(arg1);
    int i= getMotorBlockIndex();
    mb->at(i)->setAcceleration(arg1);
    get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[i]->set_acce(arg1);
}


void ShowPage::on_Show_DelayInput_spinBox_valueChanged(int arg1)
{
    int i= getMotorBlockIndex();
    mb->at(i)->setDelay(arg1);
    get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[i]->set_delay(arg1);
}

void ShowPage::on_Show_ContiInput_spinBox_valueChanged(int arg1)
{
    int i= getMotorBlockIndex();
    mb->at(i)->setContinue(arg1);
    get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[i]->set_cont(arg1);
}

void ShowPage::on_Show_SetMinPos_spinBox_valueChanged(int arg1)
{
     int i= getMotorBlockIndex();
     mb->at(i)->setMinPosition(arg1);
    ui->Show_SetDes_Slider->setRange(mb->at(i)->getMinPosition(), mb->at(i)->getMaxPosition());
}

void ShowPage::on_Show_SetMaxPos_spinBox_valueChanged(int arg1)
{
     int i= getMotorBlockIndex();
     mb->at(i)->setMaxPosition(arg1);
     ui->Show_SetDes_Slider->setRange(mb->at(i)->getMinPosition(), mb->at(i)->getMaxPosition());
}

void ShowPage::on_Show_ManualSpeed_slider_valueChanged(int value)
{
     ui->Show_ManualSpeed_spinBox->setValue(value);
     int i= getMotorBlockIndex();
     mb->at(i)->setManualSpeed(value);
}

void ShowPage::on_Show_ManualSpeed_spinBox_valueChanged(int arg1)
{
     ui->Show_ManualSpeed_slider->setValue(arg1);
     int i= getMotorBlockIndex();
     mb->at(i)->setManualSpeed(arg1);
}

void ShowPage::on_Show_HomeSpeed_slider_valueChanged(int value)
{
     ui->Show_HomeSpeed_spinBox->setValue(value);
     int i= getMotorBlockIndex();
     mb->at(i)->setHomeSpeed(value);
}

void ShowPage::on_Show_HomeSpeed_spinBox_valueChanged(int arg1)
{
     ui->Show_HomeSpeed_slider->setValue(arg1);
     int i= getMotorBlockIndex();
     mb->at(i)->setHomeSpeed(arg1);
}

void ShowPage::ShowPage_Mouse_Pressed(int i,MotorCue* mc)
{
    qDebug()<<"show:"<<mc->get_delay();
     set_Des_Slider(mc->get_des());
     set_Des_spinbox(mc->get_des());
     set_SpeedInput_Slider(mc->get_speed());
     set_SpeedInput_spinbox(mc->get_speed());
     set_AcceInput_Slider(mc->get_acce());
     set_AcceInput_spinbox(mc->get_acce());
     set_DelayInput_spinbox(mc->get_delay());
     set_ContiInput_spinBox(mc->get_conti());
     set_SetMinPos_spinBox(mb->at(i)->getMinPosition());
     set_SetMaxPos_spinBox(mb->at(i)->getMaxPosition());
     set_ManualSpeed_slider(mb->at(i)->getManualSpeed());
     set_ManualSpeed_spinBox(mb->at(i)->getManualSpeed());
     set_HomeSpeed_slider(mb->at(i)->getHomeSpeed());
     set_HomeSpeed_spinBox(mb->at(i)->getHomeSpeed());
     ui->Show_SetDes_Slider->setRange(mb->at(i)->getMinPosition(), mb->at(i)->getMaxPosition());

}

void ShowPage::set_Des_Slider(int value){ui->Show_SetDes_Slider->setValue(value);}
void ShowPage::set_Des_spinbox(int value){ui->Show_SetDes_spinBox->setValue(value);}
void ShowPage::set_SpeedInput_Slider(int value){ui->Show_SpeedInput_Slider->setValue(value);}
void ShowPage::set_SpeedInput_spinbox(int value){ui->Show_SpeedInput_spinBox->setValue(value);}
void ShowPage::set_AcceInput_Slider(int value){ ui->Show_AcceInput_Slider->setValue(value);}
void ShowPage::set_AcceInput_spinbox(int value){ui->Show_AcceInput_spinBox->setValue(value);}
void ShowPage::set_DelayInput_spinbox(int value){ui->Show_DelayInput_spinBox->setValue(value);}
void ShowPage::set_ContiInput_spinBox(int value){ui->Show_ContiInput_spinBox->setValue(value);}
void ShowPage::set_SetMinPos_spinBox(int value){ui->Show_SetMinPos_spinBox->setValue(value);}
void ShowPage::set_SetMaxPos_spinBox(int value){ui->Show_SetMaxPos_spinBox->setValue(value);}
void ShowPage::set_ManualSpeed_slider(int value){ui->Show_ManualSpeed_slider->setValue(value);}
void ShowPage::set_ManualSpeed_spinBox(int value){ui->Show_ManualSpeed_spinBox->setValue(value);}
void ShowPage::set_HomeSpeed_slider(int value){ui->Show_HomeSpeed_slider->setValue(value);}
void ShowPage::set_HomeSpeed_spinBox(int value){ui->Show_HomeSpeed_spinBox->setValue(value);}

void ShowPage::set_ui_default()
{
    ui->Show_SetDes_Slider->setRange(0, 150000);
    ui->Show_SpeedInput_Slider->setRange(0,3000);
    ui->Show_AcceInput_Slider->setRange(0,100);
    ui->Show_ManualSpeed_slider->setRange(0,2000);
    ui->Show_HomeSpeed_slider->setRange(0,3000);

    ui->Show_SetDes_spinBox->setRange(0, 150000);
    ui->Show_SpeedInput_spinBox->setRange(0,3000);
    ui->Show_AcceInput_spinBox->setRange(0,100);
    ui->Show_ManualSpeed_spinBox->setRange(0,2000);
    ui->Show_HomeSpeed_spinBox->setRange(0,3000);
    ui->Show_SetMaxPos_spinBox->setRange(1,200000);
    ui->Show_SetMinPos_spinBox->setRange(0,3000);

    ui->Show_SetDes_spinBox->setValue(10000);
    ui->Show_SpeedInput_spinBox->setValue(1500);
    ui->Show_AcceInput_spinBox->setValue(20);
    ui->Show_ManualSpeed_spinBox->setValue(1500);
    ui->Show_HomeSpeed_spinBox->setValue(2000);
    ui->Show_SetMaxPos_spinBox->setValue(300000);
    ui->Show_SetMinPos_spinBox->setValue(0);


    ui->Show_SetDes_Slider->setPageStep(100);
    ui->Show_SpeedInput_Slider->setPageStep(100);
    ui->Show_AcceInput_Slider->setPageStep(5);
    ui->Show_ManualSpeed_slider->setPageStep(100);
    ui->Show_HomeSpeed_slider->setPageStep(5);

    ui->Show_SetDes_spinBox->setKeyboardTracking(false);
    ui->Show_SetMinPos_spinBox->setKeyboardTracking(false);
    ui->Show_SpeedInput_spinBox->setKeyboardTracking(false);
    ui->Show_AcceInput_spinBox->setKeyboardTracking(false);
    ui->Show_ManualSpeed_spinBox->setKeyboardTracking(false);
    ui->Show_HomeSpeed_spinBox->setKeyboardTracking(false);
    ui->Show_SetMaxPos_spinBox->setKeyboardTracking(false);
    ui->Show_SetMinPos_spinBox->setKeyboardTracking(false);

}

int ShowPage::getMotorBlockIndex()
{
    int index=0;
    for(int i=0;i<8;i++){
        if(mb->at(i)->getName()==selectIndexName){
            index = i;
        }
    }
    return index;
}

QTableView *ShowPage::get_cueList_table()
{
    return ui->Show_CueListTable_tableView;
}

void ShowPage::on_Show_AddCue_button_clicked()
{

    int row = get_m_model()->rowCount();
    int count = 1;
    if(ui->Show_CueListTable_tableView->currentIndex().row()<0){
        get_m_model()->insertRows(row,count, QModelIndex());
        DataPage::cueList_table_model->insertRows(row,count, QModelIndex());
        for (int c = 0; c < count; ++c) {
            CueData* cue = new CueData;
            cue->set_cueUsed(true);
            cue->set_cueName("Q");
            cue->set_cueDelay(row+100);
            cue->set_cueDmxChannel(c);
            cue->set_cueContinue(c);
            get_m_model()->CueList.insert(row,cue);
            DataPage::cueList_table_model->CueList.insert(row,cue);
        }
        ui->Show_CueListTable_tableView->selectRow(row);
    }else{
        row = ui->Show_CueListTable_tableView->currentIndex().row();
        get_m_model()->insertRows(row+1,count, QModelIndex());
        DataPage::cueList_table_model->insertRows(row,count, QModelIndex());
        for (int c = 0; c < count; ++c) {
            CueData* cue = new CueData;
            cue->set_cueUsed(true);
            cue->set_cueName("Q");
            cue->set_cueDelay(row+100);
            cue->set_cueDmxChannel(c);
            cue->set_cueContinue(c);
            get_m_model()->CueList.insert(row,cue);
           DataPage::cueList_table_model->CueList.insert(row,cue);
        }
        ui->Show_CueListTable_tableView->selectRow(row+1);
    }
//    get_m_model()->CueList.insert(row,cue);
////  cueList_Model->insertRow(row);
//    for(int m=0;m<8;m++){
//        mb->at(m)->setCue();
//    }
//    get_m_model()->setData(get_m_model()->index(row,0),row);
////    cueList_Model->setData(cueList_Model->index(row,0),row);
//    get_m_model()->setData(get_m_model()->index(row,1),"CUE");
//    get_m_model()->setData(get_m_model()->index(row,2), row+1);
//    get_m_model()->setData(get_m_model()->index(row,3), 0);
//    get_m_model()->setData(get_m_model()->index(row,4), false);

    for (int i = 0; i < get_m_model()->rowCount(); ++i) {

            get_m_model()->setData(get_m_model()->index(i,0),i);
            DataPage::cueList_table_model->setData(get_m_model()->index(i,0),i);
            qDebug() << i;

    }

}

void ShowPage::on_Show_DeleteCue_button_clicked()
{
    int row = ui->Show_CueListTable_tableView->currentIndex().row();
    int count = 1;
    get_m_model()->removeRows(row,count,QModelIndex());
    DataPage::cueList_table_model->removeRows(row,count,QModelIndex());
    for (int c = 0; c < count; ++c) {
            get_m_model()->CueList.removeAt(row);
            DataPage::cueList_table_model->CueList.removeAt(row);
        }
     for (int i = 0; i <  get_m_model()->rowCount(); ++i) {
         get_m_model()->setData(get_m_model()->index(i,0),i);
         DataPage::cueList_table_model->setData(DataPage::cueList_table_model->index(i,0),i);
     }
     ui->Show_CueListTable_tableView->selectRow(row);
//    QItemSelectionModel *selmodel = ui->Show_CueListTable_tableView->selectionModel();
//    QModelIndex current = selmodel->currentIndex(); // the "current" item
//    QModelIndexList selected = selmodel->selectedIndexes(); // list of "selected" items

//        for (int i = 0; i < selected.size(); ++i) {

//     qDebug() << selected.at(i).row();
//     qDebug() << cueList_Model->removeRows( selected.at(i).row(), 1);
//     cueList_Model->submitAll();

//         }

//        cueList_Model->removeRow(ui->Show_CueListTable_tableView->currentIndex().row());
//        qDebug() << cueList_Model->rowCount();

//         for (int i = 0; i < cueList_Model->rowCount(); ++i) {

//                 cueList_Model->setData(cueList_Model->index(i,0),i);
//         }

//        cueList_Model->submitAll();


}

void ShowPage::on_Show_SelectPreviousCue_button_clicked()
{

}

void ShowPage::on_Show_SelectNextCue_button_clicked()
{

}

void ShowPage::on_Show_EditMode_Togglebutton_clicked(bool checked)
{

}

void ShowPage::UpdateData(const QModelIndex &indexA, const QModelIndex &indexB)
{

}

void ShowPage::onTableClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        cueTableSelectRow = index.row();
        QString cellText = index.data().toString();
        showMotorData();
        qDebug() << index.row();
    }
}

void ShowPage::showMotorData2(const QModelIndex & index)
{
    int row = cueTableSelectRow;
    for(int i=0;i<8;i++){
        bool used = get_m_model()->CueList.at(row)->MCue[i]->get_used();
        mb->at(i)->setUsed(used);
        int now = get_m_model()->CueList.at(row)->MCue[i]->get_nowPos();
        mb->at(i)->setNowPosition(now);
        int des = get_m_model()->CueList.at(row)->MCue[i]->get_des();
        mb->at(i)->setDestination(des);
        int speed = get_m_model()->CueList.at(row)->MCue[i]->get_speed();
        mb->at(i)->setSpeed(speed);
        int acce = get_m_model()->CueList.at(row)->MCue[i]->get_acce();
        mb->at(i)->setAcceleration(acce);
        int delay = get_m_model()->CueList.at(row)->MCue[i]->get_delay();
        mb->at(i)->setDelay(delay);
        int conti = get_m_model()->CueList.at(row)->MCue[i]->get_conti();
        mb->at(i)->setContinue(conti);

    }
    ui->Show_CueListTable_tableView->selectRow(index.row());
    qDebug() << "show2:"<<ui->Show_CueListTable_tableView->selectionModel()->currentIndex().row();
}

void ShowPage::progress()
{


    int delay = get_m_model()->data(get_m_model()->index(get_cueTableSelectRow(),2)).toInt();

    if(get_m_model()->data(get_m_model()->index(get_cueTableSelectRow(),5)).toBool()==true){
        cue_flag = true;
//        if(get_m_model()->data(get_m_model()->index(get_cueTableSelectRow(),4)).toInt()==1){
//            cue_conti_flag = true;
            if(get_m_model()->data(get_m_model()->index(get_cueTableSelectRow(),2)).toInt()>0){
                cue_delay_flag = false;
                delay_temp++;
                show_heart.setInterval(1000);
                get_m_model()->setData(get_m_model()->index(get_cueTableSelectRow(),2),(delay-1));
                  // get_m_model()->index(c,1),cueList_Model->index(c,1).data().toString()
                qDebug() << "cue dalay:" <<get_m_model()->data(get_m_model()->index(get_cueTableSelectRow(),2)).toInt();
            }else{
                 cue_delay_flag = true;
                        show_heart.setInterval(1000);
                        for(int m=0;m<mb->size();m++){
                            if(mb->at(m)->getUsed()==true){
                                motor_flag[m] = true;
                                if(mb->at(m)->getDelay()>0){
                                    motor_delay_flag[m] = false;
                                    mb->at(m)->setDelay(mb->at(m)->getDelay()-1);
                                }else{
                                    motor_delay_flag[m] = true;
                                    if(mb->at(m)->getNowPosition()<mb->at(m)->getDesTination()){
                                        flag_all_motor_finished = false;
                                        mb->at(m)->setNowPosition(mb->at(m)->getNowPosition()+interval_data[m]);
                                    }
                                    if(mb->at(m)->getNowPosition()==mb->at(m)->getDesTination()){
                                        flag_all_motor_finished = false;
                                        if( flag_arrived[m]==false){
                                         total_finished_motor = total_finished_motor+1;
                                         motor_delay_flag[m] = false;
                                         flag_arrived[m] = true;
                                          qDebug() << "total_finished_motor==:"<< total_finished_motor;
                                        }
                                    }
                                    if(mb->at(m)->getNowPosition()>mb->at(m)->getDesTination()){
                                        flag_all_motor_finished = false;
                                        mb->at(m)->setNowPosition(mb->at(m)->getNowPosition()-interval_data[m]);
                                    }
//                                    else{
            //                            if(m<4){
            //                                QString id = QString::number(m+1);
            //                                QString speed =  QString::number(mb->at(m)->getSpeed());
            //                                QString acce =  QString::number(mb->at(m)->getAcceleratiob());
            //                                QString des = QString::number(mb->at(m)->getDesTination());
            ////                                QString speed_data = "t"+id+"pn10"+"="+speed+"\n";
            ////                                     emit write_all_motors(speed_data.toLocal8Bit(),4);
            ////                                 qDebug() << speed_data;
            ////                                QString acce_data = "t"+id+"pn11"+"="+acce+"\n";
            ////                                     emit write_all_motors(acce_data.toLocal8Bit(),4);
            ////                                qDebug() << acce_data;
            //                                QString des_data = "t"+id+"ma"+des+"\n";
            //                                     emit write_all_motors(des_data.toLocal8Bit(),4);
            //                                qDebug() << des_data;
            //                            }

//                                       total_finished_motor = total_finished_motor+1;

                                       if(total_finished_motor == mb->size()){
                                          flag_all_motor_finished = true;
                                          total_finished_motor = 0;
                                          for(int m=0;m<mb->size();m++){
                                            flag_arrived[m] = false;
                                          }
                                          show_heart.stop();

                                          get_m_model()->setData(get_m_model()->index(get_cueTableSelectRow(),2),delay_temp);
                                          delay_temp = 0;

                                          if(get_cueTableSelectRow()==cueList_Model->rowCount()-1){
                                              final_cue_flag = true;
                                              show_heart.stop();
                                              qDebug() << "final:" <<get_cueTableSelectRow();
                                          }else{
                                                  final_cue_flag = false;
                                                  if(get_m_model()->data(get_m_model()->index(get_cueTableSelectRow(),4)).toInt()==1){
                                                      QModelIndex index = cueList_Model->index(get_cueTableSelectRow()+1,1);
                                                      onTableClicked(index);
                                                      ui->Show_CueListTable_tableView->selectRow(index.row());
                                                      cue_progress(get_cueTableSelectRow());
                                                      qDebug() << "count:" <<get_cueTableSelectRow();
                                                  }else{

                                                  }

                                          }

                                       }
//                                    }

                                }
                            }else{
                                 motor_flag[m] = false;
                                 if( flag_arrived[m]==false){
                                  total_finished_motor = total_finished_motor+1;
                                  flag_arrived[m] = true;
                                  motor_delay_flag[m] = false;
                                  qDebug() << "total_finished_motor else:"<< total_finished_motor;
                                 }

                                 if(total_finished_motor == mb->size()){
                                    show_heart.setInterval(100);
                                    flag_all_motor_finished = true;
                                    total_finished_motor = 0;
                                    for(int m=0;m<mb->size();m++){
                                      flag_arrived[m] = false;
                                    }
                                    show_heart.stop();

                                    get_m_model()->setData(get_m_model()->index(get_cueTableSelectRow(),2),delay_temp);
                                    delay_temp = 0;

                                    if(get_cueTableSelectRow()==cueList_Model->rowCount()-1){
                                        final_cue_flag = true;
                                        show_heart.stop();
                                        qDebug() << "final:" <<get_cueTableSelectRow();
                                    }else{
                                            final_cue_flag = false;
                                            if(get_m_model()->data(get_m_model()->index(get_cueTableSelectRow(),4)).toInt()==1){
                                                QModelIndex index = cueList_Model->index(get_cueTableSelectRow()+1,1);
                                                onTableClicked(index);
                                                ui->Show_CueListTable_tableView->selectRow(index.row());
                                                cue_progress(get_cueTableSelectRow());
                                                qDebug() << "count:" <<get_cueTableSelectRow();
                                            }else{

                                            }

                                    }

                                 }
                            }
                        }
            }
//        }else{
//            cue_conti_flag = false;
//            show_heart.stop();
//        }
    }else{
        cue_flag = false;
        show_heart.setInterval(100);
        QModelIndex index = cueList_Model->index(get_cueTableSelectRow()+1,1);
        onTableClicked(index);
        ui->Show_CueListTable_tableView->selectRow(index.row());
        cue_progress(get_cueTableSelectRow());
        qDebug() << "count:" <<get_cueTableSelectRow();
        //先到最後一 個cue停止，邏輯還要再改
//        if(get_cueTableSelectRow()==cueList_Model->rowCount()-1){
//            show_heart.stop();
//        }
    }


    if(cue_flag==true){
            if(cue_delay_flag==true){
                for(int m=0;m<4;m++){
                    if(motor_flag[m]==true){
                        if(motor_delay_flag[m]==true){
                            //send quest
                                    QString id = QString::number(m+1);
                                    QString speed =  QString::number(mb->at(m)->getSpeed());
                                    QString acce =  QString::number(mb->at(m)->getAcceleratiob());
                                    QString des = QString::number(mb->at(m)->getDesTination());
                                    QString speed_data = "t"+id+"pn10"+"="+speed+"\n";
//                                         emit write_all_motors(speed_data.toLocal8Bit(),4);
//                            //         qDebug() << speed_data;
//                                    QString acce_data = "t"+id+"pn11"+"="+acce+"\n";
//                                         emit write_all_motors(acce_data.toLocal8Bit(),4);
                                //    qDebug() << acce_data;
                                    QString des_data = "t"+id+"ma"+des+"0\n";
                                         emit write_all_motors(des_data.toLocal8Bit(),4);
                             //       qDebug() << des_data;
                                    motor_delay_flag[m]=false;
                        }else{
                            //motor delay
                        }
                    }else{
                        //motor mute
                    }
                }
            }else{
                //cue delay
            }

    }else{
        //cue mute and select next row
    }

}

void ShowPage::cue_progress(int val)
{
    qDebug() << "new:"<< val;

    for(int m=0;m<8;m++){
        mb->at(m)->setNowPosition(0);
        if(mb->at(m)->getNowPosition()<mb->at(m)->getDesTination()){
            interval_data[m] = abs((mb->at(m)->getDesTination() - mb->at(m)->getNowPosition()))/10;
            if(m<4){
                QString id = QString::number(m+1);
                QString speed =  QString::number(mb->at(m)->getSpeed());
                QString acce =  QString::number(mb->at(m)->getAcceleratiob());
                QString des = QString::number(mb->at(m)->getDesTination());
                QString speed_data = "t"+id+"pn10"+"="+speed+"\n";
                     emit write_all_motors(speed_data.toLocal8Bit(),4);
                 qDebug() << speed_data;
                QString acce_data = "t"+id+"pn11"+"="+acce+"\n";
                     emit write_all_motors(acce_data.toLocal8Bit(),4);
                qDebug() << acce_data;
            }
        }else{
        }
    }
    show_heart.start();

}

int ShowPage::get_cueTableSelectRow()
{
    return cueTableSelectRow;
}
void ShowPage::select_CueTableRow(int row)
{
    cueTableSelectRow = row;

}

void ShowPage::showMotorData()
{
    int row = cueTableSelectRow;
    for(int i=0;i<8;i++){
        bool used = get_m_model()->CueList.at(row)->MCue[i]->get_used();
        mb->at(i)->setUsed(used);
        int now = get_m_model()->CueList.at(row)->MCue[i]->get_nowPos();
        mb->at(i)->setNowPosition(now);
        int des = get_m_model()->CueList.at(row)->MCue[i]->get_des();
        mb->at(i)->setDestination(des);
        int speed = get_m_model()->CueList.at(row)->MCue[i]->get_speed();
        mb->at(i)->setSpeed(speed);
        int acce = get_m_model()->CueList.at(row)->MCue[i]->get_acce();
        mb->at(i)->setAcceleration(acce);
        int delay = get_m_model()->CueList.at(row)->MCue[i]->get_delay();
        mb->at(i)->setDelay(delay);
        int conti = get_m_model()->CueList.at(row)->MCue[i]->get_conti();
        mb->at(i)->setContinue(conti);

    }
 //   qDebug() << "showMotorData";
}


void ShowPage::on_Show_Go_Button_clicked()
{

    for(int m=0;m<8;m++){
        mb->at(m)->setNowPosition(0);
        if(mb->at(m)->getNowPosition()<mb->at(m)->getDesTination()){
            interval_data[m] = (mb->at(m)->getDesTination() - mb->at(m)->getNowPosition())/10;
        }else{
        }
    }

//    if(m_thread->isRunning())
//    {
//        return;
//    }
//    m_thread->start();
    show_heart.setInterval(100);
    show_heart.start();
}


void ShowPage::on_Show_SetMaxPos_button_clicked(){
    ui->Show_SetDes_Slider->setValue(ui->Show_SetMaxPos_spinBox->value());
    ui->Show_SetDes_spinBox->setValue(ui->Show_SetMaxPos_spinBox->value());
    int i= getMotorBlockIndex();
    mb->at(i)->setMaxPosition(ui->Show_SetMaxPos_spinBox->value());//不確定要不要存到cue中
//    get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[i]->set_des(value);
}

void ShowPage::on_Show_SetMinPos_button_clicked()
{
    ui->Show_SetDes_Slider->setValue(ui->Show_SetMinPos_spinBox->value());
    ui->Show_SetDes_spinBox->setValue(ui->Show_SetMinPos_spinBox->value());
    int i= getMotorBlockIndex();
    mb->at(i)->setMinPosition(ui->Show_SetMinPos_spinBox->value());//不確定要不要存到cue中
//    get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[i]->set_des(value);
}

void ShowPage::on_Show_AllMin_Button_clicked()
{
    QString t = "t1jgf\nt2jgf\nt3jgf\nt4jgf\n";
    emit write_all_motors_max(t.toLocal8Bit(),4);
//    qDebug() << "on_Show_AllMin_Button_clicked ";
}

void ShowPage::on_Show_AdvancedSetting_Button_clicked()
{
    for(int m=0;m<mb->size();m++){
        mb->at(m)->setDestination(ui->Show_SetDes_spinBox->value());
        mb->at(m)->setSpeed(ui->Show_SpeedInput_spinBox->value());
        mb->at(m)->setAcceleration(ui->Show_AcceInput_spinBox->value());
        get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[m]->set_des(ui->Show_SetDes_spinBox->value());
        get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[m]->set_speed(ui->Show_SpeedInput_spinBox->value());
        get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[m]->set_acce(ui->Show_AcceInput_spinBox->value());
    }

}

void ShowPage::on_Show_Stop_Button_clicked()
{
    show_heart.stop();
}
