#ifndef MOTORSETTINGDATA_H
#define MOTORSETTINGDATA_H
#include "QString"

class MotorSettingData
{
public:
    MotorSettingData();
public:
    void set_mode(int mode);
    void set_name(QString name);
    void set_reverse(bool rev);
    void set_minPosition(int val);
    void set_maxPosition(int val);
    void set_minSpeed(int val);
    void set_maxSpeed(int val);
    void set_minAcce(int val);
    void set_maxAcce(int val);
    void set_autoSpeed(int val);
    void set_homeSpeed(int val);
    void set_manualSpeed(int val);
    void set_DMX_fixture(int val);

    int get_mode();
    QString get_name();
    bool get_reverse();
    int get_minPosition();
    int get_maxPosition();
    int get_minSpeed();
    int get_maxSpeed();
    int get_minAcce();
    int get_maxAcce();
    int get_autoSpeed();
    int get_homeSpeed();
    int get_manualSpeed();
    int get_DMX_fixture();


private:
    int _mode;
    QString _name;
    bool _reverse;
    int _minPosition;
    int _maxPosition;
    int _minSpeed;
    int _maxSpeed;
    int _minAcce;
    int _maxAcce;
    int _autoSpeed;
    int _homeSpeed;
    int _manualSpeed;
    int _DMX_fixture;


};

#endif // MOTORSETTINGDATA_H
