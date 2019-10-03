#ifndef MOVABLEPOINT_H
#define MOVABLEPOINT_H

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>



class MovablePoint : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT

private:
	Qt::GlobalColor color_;

signals:
    void positionChanged(const QPointF &pos);

public:
	using Ptr = MovablePoint*;

	explicit MovablePoint(int radius, Qt::GlobalColor color, QGraphicsItem *parent = nullptr);

	virtual ~MovablePoint() override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MOVABLEPOINT_H
