#ifndef CUEDATA_H
#define CUEDATA_H
#include "QString"
#include <QListData>
#include <QAbstractListModel>
#include "motorcue.h"


class CueData
{
public:
    CueData(bool &used,QString &name,
            int &delay,int &dmx,
            int &conti);
    CueData();
public:

    void set_cueUsed(bool used);
    void set_cueName(QString name);
    void set_cueDelay(int delay);
    void set_cueDmxChannel(int ch);
    void set_cueContinue(int conti);

    bool get_cueUsed();
    QString get_cueName();
    int get_cueDelay();
    int get_cueDmxChannel();
    int get_cueContinue();

    MotorCue *MCue[8];

public:
    bool _cueUsed = true;
    QString _cueName = "cue";
    int _cueDelay = 0;
    int _dmx = 0;
    int _cueContinue = 0;

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
