#include "plane.h"
#include "Basic/arc.h"

#include <QPainter>
#include <QPen>
#include <QDebug>
#include <qgraphicssceneevent.h>
#include <QGraphicsScene>

void Plane::redraw() {
    GraphicsItemBase::redraw();
    update();
}

void Plane::animateTo(QString figureFilePath, bool isForwardAnimation)
{
    if (! isForwardAnimation) {
        createPlane();
        return;
    }

    QList<QPointF> figureTrianglesPoints;
    QList<QPointF> currentTrianglesPoints;

    {
        QFile f(figureFilePath);
        if (! f.open(QIODevice::OpenModeFlag::ReadWrite)){
            qFatal("[%s] %s", figureFilePath.toLocal8Bit().constData(), f.errorString().toLocal8Bit().constData());
        }
        QDataStream strm(&f);
        int size;
        strm >> size;
        for (int i = 0; i < size; ++i) {
            QPointF p;
            strm >> p;
            figureTrianglesPoints << p;
        }
        f.close();
    }

    // save cuurent picture to currentTrianglesPoints
    for (const auto &movablePoint : triangles_) {
        currentTrianglesPoints << movablePoint->pos();
    }

    QTimeLine *timeLine = new QTimeLine(3000, scene());
    timeLine->setFrameRange(0, animationFrameCount_);


    scene()->connect(timeLine, &QTimeLine::frameChanged, scene(), [=]{
        for (int i = 0; i < currentTrianglesPoints.size()-1; ++i) {
            const auto deltaPoint = currentTrianglesPoints[i] - figureTrianglesPoints[i];
            const auto stepPoint = QPointF(deltaPoint.x()/animationFrameCount_,
                                           deltaPoint.y()/animationFrameCount_);

            triangles_[i]->setPos(triangles_[i]->pos() - stepPoint);
        }
    });

    timeLine->start();
}


Plane::Plane(QChart *chart, Transformation2D *transformation)
    : GraphicsItemBase (chart, transformation)
{
    createPlane();

//    QFile f("/home/childcity/cat.bin");
//    if (! f.open(QIODevice::OpenModeFlag::ReadWrite)){
//        qFatal("%s", f.errorString().toLocal8Bit().constData());
//    }
//    QDataStream strm(&f);
//    int size;
//    strm >> size;
//    for (int i = 0; i < size; ++i) {
//        QPointF p;
//        strm >> p;
//        //triangles_ << createPlanePoint(p);
//    }
//    f.close();
}

Plane::~Plane()
{
    clearTringle();
}

QRectF Plane::boundingRect() const
{
    // outer most edges
    double xDelta = transformation_->getDeltaWidth()*k
            + (transformation_->isProectiveEnabled() || transformation_->isAffineEnabled()
               ? affineXYDelta.x()*k
               : 0);

    double yDelta = transformation_->getDeltaHeight()*k
            - (transformation_->isProectiveEnabled() || transformation_->isAffineEnabled()
               ? affineXYDelta.y()*k
               : 0);


    return QRectF(160 + xDelta
                  , 0 - 150 - yDelta
                  , 430
                  , 430);
}

void Plane::setTrianglesVisible(bool isTrianglesVisible)
{
    isTrianglesVisible_ = isTrianglesVisible;
    redraw();

    //    if(!isTrianglesVisible){
    //        QFile f("cat.bin");
    //        f.open(QIODevice::OpenModeFlag::ReadWrite);
    //        QDataStream strm(&f);

    //        strm << triangles_.size();
    //        for(auto mP : triangles_){
    //            strm << mP->pos();
    //        }
    //        f.close();
    //    }
}

void Plane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItemBase::paint(painter, option, widget);
    drawPlane(painter);
    transformateDatail();
}

void Plane::mousePressEvent (QGraphicsSceneMouseEvent * event)
{
    return GraphicsItemBase::mousePressEvent(event);
}

void Plane::createPlane()
{
    clearTringle();

    QPointF delta(boundingRect().topLeft());
    QPointF stP(30 + delta.rx(), 250 + delta.ry()), tmP(stP);

    triangles_ << createPlanePoint(stP);
    stP.rx() += 10;     stP.ry() -= 22;
    tmP.rx() -= 5;      tmP.ry() -= 6;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);


    stP.rx() += 133;    stP.ry() -= 11;
    tmP.rx() += 101;    tmP.ry() -= 33;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);


    stP.rx() += 33;     stP.ry() -= 0;
    tmP.rx() += 69;     tmP.ry() -= 23;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);

    stP.rx() += 16;     stP.ry() -= 1;
    tmP.rx() += 18; tmP.ry() += 30;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);

    stP.rx() += 83;     stP.ry() -=  85;
    tmP.rx() += 53;     tmP.ry() -= 63;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);

    stP.rx() += 47;     stP.ry() -= 11;
    tmP.rx() += 57;     tmP.ry() -= 44;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);

    stP.rx() += 34;     stP.ry() += 21;
    tmP.rx() += 67;     tmP.ry() += 20;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);

    stP.rx() -= 62;     stP.ry() += 95;
    tmP.rx() += 0;      tmP.ry() += 33;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);

    stP.rx() += 28;     stP.ry() += 18;
    tmP.rx() -= 52;      tmP.ry() += 84;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);


    stP.rx() += 28;     stP.ry() += 20;
    tmP.rx() += 50;      tmP.ry() -= 7;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);

    stP.rx() += 28;     stP.ry() += 26;
    tmP.rx() += 26;      tmP.ry() += 56;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);

    stP.rx() -= 18;     stP.ry() += 14;
    tmP.rx() -= 17;      tmP.ry() += 20;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);

    stP.rx() -= 104;     stP.ry() -= 27;
    tmP.rx() -= 65;      tmP.ry() -= 21;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);

    stP.rx() -= 47;     stP.ry() += 18;
    tmP.rx() -= 72;      tmP.ry() += 20;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);

    stP.rx() -= 82;     stP.ry() += 21;
    tmP.rx() -= 58;      tmP.ry() += 18;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);

    stP.rx() -= 62;     stP.ry() -= 26;
    tmP.rx() -= 62;      tmP.ry() -= 20;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);

    stP.rx() += 44;     stP.ry() -= 15;
    tmP.rx() -= 41;      tmP.ry() -= 30;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);

    stP.rx() -= 19;     stP.ry() -= 34;
    tmP.rx() += 40;      tmP.ry() -= 4;
    triangles_ << createPlanePoint(tmP) << createPlanePoint(stP);

    tmP.rx() -= 68;      tmP.ry() -= 32;
    triangles_ << createPlanePoint(tmP) << triangles_.at(0);

    setupSmoothing();
}

void Plane::setupSmoothing()
{
    const auto doubleClickedAction = [=](const QPointF &pos){
        const auto it = std::find_if(triangles_.begin(), triangles_.end(), [=](const QGraphicsItem *a) { return a->pos() == pos; });

        const auto r21 = (*it)->pos();
        const auto r11 = (*(it-1))->pos();
        auto r12 = (*(it+1))->pos();

        const double alpha1 = QLineF(r11, r21).length();
        const double alpha2 = QLineF(r12, r21).length();

        // Расчитываем глаткость первого порядка для кривой Безье второго порядка
        r12 = r21 + (alpha2 * (r21 - r11)) / alpha1;
        (*(it+1))->setPos(r12);

        scene()->connect(*(it-1), &MovablePoint::positionChanged, scene(), [=]{
            const auto r21 = (*it)->pos();
            const auto r11 = (*(it-1))->pos();
            auto r12 = (*(it+1))->pos();

            const double alpha1 = QLineF(r11, r21).length();
            const double alpha2 = QLineF(r12, r21).length();

            // Расчитываем глаткость первого порядка для кривой Безье второго порядка
            r12 = r21 + (alpha2 * (r21 - r11)) / alpha1;
            (*(it+1))->setPos(r12);
        });
    };

    for(const MovablePoint *mp : triangles_){
        scene()->connect(mp, &MovablePoint::doubleClicked, doubleClickedAction);
    }
}

void Plane::drawPlane(QPainter *painter)
{
    QPainterPath plaine(triangles_.at(0)->pos());

    QPointF stP, ctrlP, edP;
    for (int i = 0; i < triangles_.size() - 1; i += 2) {
        stP = triangles_.at(i+0)->pos();
        ctrlP = triangles_.at(i+1)->pos();
        edP = triangles_.at(i+2)->pos();
        plaine.quadTo(ctrlP, edP);

        if(isTrianglesVisible_){
            painter->setPen(QPen(Qt::black, 1, Qt::PenStyle::DashLine));
            painter->drawLine({stP, ctrlP});
            painter->drawLine({ctrlP, edP});
        }
    }

    painter->setPen(QPen(Qt::red, 3, Qt::PenStyle::SolidLine));
    painter->drawPath(plaine);
}

void Plane::clearTringle()
{
    for(auto tr : triangles_){
        tr->deleteLater();
    }

    triangles_.clear();
}

void Plane::transformateDatail()
{
    GraphicsItemBase::transformateDatail();
    setTransform(transformation_->getTransformation().first);
}

MovablePoint *Plane::createPlanePoint(const QPointF &point) {
    MovablePoint *mPoint = new MovablePoint(isTrianglesVisible_ ? 3 : 0, Qt::darkGray, "", this);
    return mPoint->setPos(point);
}
