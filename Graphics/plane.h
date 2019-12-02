#ifndef Plane_H
#define Plane_H

#include "graphicsitembase.h"
#include "movablepoint.h"
#include "transformation.h"

#include <QChart>
#include <QGraphicsItem>
#include <QTimeLine>

using namespace QtCharts;

class Plane: public QObject, public GraphicsItemBase {
private:
    constexpr static int animationFrameCount_ = 50;

    bool isTrianglesVisible_ = true;
    QList<MovablePoint *> triangles_;
    QList<MovablePoint *> catTriangles_;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent (QGraphicsSceneMouseEvent * event) override;

public:
    Plane(QChart *chart, Transformation *transformation);

    ~Plane() override;

    QRectF boundingRect() const override;

    void redraw() override;

    void animateTo(QString figureFilePath, bool isForwardAnimation)
    {
        QFile f("cat.bin");
        f.open(QIODevice::OpenModeFlag::ReadWrite);
        QDataStream strm(&f);
        int size;
        strm >> size;
        for (int i = 0; i < size; ++i) {
            QPointF mP;
            strm >>mP;
            catTriangles_ << createPlanePoint(mP);
        }
        f.close();

        QTimeLine *timeLine = new QTimeLine(2500, nullptr);
        timeLine->setFrameRange(0, animationFrameCount_);

        connect(timeLine, &QTimeLine::frameChanged, this, [=](int currFrame){
        });

        timeLine->start();
    }

    void setTrianglesVisible(bool isTrianglesVisible);

private:
    void transformateDatail() override;

    MovablePoint *createPlanePoint(const QPointF &point) {
        MovablePoint *mPoint = new MovablePoint(5, Qt::darkGray, "", this);
        return mPoint->setPos(point);
    }

    void createPlane();

    void drawPlane(QPainter *painter);
};

#endif // Plane_H
