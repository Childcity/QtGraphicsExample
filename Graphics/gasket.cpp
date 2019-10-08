#include "gasket.h"
#include "arc.h"

#include <QPainter>
#include <QPen>
#include <QWidget>
#include <algorithm>
#include <QDebug>
#include <QMatrix4x4>
#include <QValueAxis>
#include <QGraphicsScene>

void Gasket::setABGH(double value)
{
    AB_GH_ = value;
    redraw();
}

void Gasket::setHeight(double value)
{
    height_ = value;
    redraw();
}

void Gasket::setWidth(double width)
{
    width_ = width;
    redraw();
}

void Gasket::redraw() {
    chart_->scene()->setBackgroundBrush((QBrush(Qt::white, Qt::SolidPattern)));
    update();
    chart_->update();
}

void Gasket::setArc8R(double value)
{
    arc8R_ = value;
    redraw();
}

void Gasket::setArc13R(double value)
{
    arc13R_ = value;
    redraw();
}

void Gasket::setArc11R(double arc11R)
{
    arc11R_ = arc11R;
    redraw();
}

void Gasket::setPointsNamesVisible(bool isPointsNamesVisible)
{
    isPointsNamesVisible_ = isPointsNamesVisible;
    redraw();
}

void Gasket::setCF(double CF)
{
    CF_ = CF;
    redraw();
}

void Gasket::setDE(double DE)
{
    DE_ = DE;
    redraw();
}

void Gasket::setPB(double BP)
{
    PB_ = BP;
    redraw();
}

void Gasket::setRotateAncle(double rotateAncle)
{
    rotateAncle_ = rotateAncle;
    redraw();
}

void Gasket::setRotatePoint(const QPointF &rotatePoint)
{
    rotatePoint_ = rotatePoint;
    redraw();
}

void Gasket::setIsAffineEnabled(bool isAffineEnabled)
{
    isAffineEnabled_ = isAffineEnabled;
    redraw();
}

void Gasket::setIsProectiveEnabled(bool isProectiveEnabled)
{
    isProectiveEnabled_ = isProectiveEnabled;
    redraw();
}

void Gasket::setAffineSystemPoints(const QPointF &affineSystemPoint, int i)
{
    affineSystemPoints_[i].second = affineSystemPoint;
    redraw();
}

void Gasket::setAffineSystemWeights(float weight, int i)
{
    affineSystemPoints_[i].first = weight;
    redraw();
}

QPointF Gasket::getCoordXEnd()
{
    auto xAxis = reinterpret_cast<QValueAxis *>(chart_->axisX());
    return {x() +  xAxis->max()*k, y()};
}

QPointF Gasket::getCoordYEnd()
{
    auto yAxis = reinterpret_cast<QValueAxis *>(chart_->axisY());
    return {x(), y() - yAxis->max()*k};
}

Gasket::Gasket(QChart *chart)
    : chart_(chart)
{
    // move to Start of XY coordinate system
    chartPos_ = chart_->pos();
    setPos({chartPos_.x() + 48, chartPos_.y() + 170 + 142});
    rotatePoint_ = pos();
}

Gasket::~Gasket(){}

QRectF Gasket::boundingRect() const
{
    // outer most edges
    //QPointF bootomLeft = chart_->plotArea().bottomLeft();
    return QRectF(x()-margin + width_*k + (isProectiveEnabled_||isAffineEnabled_ ? affineXYDelta.x()*k : 0)
                  , y()-margin - 50*k - height_*k + (isProectiveEnabled_||isAffineEnabled_ ? affineXYDelta.y()*k : 0)//50 - detail width
                  , (AB_GH_ + (PB_<0?-PB_:0))*k + margin*2 // if PB is longer then AB -> boundingRect should be extended till PB ends
                  , 50*k + margin*2);
}

void Gasket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    using namespace Graphics;

    //############### creating detail lines #################

    QPointF stP = {boundingRect().topLeft().x()+margin, boundingRect().topLeft().y()+margin};
    QPointF t; //tmp point


    QLineF lAB(10*k, 0, AB_GH_*k, 0);
    QLineF lBC(lAB.p2(), QPointF(lAB.p2().x(), lAB.p2().y() + ((50-CF_)/2)*k));


    t.rx() = lAB.p2().x() - PB_*k;
    t.ry() = lAB.p2().y() + (50./2. - DE_/2.)*k;
    QLineF lCD(lBC.p2(), t);
    QLineF lDE(t, QPointF(t.x(), t.y() + DE_*k));


    QLineF lEF(lDE.p2(), QPointF(lBC.p2().x(), lAB.p2().y() + (50 - ((50-CF_)/2))*k));
    QLineF lFG(lEF.p2(), QPointF(lEF.p2().x(), lAB.p2().y() + 50*k));
    QLineF lGH(lFG.p2(), QPointF());


    t.rx() = lFG.translated(stP).p2().x() - (AB_GH_-10)*k;
    t.ry() = lFG.translated(stP).p2().y() - 10*k;
    Arc arc(M_PI/2., M_PI, arc8R_*k, t);
    QVector<QPointF> arc8 = arc.getPoints();
    lGH.setP2(arc8.first() - stP);


    t.rx() = (t-stP).x() - 10*k;
    t.ry() = (t-stP).y();
    QLineF lIJ(arc8.last() - stP, QPointF(t.x(), t.y() - 7.5*k));
    QLineF lJK(lIJ.p2(), QPointF());


    t.rx() = lIJ.translated(stP).p2().x() + 17*k;
    t.ry() = lIJ.translated(stP).p2().y() - 7.5*k;
    arc = Arc(-M_PI/1.25, M_PI/1.23, arc11R_*k, t);
    QVector<QPointF> arc11 = arc.getPoints();
    lJK.setP2(arc11.last() - stP);


    t.rx() = lIJ.p2().x();
    t.ry() = lIJ.p2().y() - 15*k;
    QLineF lLM(t, arc11.first() - stP);
    QLineF lMN(t, QPointF());


    t.rx() = (t+stP).x() + 10*k;
    t.ry() = (t+stP).y() - 7.5*k;
    arc = Arc (-M_PI, -M_PI/2., arc13R_*k, t);
    QVector<QPointF> arc13 = arc.getPoints();

    lMN.setP2(arc13.first() - stP); // set end of MN to start of Arc
    lAB.setP1(arc13.last() - stP); // set start of AB to end of Arc

    QVector<QLineF> lines({
                            lAB, lBC, lCD, lDE, lEF, lFG, lGH, lIJ, lJK, lLM, lMN
                         });

    for(auto &line : lines){
        line.translate(stP);
        //qDebug() <<line;
    }


    //############### drawing detail lines #################
    painter->setRenderHint(QPainter::Antialiasing);

    // painting symetric lines
    drawSymetricLines(painter, stP, arc11);

    // painting lines
    painter->setPen({Qt::red, 3});
    painter->drawLines(lines);
    painter->drawLines(arc8.data(), arc8.size()/2);
    painter->drawLines(arc11.data(), arc11.size()/2);
    painter->drawLines(arc13.data(), arc13.size()/2);

    // painting text
    if(isPointsNamesVisible_)
        drawPointsNames(painter, lines);

    transformateDatail();
}

void Gasket::transformateDatail()
{
    QMatrix4x4 transformationMatrix;
    QTransform transformMatrix;

    {   // clear transformation of chart
        chart_->setTransform(QTransform());
        chart_->setPos(chartPos_);
    }

    {
        float a    = static_cast<float>(M_PI/180. * rotateAncle_);
        float sina = sinf(a);
        float cosa = cosf(a);
        float centerX = static_cast<float>(rotatePoint_.x());
        float centerY = static_cast<float>(rotatePoint_.y());

        // rotate about Z and translate
        transformationMatrix = QMatrix4x4(cosa,   sina,   0,    centerX - cosa*centerX - sina*centerY,
                                         -sina,   cosa,   0,   centerY - -sina*centerX - cosa*centerY,
                                          0,       0,     1,   0,
                                          0,       0,     0,   1);

        transformMatrix = transformationMatrix.toTransform();
    }


    if(isProectiveEnabled_){
        double Xy = affineSystemPoints_[0].second.x();
        double Yy = affineSystemPoints_[0].second.y();
        double Wy = static_cast<double>(affineSystemPoints_[0].first);

        double X0 = static_cast<double>(affineSystemPoints_[1].second.x());
        double Y0 = affineSystemPoints_[1].second.y();
        double W0 = static_cast<double>(affineSystemPoints_[1].first);

        double Xx = affineSystemPoints_[2].second.x();
        double Yx = affineSystemPoints_[2].second.y();
        double Wx = static_cast<double>(affineSystemPoints_[2].first);

        auto affineT = QTransform(Xx*Wx,    Yx*Wx,          Wx,
                                 Xy*Wy,    Yy*Wy,          Wy,
                                 X0*W0,    Y0*W0,          W0);
        transformMatrix *= affineT;

        chart_->setPos(pos());
        chart_->setTransform(affineT);
    }



    if(isAffineEnabled_){
        double Xy = affineSystemPoints_[0].second.x();
        double Yy = affineSystemPoints_[0].second.y();

        double X0 = static_cast<double>(affineSystemPoints_[1].second.x());
        double Y0 = affineSystemPoints_[1].second.y();

        double Xx = affineSystemPoints_[2].second.x();
        double Yx = affineSystemPoints_[2].second.y();

        auto affineT = QTransform(Xx,    Yx,         0,
                                 Xy,    Yy,          0,
                                 X0,    Y0,          1);
        transformMatrix *= affineT;

        chart_->setPos(pos());
        chart_->setTransform(affineT);
    }

    setTransform(transformMatrix);
}

void Gasket::drawSymetricLines(QPainter *painter, const QPointF &stP, const QVector<QPointF> &arc)
{
    painter->setPen(QPen(Qt::black, 2, Qt::PenStyle::DashDotLine));
    //painter->drawRect(boundingRect()); //draw rectangle
    //painter->drawEllipse(QRectF(pos().x()-5, pos().y()-5, 10, 10));
    //painter->drawEllipse(QRectF(rotatePoint_.x()-5, rotatePoint_.y()-5, 10, 10));
    //painter->drawEllipse(QRectF(-5, -5, 10, 10));

    //auto chartRect = mapRectFromItem(chart_, chart_->scene()->sceneRect());
    //painter->drawEllipse(QRectF(chartRect.topRight().x()-10, chartRect.topRight().y(), 10, 10));
    //painter->drawEllipse(QRectF(chartRect.bottomLeft().x(), chartRect.bottomLeft().y()-10, 10, 10));
    painter->drawRect(mapRectFromItem(chart_, chart_->boundingRect()));
    //painter->drawRect(chartRect); //peinter rect

    // draw symetric line
    QPointF t(stP.x() - 2*k, stP.y() + 50.*k/2.);
    painter->drawLine(t, QPointF(t.x() + AB_GH_*k + 4*k + (PB_<0 ? -PB_*k:0), t.y()));

    QPointF arcTopPoint = *std::min_element(arc.constBegin(), arc.constEnd()
                                            , [](const QPointF &l, const QPointF &r){return r.y()>l.y();});
    arcTopPoint.ry() -= 2*k;
    double radius = arcTopPoint.y() - t.y();
    painter->drawLine(arcTopPoint, {arcTopPoint.x()
                                    , arcTopPoint.y() - 2 * radius});
}

void Gasket::drawPointsNames(QPainter *painter, const QVector<QLineF> &lines)
{
    QPointF txtP;
    painter->setPen({Qt::black, 1});
    painter->setFont(QFont("", fontSize, 1));

    txtP.rx() = lines[0].p1().x();
    txtP.ry() = lines[0].p1().y() - textDistance;
    painter->drawText(txtP, "A");

    txtP.rx() = lines[0].p2().x() - PB_*k;
    txtP.ry() = lines[0].p2().y() - textDistance;
    painter->drawText(txtP, "P");

    txtP.rx() = lines[0].p2().x();
    txtP.ry() = lines[0].p2().y() - textDistance;
    painter->drawText(txtP, "B");

    txtP.rx() = lines[1].p2().x() + textDistance;
    txtP.ry() = lines[1].p2().y();
    painter->drawText(txtP, "C");

    txtP.rx() = lines[2].p2().x() - textDistance * 2;
    txtP.ry() = lines[2].p2().y();
    painter->drawText(txtP, "D");

    txtP.rx() = lines[3].p2().x() - textDistance * 2;
    txtP.ry() = lines[3].p2().y();
    painter->drawText(txtP, "E");

    txtP.rx() = lines[4].p2().x() + textDistance;
    txtP.ry() = lines[4].p2().y();
    painter->drawText(txtP, "F");

    txtP.rx() = lines[5].p2().x() + textDistance;
    txtP.ry() = lines[5].p2().y();
    painter->drawText(txtP, "G");

    txtP.rx() = lines[6].p2().x();
    txtP.ry() = lines[6].p2().y() - textDistance;
    painter->drawText(txtP, "H");

    txtP.rx() = lines[7].p1().x() + textDistance;
    txtP.ry() = lines[7].p1().y();
    painter->drawText(txtP, "I");

    txtP.rx() = lines[7].p2().x() + textDistance;
    txtP.ry() = lines[7].p2().y() - textDistance;
    painter->drawText(txtP, "J");

    txtP.rx() = lines[8].p2().x() + textDistance;
    txtP.ry() = lines[8].p2().y() - textDistance;
    painter->drawText(txtP, "K");

    txtP.rx() = lines[9].p2().x() + textDistance;
    txtP.ry() = lines[9].p2().y() + textDistance * 2;
    painter->drawText(txtP, "L");

    txtP.rx() = lines[9].p1().x() + textDistance;
    txtP.ry() = lines[9].p1().y() + textDistance * 2;
    painter->drawText(txtP, "M");

    txtP.rx() = lines[10].p2().x() + textDistance;
    txtP.ry() = lines[10].p2().y();
    painter->drawText(txtP, "N");
}
