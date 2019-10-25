#ifndef SYSTEMSETTINGDATA_H
#define SYSTEMSETTINGDATA_H
#include "QString"
class SystemSettingData
{
public:
    SystemSettingData();
public:
   void  set_ID(int id);
   void  set_name(QString name);
   void  set_ULM_used(bool used);
   void  set_LLM_used(bool used);
   void  set_Mode(int mode);

    int get_ID();
    QString get_name();
    bool get_ULM_used();
    bool get_LLM_used();
    int get_Mode();

private:
    int _ID;
    QString _name;
    bool _ULM_used;
    bool _LLM_used;
    int _Mode;


};

#endif // SYSTEMSETTINGDATA_H
