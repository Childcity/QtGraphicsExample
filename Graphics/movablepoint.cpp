#include "movablepoint.h"

#include <QPainter>

MovablePoint::MovablePoint(int radius, Qt::GlobalColor color, QString label, QGraphicsItem *parent)
    : QObject()
    , QGraphicsEllipseItem(parent)
    , color_(color)
    , label_(label)
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

QRectF MovablePoint::boundingRect() const
{
    QRectF rect = QGraphicsEllipseItem::boundingRect();
    return QRectF(rect.topLeft().x() - 10, rect.topLeft().y() - 10,
                  rect.width() + 10, rect.height() + 10);
}

void MovablePoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsEllipseItem::paint(painter, option, widget);
    painter->drawText(boundingRect().center() + QPoint(7,10), label_);    // Draw you text
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
