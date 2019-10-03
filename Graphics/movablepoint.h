#ifndef MOVABLEPOINT_H
#define MOVABLEPOINT_H

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>



class MovablePoint : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT

private:
	Qt::GlobalColor color_;
    QString label_;

signals:
    void positionChanged(const QPointF &pos);

public:
	using Ptr = MovablePoint*;

    explicit MovablePoint(int radius, Qt::GlobalColor color, QString label, QGraphicsItem *parent = nullptr);

	virtual ~MovablePoint() override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MOVABLEPOINT_H
