#ifndef MODESETTINGDATA_H
#define MODESETTINGDATA_H
#include "QString"

class ModeSettingData
{
public:
    ModeSettingData();
public:
    void set_ID(int id);
    void set_name(QString name);
    void set_speed(int speed);
    void set_acce(int acce);
    void set_ULM(int ulm);
    void set_LLM(int llm);

    int get_ID();
    QString get_name();
    int get_speed();
    int get_acce();
    int get_ULM();
    int get_LLM();
private:
    int _ID;
    QString _name;
    int _speed;
    int _acce;
    int _ULM;
    int _LLM;
};

#endif // MODESETTINGDATA_H
