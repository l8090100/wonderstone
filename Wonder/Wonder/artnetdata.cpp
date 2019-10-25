#include "artnetdata.h"
#include <QDebug>



Artnetdata::Artnetdata()
{

}

void Artnetdata::set_ID(int id)
{
    this->_ID = id;
}
void Artnetdata::set_function(QString func)
{
    this->_function = func;
}
void Artnetdata::set_channel(int chan)
{
    this->_channel = chan;
}
void Artnetdata::set_used(bool used)
{
    this->_used = used;
}

int Artnetdata::get_ID()
{
    return this->_ID;
}
QString Artnetdata::get_function()
{
    return this->_function;
}
int Artnetdata::get_channel()
{
    return this->_channel;
}
bool Artnetdata::get_used()
{
    return this->_used;
}
