#include "cuedata.h"
#include <QDebug>

CueData::CueData(bool &used,QString &name,
        int &delay,int &dmx,
        int &conti)
    :   _cueUsed(used) ,
        _cueName(name),
        _cueDelay(delay) ,
        _dmx(dmx) ,
        _cueContinue(conti)
{

}
CueData::CueData()
{
    for(int m=0;m<8;m++){
        MCue[m] = new MotorCue;
        MCue[m]->set_used(m%2);
        MCue[m]->set_nowPos((m+1)*(m+1));
        MCue[m]->set_des((m+1)*(m+1));
        MCue[m]->set_acce((m+1)*(m+1));
        MCue[m]->set_speed((m+1)*(m+1));
        MCue[m]->set_delay((m+1)*(m+1));
        MCue[m]->set_cont((m+1)*(m+1));
    }
}

void CueData::set_cueUsed(bool used)
{
    this->_cueUsed = used;
}

void CueData::set_cueName(QString name)
{
    this->_cueName = name;
}
void CueData::set_cueDelay(int delay)
{
    this->_cueDelay = delay;
}
void CueData::set_cueDmxChannel(int ch)
{
    this->_dmx = ch;
}
void CueData::set_cueContinue(int conti)
{
    this->_cueContinue = conti;
}
bool CueData::get_cueUsed()
{
    return this->_cueUsed;
}
QString CueData::get_cueName()
{
    return this->_cueName;
}
int CueData::get_cueDelay()
{
    return this->_cueDelay;
}
int CueData::get_cueDmxChannel()
{
    return this->_dmx;
}

int CueData::get_cueContinue()
{
    return this->_cueContinue;
}

