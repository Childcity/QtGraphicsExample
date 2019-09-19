#ifndef GASKETROTATEPOINT_H
#define GASKETROTATEPOINT_H

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>



class GasketRotatePoint : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
signals:
    void positionChanged(const QPointF &pos);

public:
    explicit GasketRotatePoint(QGraphicsItem *parent = nullptr);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    virtual ~GasketRotatePoint() override;
};

#endif // GASKETROTATEPOINT_H
