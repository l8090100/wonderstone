#include "modesettingdata.h"

ModeSettingData::ModeSettingData()
{

}

void ModeSettingData::set_ID(int id)
{
    this->_ID = id;
}

void ModeSettingData::set_name(QString name)
{
    this->_name = name;
}

void ModeSettingData::set_speed(int speed)
{
    this->_speed;
}

void ModeSettingData::set_acce(int acce)
{
    this->_acce = acce;
}

void ModeSettingData::set_ULM(int ulm)
{
    this->_ULM = ulm;
}

void ModeSettingData::set_LLM(int llm)
{
    this->_LLM = llm;
}

int ModeSettingData::get_ID()
{
    return this->_ID;
}

QString ModeSettingData::get_name()
{
    return this->_name;
}

int ModeSettingData::get_speed()
{
    return this->_speed;
}

int ModeSettingData::get_acce()
{
    return this->_acce;
}

int ModeSettingData::get_ULM()
{
    return this->_ULM;
}

int ModeSettingData::get_LLM()
{
    return this->_LLM;
}
