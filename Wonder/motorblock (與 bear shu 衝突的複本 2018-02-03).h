#ifndef MOTORBLOCK_H
#define MOTORBLOCK_H

#include <QGroupBox>
#include <QWidget>
#include <QMouseEvent>
#include "cuedata.h"


QT_BEGIN_NAMESPACE
class QPushButton;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QSpinBox;
class QStackedWidget;

QT_END_NAMESPACE

//! [0]
class MotorBlock : public QGroupBox
{
    Q_OBJECT

public:
    MotorBlock(QWidget *parent = 0);

    void setID(int id);
    void setUsed(bool used);
    void setName(QString name);
    void setNowPosition(int val);
    void setDestination(int val);
    void setSpeed(int val);
    void setAcceleration(int val);
    void setDelay(int val);
    void setContinue(int val);
    void setSituation(QString situation);

    void setMinPosition(int val);
    void setMaxPosition(int val);
    void setMinSpeed(int val);
    void setMaxSpeed(int val);
    void setMinAcceleration(int val);
    void setMaxAcceleration(int val);
    void setAutoSpeed(int val);
    void setHomeSpeed(int val);
    void setManualSpeed(int val);
    void setDMXChannel(int val);
    void setReverse(bool rev);

    int getID();
    bool getMode();
    bool getUsed();
    QString getName();
    int getNowPosition();
    int getDesTination();
    int getSpeed();
    int getAcceleratiob();
    int getDelay();
    int getContinue();
    QString getSituation();

    int getMinPosition();
    int getMaxPosition();
    int getMinSpeed();
    int getMaxSpeed();
    int getMinAcceleration();
    int getMaxAcceleration();
    int getAutoSpeed();
    int getHomeSpeed();
    int getManualSpeed();
    int getDMXChannel();
    bool getReverse();

    void setNumberToLabel(QLabel *label,int val);

    void mousePressEvent(QMouseEvent *ev);

public:
    void addCue();
    void setCue();
    void deleteCue();




signals:
   // void valueChanged(int value);
    void MotorBlock_Mouse_Pressed(int,MotorCue*);

public slots:
   // void setValue(int value);
    void setMode();
    void toggleButton_SetUsed();


private:
    QPushButton *Tab_B;
    QPushButton *Mode_B;
    QPushButton *Used_B;
    QPushButton *Manual_Minus_B;
    QPushButton *Manual_Enable_B;
    QPushButton *Manual_Plus_B;
    QLabel  *Name_L;
    QLabel  *NowPosition_L;
    QLabel  *Destination_L;
    QLabel  *Speed_L;
    QLabel  *Acceleration_L;
    QLabel  *Delay_L;
    QLabel  *Continue_L;
    QLabel  *Situation_L;

private:
    int M_id;
    int M_minPosition = 0;
    int M_maxPosition = 100000;
    int M_minSpeed = 0;
    int M_maxSpeed = 1000;
    int M_minAcceleration = 0;
    int M_maxAcceleration =1000;
    int M_autoSpeed = 100;
    int M_homeSpeed = 50;
    int M_manualSpeed = 100;
    int M_dmxChannel = 0;

    bool M_mode;
    bool M_used;
    QString M_name;
    int M_nowPos;
    int M_des;
    int M_speed;
    int M_acce;
    int M_delay;
    int M_conti;
    QString M_situation;

    bool M_reverse = false;

private:
    QVector<CueData> *cue[100];


};
//! [0]

#endif
