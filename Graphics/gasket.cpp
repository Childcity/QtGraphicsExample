#include "gasket.h"
#include "arc.h"

#include <QPainter>
#include <QPen>
#include <QDebug>

void Gasket::redraw() {
    GraphicsItemBase::redraw();
    update();
}


void Gasket::setABGH(double value)
{
    AB_GH_ = value;
    redraw();
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

Gasket::Gasket(QChart *chart, Transformation2D *transformation)
    : GraphicsItemBase (chart, transformation)
{}

Gasket::~Gasket(){}

QRectF Gasket::boundingRect() const
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


    return QRectF(x()-margin + xDelta
                  , y()-margin - 50*k - yDelta//50 - detail width
                  , (AB_GH_ + (PB_<0?-PB_:0))*k + margin*2 // if PB is longer then AB -> boundingRect should be extended till PB ends
                  , 50*k + margin*2);
}

void Gasket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsItemBase::paint(painter, option, widget);
    drawGasket(painter);
    transformateDatail();
}

void Gasket::transformateDatail()
{
    GraphicsItemBase::transformateDatail();
    setTransform(transformation_->getTransformation().first);
}

void Gasket::drawSymetricLines(QPainter *painter, const QPointF &stP, const QVector<QPointF> &arc)
{
    // draw symetric line
    painter->setPen(QPen(Qt::black, 2, Qt::PenStyle::DashDotLine));
    QPointF t(stP.x() - 2*k, stP.y() + 50.*k/2.);
    painter->drawLine(t, QPointF(t.x() + AB_GH_*k + 4*k + (PB_<0 ? -PB_*k:0), t.y()));

    QPointF arcTopPoint = *std::min_element(arc.constBegin(), arc.constEnd()
                                            , [](const QPointF &l, const QPointF &r){return r.y()>l.y();});
    arcTopPoint.ry() -= 2*k;
    double radius = arcTopPoint.y() - t.y();
    painter->drawLine(arcTopPoint, {arcTopPoint.x()
                                    , arcTopPoint.y() - 2 * radius});
}

void Gasket::drawGasket(QPainter *painter)
{
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
