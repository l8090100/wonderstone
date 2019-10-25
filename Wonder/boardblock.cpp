
#include <QtWidgets>

#include "boardblock.h"
#include "showpage.h"

BlockMotor::BlockMotor(QWidget *parent)
    : QGroupBox(parent), color(Qt::lightGray), dragOver(false)
{
    Jog_P_B  =  new QPushButton();
    Jog_P_B->setText("^");
    Jog_P_B->setMaximumHeight(50);
    Jog_P_B->setMaximumWidth(50);
    Jog_N_B = new QPushButton();
    Jog_N_B->setText("v");
    Jog_N_B->setMaximumHeight(50);
    Jog_N_B->setMaximumWidth(50);
    Name_L = new QLabel();
    QBoxLayout *blockLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    blockLayout->addWidget(Jog_P_B);
    blockLayout->addWidget(Name_L);
    blockLayout->addWidget(Jog_N_B);
    addAction(new QAction(tr("&CUE"), this));
        //设置contextMenuPolicy属性值为 '以Actions为弹出菜单的菜单项组成菜单
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setLayout(blockLayout);
    setAcceptDrops(true);
}
//! [0]

//! [1]
void BlockMotor::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasColor()) {
        event->setAccepted(true);
        dragOver = true;
        update();
    } else {
        event->setAccepted(false);
    }
}
//! [1]

//! [2]
void BlockMotor::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    dragOver = false;
    update();
}
//! [2]

//! [3]
void BlockMotor::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    dragOver = false;
    if (event->mimeData()->hasColor())
        color = qvariant_cast<QColor>(event->mimeData()->colorData());
    update();
}
//! [3]

BlockCue::BlockCue(QWidget *parent)
    : QGroupBox(parent), color(Qt::lightGray), dragOver(false)
{
    Go_B  =  new QPushButton();
    Name_L = new QLabel();
    Go_B->setMinimumHeight(50);
    Go_B->setMinimumWidth(50);
    QBoxLayout *blockLayout = new QBoxLayout(QBoxLayout::TopToBottom);
//    blockLayout->addWidget(Name_L);
    blockLayout->addWidget(Go_B);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(showContextmenu(const QPoint&)));//this是datatable所在窗口
    cmenu = NULL;

    setLayout(blockLayout);
    setAcceptDrops(true);

}

void BlockCue::set_name(QString name)
{
    this->Go_B->setText(name);
}
void BlockCue::showContextmenu(const QPoint&)
{
    if(cmenu)//保证同时只存在一个menu，及时释放内存
        {
            delete cmenu;
            cmenu = NULL;
        }
        QMenu *cmenu = new QMenu();

        for(int c=0;c<ShowPage::m_model->CueList.size();c++){
             QAction *action = new QAction(ShowPage::m_model->CueList.at(c)->get_cueName());
             cmenu->addAction(action);
             connect(action, SIGNAL(triggered()), this, SLOT(showCueData()));
        }



        cmenu->exec(QCursor::pos());//在当前鼠标位置显示
        //cmenu->exec(pos)是在viewport显示
}

void BlockCue::showCueData()
{
   qDebug()<<"ok";
}
BoardBlock::BoardBlock(QWidget *parent)
    : QGroupBox(parent), color(Qt::lightGray), dragOver(false)
{
    Func_B  =  new QPushButton();
    Func_B->setMaximumHeight(80);
    Func_B->setMaximumWidth(80);
    QBoxLayout *blockLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    blockLayout->addWidget(Func_B);
    setLayout(blockLayout);
    setAcceptDrops(true);

}
