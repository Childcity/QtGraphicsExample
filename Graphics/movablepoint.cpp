#include "movablepoint.h"

#include <QDateTime>
#include <QPainter>

MovablePoint::MovablePoint(int radius, Qt::GlobalColor color, QString label, QGraphicsItem *parent)
    : QObject()
    , QGraphicsEllipseItem(parent)
    , color_(color)
    , label_(label)
{
    setRect(QRectF(-radius, -radius, 2*radius, 2*radius));

//    setAcceptHoverEvents(true);
//    setAcceptTouchEvents(true);
    //setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setBrush(QBrush(color_, Qt::BrushStyle::SolidPattern));
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges,true);
}

MovablePoint *MovablePoint::setPos(const QPointF &pos)
{
    QGraphicsEllipseItem::setPos(pos);
    return this;
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
QDateTime lastClick_;
void MovablePoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if((QDateTime::currentMSecsSinceEpoch() - lastClick_.toMSecsSinceEpoch()) < 350){
        emit doubleClicked(pos());
    }

    lastClick_ = QDateTime::currentDateTime();

    if (event->button() == Qt::MouseButton::LeftButton) {
        setBrush(QBrush(color_, Qt::BrushStyle::CrossPattern));
        QGraphicsEllipseItem::mousePressEvent(event);
        event->accept();
        return;
    }
    event->ignore();
}

void MovablePoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton) {
        setBrush(QBrush(color_, Qt::BrushStyle::SolidPattern));
        QGraphicsEllipseItem::mouseReleaseEvent(event);
        event->accept();
        return;
    }
    event->ignore();
}

MovablePoint::~MovablePoint() {}
