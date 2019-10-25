#include "motorsettingdata.h"

MotorSettingData::MotorSettingData()
{

}

void MotorSettingData::set_mode(int mode){this->_mode = mode;}
void MotorSettingData::set_name(QString name){this->_name = name;}
void MotorSettingData::set_reverse(bool rev){this->_reverse = rev;}
void MotorSettingData::set_minPosition(int val){this->_minPosition = val;}
void MotorSettingData::set_maxPosition(int val){this->_maxPosition = val;}
void MotorSettingData::set_minSpeed(int val){this->_minSpeed = val;}
void MotorSettingData::set_maxSpeed(int val){this->_maxSpeed = val;}
void MotorSettingData::set_minAcce(int val){this->_minAcce = val;}
void MotorSettingData::set_maxAcce(int val){this->_maxAcce = val;}
void MotorSettingData::set_autoSpeed(int val){this->_autoSpeed = val;}
void MotorSettingData::set_homeSpeed(int val){this->_homeSpeed = val;}
void MotorSettingData::set_manualSpeed(int val){this->_manualSpeed = val;}
void MotorSettingData::set_DMX_fixture(int val){this->_DMX_fixture = val;}

int MotorSettingData::get_mode(){return this->_mode;}
QString MotorSettingData::get_name(){return this->_name;}
bool MotorSettingData::get_reverse(){return this->_reverse;}
int MotorSettingData::get_minPosition(){return this->_minPosition;}
int MotorSettingData::get_maxPosition(){return this->_maxPosition;}
int MotorSettingData::get_minSpeed(){return this->_minSpeed;}
int MotorSettingData::get_maxSpeed(){return this->_maxSpeed;}
int MotorSettingData::get_minAcce(){return this->_minAcce;}
int MotorSettingData::get_maxAcce(){return this->_maxAcce;}
int MotorSettingData::get_autoSpeed(){return this->_autoSpeed;}
int MotorSettingData::get_homeSpeed(){return this->_homeSpeed;}
int MotorSettingData::get_manualSpeed(){return this->_manualSpeed;}
int MotorSettingData::get_DMX_fixture(){return this->_DMX_fixture;}
