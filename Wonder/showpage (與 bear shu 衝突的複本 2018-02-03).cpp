#include "showpage.h"
#include "ui_showpage.h"
#include "motorblock.h"
#include <QObject>
#include <QDebug>

int ShowPage::cueTableSelectRow = 0;
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
//        get_m_model()->importDataToModel();
//        get_m_model()->importDataToModel();
//        get_m_model()->importDataToModel();
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
}

void ShowPage::on_Show_SetMaxPos_spinBox_valueChanged(int arg1)
{
     int i= getMotorBlockIndex();
     mb->at(i)->setMaxPosition(arg1);
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
        for (int c = 0; c < count; ++c) {
            CueData* cue = new CueData;
            cue->set_cueUsed(true);
            cue->set_cueName("Q");
            cue->set_cueDelay(row+100);
            cue->set_cueDmxChannel(c);
            cue->set_cueContinue(c);
            get_m_model()->CueList.insert(row,cue);
        }
        ui->Show_CueListTable_tableView->selectRow(row);
    }else{
        row = ui->Show_CueListTable_tableView->currentIndex().row();
        get_m_model()->insertRows(row+1,count, QModelIndex());
        for (int c = 0; c < count; ++c) {
            CueData* cue = new CueData;
            cue->set_cueUsed(true);
            cue->set_cueName("Q");
            cue->set_cueDelay(row+100);
            cue->set_cueDmxChannel(c);
            cue->set_cueContinue(c);
            get_m_model()->CueList.insert(row,cue);
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
            qDebug() << i;

    }

}

void ShowPage::on_Show_DeleteCue_button_clicked()
{
    int row = ui->Show_CueListTable_tableView->currentIndex().row();
    int count = 1;
    get_m_model()->removeRows(row,count,QModelIndex());
    for (int c = 0; c < count; ++c) {
            get_m_model()->CueList.removeAt(row);
        }
     for (int i = 0; i <  get_m_model()->rowCount(); ++i) {
         get_m_model()->setData(get_m_model()->index(i,0),i);
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

}

