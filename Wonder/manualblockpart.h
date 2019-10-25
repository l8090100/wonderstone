#ifndef MANUALBLOCKPART_H
#define MANUALBLOCKPART_H

#include <QGraphicsItem>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QParallelAnimationGroup;
QT_END_NAMESPACE

//! [0]
class ManualBlockPart : public QGraphicsObject
{
public:
    ManualBlockPart(QGraphicsItem *parent = 0);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;

    QColor color;
    bool dragOver;
};
//! [0]

//! [1]
class ManualMotor : public ManualBlockPart
{
public:
    ManualMotor(QGraphicsItem *parent = 0);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;

private:
    QPixmap pixmap;
};
//! [1]

//! [2]
class ManualCue : public ManualBlockPart
{
public:
    ManualCue(QGraphicsItem *parent = 0);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
};
//! [2]

//! [3]
class ManualFunc : public ManualBlockPart
{
public:
    ManualFunc(QGraphicsItem *parent = 0);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
};
//! [3]

//! [4]
class ManualBlock : public ManualBlockPart
{
public:
    ManualBlock(QGraphicsItem *parent = 0);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
};
//! [4]
//!
#endif // MANUALBLOCKPART_H
