#ifndef Plane_H
#define Plane_H

#include "graphicsitembase.h"
#include "transformation.h"

#include <QChart>
#include <QGraphicsItem>

using namespace QtCharts;

class Plane : public GraphicsItemBase {

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public:
    Plane(QChart *chart, Transformation *transformation);

    ~Plane() override;

    QRectF boundingRect() const override;

    void redraw() override;

    QPointF mauseP;

private:
    void transformateDatail() override;

    void drawPlane(QPainter *painter);
};

#endif // Plane_H
