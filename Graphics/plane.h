#ifndef Plane_H
#define Plane_H

#include "graphicsitembase.h"
#include "movablepoint.h"
#include "transformation.h"

#include <QChart>
#include <QGraphicsItem>
#include <QTimeLine>

using namespace QtCharts;

class Plane: public GraphicsItemBase {
private:
    constexpr static int animationFrameCount_ = 50;

    bool isTrianglesVisible_ = true;
    QList<MovablePoint *> triangles_;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent (QGraphicsSceneMouseEvent * event) override;

public:
    Plane(QChart *chart, Transformation *transformation);

    ~Plane() override;

    QRectF boundingRect() const override;

    void redraw() override;

    void animateTo(QString figureFilePath, bool isForwardAnimation);

    void setTrianglesVisible(bool isTrianglesVisible);

private:
    void transformateDatail() override;

    MovablePoint *createPlanePoint(const QPointF &point);

    void createPlane();

    void drawPlane(QPainter *painter);

    void clearTringle();
};

#endif // Plane_H
