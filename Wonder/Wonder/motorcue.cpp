#include "motorcue.h"

MotorCue::MotorCue(bool &mode, bool &used,
                   QString &name,
                   int &nowPos,int &des,
                   int &speed,int &acce,
                   int &delay, int &conti)
            :MC_mode(mode),MC_used(used),
             MC_name(name),
             MC_nowPos(nowPos),MC_des(des),
             MC_speed(speed),MC_acce(acce),
             MC_delay(delay),MC_conti(conti)
{

}

MotorCue::MotorCue()
{

}

void MotorCue::set_mode(bool mode)
{
    this->MC_mode = mode;
}
void MotorCue::set_used(bool used)
{
    this->MC_used = used;
}
void MotorCue::set_name(QString name)
{
    this->MC_name = name;
}
void MotorCue::set_nowPos(int nowp)
{
    this->MC_nowPos = nowp;
}
void MotorCue::set_des(int des)
{
    this->MC_des = des;
}
void MotorCue::set_speed(int speed)
{
    this->MC_speed = speed;
}
void MotorCue::set_acce(int acce)
{
    this->MC_acce = acce;
}
void MotorCue::set_delay(int delay)
{
    this->MC_delay = delay;
}
void MotorCue::set_cont(int cont)
{
    this->MC_conti = cont;
}

bool MotorCue::get_mode()
{
    return this->MC_mode;
}
bool MotorCue::get_used()
{
    return  this->MC_used;
}
QString MotorCue::get_name()
{
    return this->MC_name;
}
int MotorCue::get_nowPos()
{
    return this->MC_nowPos;
}
int MotorCue::get_des()
{
    return this->MC_des;
}
int MotorCue::get_speed()
{
    return this->MC_speed;
}
int MotorCue::get_acce()
{
    return this->MC_acce;
}
int MotorCue::get_delay()
{
    return this->MC_delay;
}
int MotorCue::get_conti()
{
    return this->MC_conti;
}
