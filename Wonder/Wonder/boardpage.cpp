#include "boardpage.h"
#include "ui_boardpage.h"
#include "manualblockpart.h"
#include <math.h>
#include "robot.h"
#include <QtWidgets>
#include <QDebug>
#include "showpage.h"


BoardPage::BoardPage(QWidget *parent): QWidget(parent),  ui(new Ui::BoardPage)
{
    ui->setupUi(this);
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(-300,-300,600,600);
    Robot *robot = new Robot;
    robot->setTransform(QTransform::fromScale(1.2, 1.2), true);
    robot->setPos(0, -20);
    scene->addItem(ShowPage::mb->at(0)->manual_b);
//! [1]
//! [2]
    QGraphicsView* view = new QGraphicsView(scene);
    ui->Board_verticalLayout->addWidget(view);
    qDebug() <<"add view in borad";
    view->setRenderHint(QPainter::Antialiasing);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setBackgroundBrush(QColor(230, 200, 167));
    view->setWindowTitle("Drag and Drop Robot");
    view->show();


};

BoardPage::~BoardPage()
{
    delete ui;
}
