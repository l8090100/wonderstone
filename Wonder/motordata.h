#ifndef MOTORDATA_H
#define MOTORDATA_H

#include "QString"


class MotorData
{

private:
    int id;
    bool used = true;
    QString motorName;
    int minPosition = 0;
    int maxPosition = 100000;
    int minSpeed = 0;
    int maxSpeed = 1000;
    int minAcceleration = 0;
    int maxAcceleration =1000;
    int autoSpeed = 100;
    int homeSpeed = 50;
    int manualSpeed = 100;
    int dmxChannel = 0;

    bool reverse = false;

public:
    MotorData(bool &used,
              QString &name,
              int &minp, int &maxp,
              int &mins, int &maxs,
              int &minacce,int &maxacce,
              int &aspeed,int &hspeed,int &mspeed,
              int &ch, int rev);


    void set_id(int id);
    void set_used(bool used);
    void set_motorName(QString name);
    void set_minPosition(int minp);
    void set_maxPosition(int maxp);
    void set_minSpeed(int mins);
    void set_maxSpeed(int maxs);
    void set_minAcceleration(int minacce);
    void set_maxAcceleration(int maxacce);
    void set_autoSpeed(int aspeed);
    void set_home_Speed(int hspeed);
    void set_manualSpeed(int mspeed);
    void set_dmxChannel(int ch);
    void set_reverse(bool rev);

    void get_used();
    void get_motorName();
    void get_id();
    void get_minPosition();
    void get_maxPosition();
    void get_minSpeed();
    void get_maxSpeed();
    void get_minAcceleration();
    void get_maxAcceleration();
    void get_autoSpeed();
    void get_home_Speed();
    void get_manualSpeed();
    void get_dmxChannel();
    void get_reverse();




};



#endif // MOTORDATA_H
