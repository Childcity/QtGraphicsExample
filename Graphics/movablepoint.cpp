#include "movablepoint.h"

MovablePoint::MovablePoint(QGraphicsItem *parent)
    : QObject(), QGraphicsEllipseItem(parent)
{
    setRect(QRectF(-10, -10, 20, 20));

    setAcceptHoverEvents(true);
    setAcceptTouchEvents(true);
    //setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setBrush(QBrush(Qt::blue, Qt::BrushStyle::SolidPattern));
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges,true);
}

QVariant MovablePoint::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{

    if (change == QGraphicsItem::ItemPositionChange){
        emit positionChanged(value.toPointF());
    }

    return QGraphicsItem::itemChange(change, value);

}

void MovablePoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        setBrush(QBrush(Qt::blue, Qt::BrushStyle::FDiagPattern));
        QGraphicsItem::mousePressEvent(event);
        event->accept();
        return;
    }
    event->ignore();
}

void MovablePoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        setBrush(QBrush(Qt::blue, Qt::BrushStyle::SolidPattern));
        QGraphicsItem::mouseReleaseEvent(event);
        event->accept();
        return;
    }
    event->ignore();
}

MovablePoint::~MovablePoint() {}
