#ifndef BOARDPAGE_H
#define BOARDPAGE_H

#include <QWidget>
#include "boardblock.h"


namespace Ui {
class BoardPage;
}

class BoardPage : public QWidget
{
    Q_OBJECT
public:
    explicit BoardPage(QWidget *parent = 0);
    ~BoardPage();
public:
    Ui::BoardPage *ui;
    static int cueBlockCount;

    static QList<BlockCue*> *cue_block;
public slots:
    void generateCueBlock(QString cueName);


};

#endif // BOARDPAGE_H
