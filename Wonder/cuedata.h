#ifndef CUEDATA_H
#define CUEDATA_H
#include "QString"
#include <QListData>
#include <QAbstractListModel>
#include "motorcue.h"


class CueData
{
public:
    CueData(bool &used,int &number,QString &name,
            int &delay,int &dmx,
            bool &conti);
    CueData();
public:
    void set_cueNumber(int num);
    void set_cueUsed(bool used);
    void set_cueName(QString name);
    void set_cueDelay(int delay);
    void set_cueDmxChannel(int ch);
    void set_cueContinue(bool conti);

    int get_cueNumber();
    bool get_cueUsed();
    QString get_cueName();
    int get_cueDelay();
    int get_cueDmxChannel();
    int get_cueContinue();

    MotorCue *MCue[10];

public:
    int _cueNumber = 0;
    bool _cueUsed = true;
    QString _cueName = "cue";
    int _cueDelay = 0;
    int _dmx = 0;
    bool _cueContinue = true;

};



//class CueDataModel : public QAbstractListModel
//{
//    Q_OBJECT
//public:
//    CueDataModel(QObject *parent = 0);
//    void addCue(const CueData &cueData);
//    int rowCount(const QModelIndex & parent = QModelIndex()) const;
//private:
//    QList<CueData> m_cueDatas;

//};

#endif // CUEDATA_H
