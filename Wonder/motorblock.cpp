#include <QtWidgets>
#include "showpage.h"
#include "ui_showpage.h"
#include "motorblock.h"
#include "cuedata.h"
#include "showpage.h"


MotorBlock::MotorBlock( QWidget *parent)
    : QGroupBox(parent)
{
    board_motor = new BlockMotor;
    Tab_B =  new QPushButton();
    Tab_B->setText("T_Motor");
    Mode_B = new QPushButton();
    Mode_B->setText("M");
    Mode_B->setCheckable(true);
    connect(Mode_B, SIGNAL(clicked()), this, SLOT(setMode()));

    Used_B = new QPushButton();
    Used_B->setText("USED");
    Used_B->setCheckable(true);
    connect(Used_B, SIGNAL(clicked()), this, SLOT(toggleButton_SetUsed()));

    Manual_Minus_B = new QPushButton();
    Manual_Minus_B->setText("<<");
    connect(Manual_Minus_B, SIGNAL(clicked()), this, SLOT(JGR()));

    Manual_Enable_B = new QPushButton();
    Manual_Enable_B->setText("O");
    Manual_Enable_B->setCheckable(true);
    connect(Manual_Enable_B, SIGNAL(clicked()), this, SLOT(JG0()));


    Manual_Plus_B = new QPushButton();
    Manual_Plus_B->setText(">>");
    connect(Manual_Plus_B, SIGNAL(clicked()), this, SLOT(JGF()));


    Name_L = new QLabel("name");
    NowPosition_L = new QLabel("NowPos");
    Destination_L = new QLabel("DES");
    Speed_L = new QLabel("Speed");
    Acceleration_L = new QLabel("ACCE");
    Delay_L = new QLabel("DEL");
    Continue_L = new QLabel("CON");
    Situation_L = new QLabel("SIT");

    blockLayout = new QBoxLayout(QBoxLayout::LeftToRight);

    blockLayout->addWidget(Mode_B);
    blockLayout->addWidget(Used_B);
    blockLayout->addWidget(Name_L);
    blockLayout->addWidget(NowPosition_L);
    blockLayout->addWidget(Destination_L);
    blockLayout->addWidget(Speed_L);
    blockLayout->addWidget(Acceleration_L);
    blockLayout->addWidget(Delay_L);
    blockLayout->addWidget(Continue_L);
    blockLayout->addWidget(Situation_L);
    blockLayout->addWidget(Manual_Minus_B);
    blockLayout->addWidget(Manual_Enable_B);
    blockLayout->addWidget(Manual_Plus_B);
    setLayout(blockLayout);


}
//Setter
void MotorBlock::setID(int id)
{
    this->M_id = id;
}

void MotorBlock::setMode()
{
    bool mode = Mode_B->isChecked();
    this->M_mode = mode;
    QString s = QString::number(mode);
    if(mode==true){
        Mode_B->setText("A");
    }else{
        Mode_B->setText("M");
    }
    ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[this->M_id]->set_mode(this->M_mode);
}

void MotorBlock::toggleButton_SetUsed()
{
    bool used = Used_B->isChecked();
    ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[this->M_id]->set_used(used);
    this->M_used = used;
    if(used==true){
        Used_B->setText("O");
    }else{
        Used_B->setText("X");
    }

}

void MotorBlock::JGF()
{
    QString id = QString::number(M_id+1);
    QString data = "t"+id+"JGF\n";
    emit write_motor(data.toLocal8Bit());
}

void MotorBlock::JG0()
{
    QString id = QString::number(M_id+1);
    QString data = "t"+id+"JG0\n";
    emit write_motor(data.toLocal8Bit());
}

void MotorBlock::JGR()
{
    QString id = QString::number(M_id+1);
    QString data = "t"+id+"JGR\n";
    emit write_motor(data.toLocal8Bit());
}

void MotorBlock::setUsed(bool used)
{ 
    QString s = QString::number(used);
    Used_B->setChecked(used);
    if(used==true){
        Used_B->setText("O");
    }else{
        Used_B->setText("X");
    }
    this->M_used = used;
}

void MotorBlock::setName(QString name)
{
    Name_L->setText(name);
    this->M_name = name;
}

void MotorBlock::setNowPosition(int val)
{
    setNumberToLabel(NowPosition_L, val);
    this->M_nowPos = val;
}

void MotorBlock::setDestination(int val)
{
    setNumberToLabel(Destination_L, val);
    this->M_des = val;
}

void MotorBlock::setSpeed(int val)
{
    setNumberToLabel(Speed_L, val);
    this->M_speed = val;

}

void MotorBlock::setAcceleration(int val)
{
    setNumberToLabel(Acceleration_L, val);
    this->M_acce = val;
}

void MotorBlock::setDelay(int val)
{
    setNumberToLabel(Delay_L, val);
    this->M_delay = val;
}

void MotorBlock::setContinue(int val)
{
    setNumberToLabel(Continue_L, val);
    this->M_conti = val;
}

void MotorBlock::setSituation(QString situation)
{
    Situation_L->setText(situation);
    this->M_situation = situation;
}

void MotorBlock::setMinPosition(int val)
{
     this->M_minPosition = val;
}

void MotorBlock::setMaxPosition(int val)
{
     this->M_maxPosition = val;
}

void MotorBlock::setMinSpeed(int val)
{
     this->M_minSpeed = val;
}

void MotorBlock::setMaxSpeed(int val)
{
     this->M_maxSpeed = val;
}

void MotorBlock::setMinAcceleration(int val)
{
     this->M_minAcceleration = val;
}

void MotorBlock::setMaxAcceleration(int val)
{
     this->M_maxAcceleration = val;
}

void MotorBlock::setAutoSpeed(int val)
{
     this->M_autoSpeed = val;
}

void MotorBlock::setHomeSpeed(int val)
{
     this->M_homeSpeed = val;
}

void MotorBlock::setManualSpeed(int val)
{
     this->M_manualSpeed = val;
}

void MotorBlock::setDMXChannel(int val)
{
     this->M_dmxChannel = val;
}

void MotorBlock::setReverse(bool rev)
{
    this->M_reverse = rev;
}

int MotorBlock::getID()
{
    return this->M_id;
}

//Getter
bool MotorBlock::getMode()
{
    return this->M_mode;
}

bool MotorBlock::getUsed()
{
    return this->M_used;
}

QString MotorBlock::getName()
{
    return this->M_name;
}

int MotorBlock::getNowPosition()
{
     return this->M_nowPos;
}

int MotorBlock::getDesTination()
{
     return this->M_des;
}

int MotorBlock::getSpeed()
{
     return this->M_speed;
}

int MotorBlock::getAcceleratiob()
{
     return this->M_acce;
}

int MotorBlock::getDelay()
{
     return this->M_delay;
}

int MotorBlock::getContinue()
{
     return this->M_conti;
}

QString MotorBlock::getSituation()
{
    return this->M_situation;
}

int MotorBlock::getMinPosition()
{
    return this->M_minPosition;
}

int MotorBlock::getMaxPosition()
{
    return this->M_maxPosition;
}

int MotorBlock::getMinSpeed()
{
    return this->M_minSpeed;
}

int MotorBlock::getMaxSpeed()
{
    return this->M_maxSpeed;
}

int MotorBlock::getMinAcceleration()
{
    return this->M_minAcceleration;
}

int MotorBlock::getMaxAcceleration()
{
    return this->M_maxAcceleration;
}

int MotorBlock::getAutoSpeed()
{
    return this->M_autoSpeed;
}

int MotorBlock::getHomeSpeed()
{
    return this->M_homeSpeed;
}

int MotorBlock::getManualSpeed()
{
    return this->M_manualSpeed;
}

int MotorBlock::getDMXChannel()
{
    return this->M_dmxChannel;
}

bool MotorBlock::getReverse()
{
    return this->M_reverse;
}

//Function
void MotorBlock::setNumberToLabel(QLabel *label,int val)
{
    QString text = QString::number(val);
    label->setText(text);
}

void MotorBlock::mousePressEvent(QMouseEvent *ev)
{
    QString text = Name_L->text();
    ShowPage::selectIndexName = text;
//    qDebug() << text;
    emit MotorBlock_Mouse_Pressed(this->M_id,ShowPage::get_m_model()->CueList.at(ShowPage::get_cueTableSelectRow())->MCue[this->M_id]);
}

void MotorBlock::setCue(){

}






