#ifndef Plane_H
#define Plane_H

#include "graphicsitembase.h"
#include "transformation.h"

#include <QChart>
#include <QGraphicsItem>

using namespace QtCharts;

class Plane: public GraphicsItemBase {
private:
    bool isTrianglesVisible_ = true;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent (QGraphicsSceneMouseEvent * event) override;

public:
    Plane(QChart *chart, Transformation *transformation);

    ~Plane() override;

    QRectF boundingRect() const override;

    void redraw() override;

    QPointF mauseP;

    void setTrianglesVisible(bool isTrianglesVisible);

private:
    void transformateDatail() override;

    void drawPlane(QPainter *painter);
};

#endif // Plane_H
