#ifndef MOTORCUE_H
#define MOTORCUE_H

#include "QString"

class MotorCue
{
    bool MC_mode = true;
    bool MC_used = true;
    QString MC_name = "motor";
    int MC_nowPos = 0;
    int MC_des = 0;
    int MC_speed = 456;
    int MC_acce = 50;
    int MC_delay = 0;
    int MC_conti = 0;

public:
    MotorCue(bool &mode, bool &used,
             QString &name,
             int &nowPos,int &des,
             int &speed,int &acce,
             int &delay, int &conti);
    MotorCue();
     void set_mode(bool mode);
     void set_used(bool used);
     void set_name(QString name);
     void set_nowPos(int nowp);
     void set_des(int des);
     void set_speed(int speed);
     void set_acce(int acce);
     void set_delay(int delay);
     void set_cont(int cont);

     bool get_mode();
     bool get_used();
     QString get_name();
     int get_nowPos();
     int get_des();
     int get_speed();
     int get_acce();
     int get_delay();
     int get_conti();

};

#endif // MOTORCUE_H
