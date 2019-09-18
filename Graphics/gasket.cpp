#include "gasket.h"
#include "arc.h"

#include <QPainter>
#include <QPen>
#include <QWidget>
#include <algorithm>
#include <QDebug>
#include <QMatrix4x4>

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

void Gasket::redraw() {
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

QPointF Gasket::getCoordStart() const
{
    return coordStart_;
}

Gasket::Gasket(QChart *chart)
    : chart_(chart)
{
    coordStart_ = {chart_->boundingRect().topLeft().x() + 43, chart_->boundingRect().topLeft().y() + 170 + 142};
    rotatePoint_= coordStart_;
    setPos(coordStart_);
}

QRectF Gasket::boundingRect() const
{
    // outer most edges
    //QPointF bootomLeft = chart_->plotArea().bottomLeft();
    return QRectF(x()-margin
                  , y()-margin - 50*k //50 - detail width
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
    //setTransformOriginPoint(center);

    float a    = static_cast<float>(M_PI/180. * rotateAncle_);
    float sina = sinf(a);
    float cosa = cosf(a);
    float centerX = static_cast<float>(rotatePoint_.x());
    float centerY = static_cast<float>(rotatePoint_.y());

    QMatrix4x4 transformationMatrix(cosa,    sina,  0,   centerX - cosa*centerX - sina*centerY,
                                    -sina,   cosa,  0,   centerY - -sina*centerX - cosa*centerY,
                                    0,       0,     1,   0,
                                    0,       0,     0,   1);

    setTransform(transformationMatrix.toTransform());
}

void Gasket::drawSymetricLines(QPainter *painter, const QPointF &stP, const QVector<QPointF> &arc)
{
    painter->setPen(QPen(Qt::black, 2, Qt::PenStyle::DashDotLine));
    painter->drawRect(boundingRect()); //draw rectangle
    //painter->drawEllipse(*new QRectF(pos().x()-5, pos().y()-5, 10, 10));

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
