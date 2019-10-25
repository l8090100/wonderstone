#ifndef ARTNETDATA_H
#define ARTNETDATA_H
#include "QString"
#include <QVariant>


class Artnetdata
{
public:
    Artnetdata();
public:
    void set_ID(int id);
    void set_function(QString func);
    void set_channel(int channel);
    void set_used(bool used);

    int get_ID();
    QString get_function();
    int get_channel();
    bool get_used();
private:
    int _ID;
    QString _function;
    int _channel;
    bool _used;

};
#endif // ARTNETDATA_H
