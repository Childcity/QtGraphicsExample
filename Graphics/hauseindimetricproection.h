#ifndef HauseInDimetricProection_H
#define HauseInDimetricProection_H

#include "Basic/graphicsitembase.h"
#include "Basic/transformation2d.h"
#include "Basic/transformation3d.h"

#include <list>
#include <vector>
#include <QChart>

using std::vector;
using std::list;
using std::pair;
using namespace QtCharts;

class HauseInDimetricProection: public GraphicsItemBase {
private:
    vector<QVector3D> points_ {
        {
            /*0*/   {200, 350, 350}, {400, 350, 350}, {400, 200, 350},
            /*3*/   {300, 100, 350}, {200, 200, 350}, // 5 points for back of house

            /*5*/   {200, 350, 50}, {400, 350, 50}, {400, 200, 50},
            /*8*/   {300, 100, 50}, {200, 200, 50}, // 5 points for front of house

            /*10*/  {400, 350-10, 50+30}, {400, 350-10, 50+60},
            /*12*/  {400, 350-90, 50+30}, {400, 350-90, 50+60}, // door

            /*14*/  {200+40, 350-50, 50}, {200+120, 350-50, 50},
            /*16*/  {200+40, 350-120, 50}, {200+120, 350-120, 50} //window
        }
    };

    list<pair<size_t, size_t>> lines_ {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}, // front lines
        {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 5}, // back lines

        {2, 4}, {7, 9},                        // connect roof in front and back
        {0, 5}, {1, 6}, {2, 7}, {3, 8}, {4, 9}, // connect front & back

        {10, 11}, {12, 13}, {11, 13}, {10, 12}, // connect door
        {14, 15}, {16, 17}, {14, 16}, {15, 17} // connect window
    };

    Transformation3D *transformation3d_;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public:
    HauseInDimetricProection(QChart *chart, Transformation2D *transformation2d, Transformation3D *transformation3d);

    QRectF boundingRect() const override;

    void redraw() override;

private:
    void transformateDatail() override;

    void genHouse();

};

#endif // HauseInDimetricProection_H
