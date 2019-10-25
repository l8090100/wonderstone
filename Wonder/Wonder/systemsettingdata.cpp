#include "systemsettingdata.h"

SystemSettingData::SystemSettingData()
{

}

void  SystemSettingData::set_ID(int id){this->_ID = id;}
void  SystemSettingData::set_name(QString name){this->_name = name;}
void  SystemSettingData::set_ULM_used(bool used){this->_ULM_used = used;}
void  SystemSettingData::set_LLM_used(bool used){this->_LLM_used = used;}
void  SystemSettingData::set_Mode(int mode){this->_Mode = mode;}

int SystemSettingData::get_ID(){return this->_ID;}
QString SystemSettingData::get_name(){return this->_name;}
bool SystemSettingData::get_ULM_used(){return this->_ULM_used;}
bool SystemSettingData::get_LLM_used(){return this->_LLM_used;}
int SystemSettingData::get_Mode(){return this->_Mode;}

