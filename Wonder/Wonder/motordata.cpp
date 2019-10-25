#include "motordata.h"

MotorData::MotorData(bool &used,
                     QString &name,
                     int &minp, int &maxp,
                     int &mins, int &maxs,
                     int &minacce,int &maxacce,
                     int &aspeed,int &hspeed,int &mspeed
                     ,int &ch, int rev)
                : used(used),
                  motorName(name),
                  minPosition(minp),
                  maxPosition(maxp),
                  minSpeed(mins),
                  maxSpeed(maxs),
                  minAcceleration(minacce),
                  maxAcceleration(maxacce),
                  autoSpeed(aspeed),
                  homeSpeed(hspeed),
                  manualSpeed(mspeed),
                  dmxChannel(ch),
                  reverse(rev)
{

}

void MotorData::set_id(int id)
{

}
void MotorData::set_used(bool used)
{

}
void MotorData::set_motorName(QString name)
{

}
void MotorData::set_minPosition(int minp)
{

}
void MotorData::set_maxPosition(int maxp)
{

}
void MotorData::set_minSpeed(int mins)
{

}
void MotorData::set_maxSpeed(int maxs)
{

}
void MotorData::set_minAcceleration(int minacce)
{

}
void MotorData::set_maxAcceleration(int maxacce)
{

}
void MotorData::set_autoSpeed(int aspeed)
{

}
void MotorData::set_home_Speed(int hspeed)
{

}
void MotorData::set_manualSpeed(int mspeed)
{

}
void MotorData::set_dmxChannel(int ch)
{

}
void MotorData::set_reverse(bool rev)
{

}

//getter

void MotorData::get_used()
{

}

void MotorData::get_motorName()
{

}
void MotorData::get_id()
{

}
void MotorData::get_minPosition()
{

}
void MotorData::get_maxPosition()
{

}
void MotorData::get_minSpeed()
{

}
void MotorData::get_maxSpeed()
{

}
void MotorData::get_minAcceleration()
{

}
void MotorData::get_maxAcceleration()
{

}
void MotorData::get_autoSpeed()
{

}
void MotorData::get_home_Speed()
{

}
void MotorData::get_manualSpeed()
{

}
void MotorData::get_dmxChannel()
{

}
void MotorData::get_reverse()
{

}
