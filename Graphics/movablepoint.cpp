#include "movablepoint.h"

MovablePoint::MovablePoint(int radius, Qt::GlobalColor color, QGraphicsItem *parent)
    : QObject()
    , QGraphicsEllipseItem(parent)
    , color_(color)
{
    setRect(QRectF(-radius, -radius, 2*radius, 2*radius));

    setAcceptHoverEvents(true);
    setAcceptTouchEvents(true);
    //setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setBrush(QBrush(color_, Qt::BrushStyle::SolidPattern));
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
        setBrush(QBrush(color_, Qt::BrushStyle::CrossPattern));
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
        setBrush(QBrush(color_, Qt::BrushStyle::SolidPattern));
        QGraphicsItem::mouseReleaseEvent(event);
        event->accept();
        return;
    }
    event->ignore();
}

MovablePoint::~MovablePoint() {}
