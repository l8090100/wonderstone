#ifndef BOARDBLOCK_H

#include <QGraphicsItem>
#include <QGroupBox>
#include <QWidget>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QPushButton;
class QBoxLayout;
class QLabel;

class QParallelAnimationGroup;

class BlockMotor : public QGroupBox
{
    Q_OBJECT
public:
    BlockMotor(QWidget *parent = 0);
    void set_name(QString name);
    void set_p_hotkey(QString key);
    void set_n_hotkey(QString key);
    QString get_name();

public:
    QPushButton *Jog_P_B;
    QPushButton *Jog_N_B;
    QLabel  *Name_L;

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    QColor color;
    bool dragOver;
};

class BlockCue : public QGroupBox
{
    Q_OBJECT
public:
    BlockCue(QWidget *parent = 0);
    QPushButton *Go_B;
    QLabel  *Name_L;
    QMenu *cmenu;

    void set_name(QString name);
public  slots:
    void showContextmenu(const QPoint&);
    void showCueData();
protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) ;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) ;
    void dropEvent(QGraphicsSceneDragDropEvent *event) ;

    QColor color;
    bool dragOver;
};
//! [0]
//!
class BoardBlock : public QGroupBox
{
    Q_OBJECT
public:
    BoardBlock(QWidget *parent = 0);
public:
    QPushButton *Func_B;
protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    QColor color;
    bool dragOver;
//    QRectF boundingRect() const;
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
};

QT_END_NAMESPACE


#define BOARDBLOCK_H

#endif // BOARDBLOCK_H
