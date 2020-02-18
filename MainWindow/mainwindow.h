#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Graphics/bernoullilemniscate.h"
#include "Graphics/transformation2d.h"
#include "Graphics/gasket.h"
#include "Graphics/plane.h"
#include "Graphics/dragonfractal.h"
#include "Graphics/hauseindimetricproection.h"

#include <QGraphicsScene>
#include <QMainWindow>
#include <QChart>


using namespace QtCharts;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

    void resizeEvent(QResizeEvent* event) override;

private:
    void redraw();
    void setAnimation();

private:
    Ui::MainWindow *ui_;
    QGraphicsScene *scene_;
    QChart *chart_;
    Gasket *gasket_;
    BernoulliLemniscate *bLemniscat_;
    Plane *plane_;
    DragonFractal *dragon_;
    HauseInDimetricProection *house_;

    Transformation2D *transformation_;
    QTimer *animationInterval_;
};

#endif // MAINWINDOW_H
