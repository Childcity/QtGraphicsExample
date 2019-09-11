#include "gasket.h"
#include "arc.h"

#include <QPainter>
#include <QPen>
#include <QWidget>
#include <QDebug>

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

Gasket::Gasket(QChart *chart)
    : chart_(chart)
{}

QRectF Gasket::boundingRect() const
{
    // outer most edges
    QPointF bootomLeft = chart_->plotArea().bottomLeft();
    return QRectF(bootomLeft.x(), bootomLeft.y() - height_*k, AB_GH_*k, 50*k);
}

void Gasket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    using namespace Graphics;

    QRectF rect = boundingRect();

    //############### creating detail lines #################

    QPointF stP = rect.topLeft();
    QPointF t; //tmp point


    QLineF lAB(10*k, 0, AB_GH_*k, 0);
    QLineF lBC(lAB.p2(), QPointF(lAB.p2().x(), lAB.p2().y() + ((50-CF_)/2)*k));


    t.rx() = lAB.p2().x() - 14*k;
    t.ry() = lAB.p2().y() + 10.4*k;
    QLineF lCD(lBC.p2(), t);
    QLineF lDE(t, QPointF(t.x(), t.y() + 30*k));


    QLineF lEF(lDE.p2(), QPointF(lBC.p2().x(), lBC.p2().y() + 20*k));
    QLineF lFG(lEF.p2(), QPointF(lEF.p2().x(), lEF.p2().y() + 15*k));
    QLineF lGH(lFG.p2(), QPointF(lFG.p2().x() - (AB_GH_-10)*k, lFG.p2().y()));


    t.rx() = lGH.translated(stP).p2().x() - 10*k;
    t.ry() = lGH.translated(stP).p2().y() - 10*k;
    Arc arc(M_PI/2., M_PI, arc8R_*k, QPointF(t.x() + 10*k, t.y()));
    QVector<QPointF> arc8 = arc.getPoints();


    t.rx() = lGH.p2().x() - 10*k;
    t.ry() = lGH.p2().y() - 10*k;
    QLineF lIJ(t, QPointF(t.x(), t.y() - 7.5*k));
    QLineF lJK(lIJ.p2(), QPointF(lIJ.p2().x() + ((((6*k)))), lIJ.p2().y()));


    t.rx() = lIJ.translated(stP).p2().x() + 17*k;
    t.ry() = lIJ.translated(stP).p2().y() - 7.5*k;
    arc = Arc (-M_PI/1.26, M_PI/1.23, arc11R_*k, t);
    QVector<QPointF> arc11 = arc.getPoints();


    t.rx() = lIJ.p2().x();
    t.ry() = lIJ.p2().y() - 15*k;
    QLineF lMN(t, QPointF(t.x(), t.y() - 7.5*k));
    QLineF lLM(lMN.p1(), QPointF(lMN.p1().x() + ((((6*k)))), lMN.p1().y()));


    t.rx() = lMN.translated(stP).p2().x() + 10*k;
    t.ry() = lMN.translated(stP).p2().y();
    arc = Arc (-M_PI, -M_PI/2., arc13R_*k, t);
    QVector<QPointF> arc13 = arc.getPoints();


    QVector<QLineF> lines({
                            lAB, lBC, lCD, lDE, lEF, lFG, lGH, lIJ, lJK, lLM, lMN
                         });

    for(auto &line : lines){
        line.translate(stP);
        //qDebug() <<line;
    }


    //############### drawing detail lines #################

    // draw rectangle
    painter->setPen({Qt::black, 1});
    painter->drawRect(rect);

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
