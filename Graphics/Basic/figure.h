#ifndef FIGURE_H
#define FIGURE_H

#include <QPointF>
#include <QVector>


namespace  Graphics{

class Figure {
protected:
    Figure();

public:
    virtual QVector<QPointF> getPoints() const = 0;
    virtual ~Figure();
};

}

#endif // FIGURE_H
