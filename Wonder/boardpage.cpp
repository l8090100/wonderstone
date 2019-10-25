#include "boardpage.h"
#include "ui_boardpage.h"
#include "manualblockpart.h"
#include <math.h>
#include "robot.h"
#include "boardblock.h"
#include <QtWidgets>
#include <QDebug>
#include "showpage.h"

int BoardPage::cueBlockCount = 0;
QList<BlockCue*> *BoardPage::cue_block = new QList<BlockCue*>;
BoardPage::BoardPage(QWidget *parent): QWidget(parent),  ui(new Ui::BoardPage)
{
    ui->setupUi(this);
    int count =0;
    for(int c=0;c<5;c++){
        for(int r=0;r<4;r++){
            BlockCue *cblock = new BlockCue;
            cue_block->append(cblock);
            ui->Board_gridLayout->addWidget(cue_block->at(count),r,c);
            count++;
        }
    }
    count =0 ;
    int row = ui->Board_gridLayout->rowCount();
    for(int i=0;i<4;i++){
        ui->Board_gridLayout->addWidget(ShowPage::mb->at(i)->get_board_motor(),row,i,3,1);
    }

};

BoardPage::~BoardPage()
{
    delete ui;
}

void BoardPage::generateCueBlock(QString cueName)
{
//    cue_block->at(cueBlockCount)->Name_L->setText(cueName);
    cue_block->at(cueBlockCount)->set_name(cueName);
    cueBlockCount++;
}
