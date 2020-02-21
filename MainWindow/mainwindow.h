#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Graphics/Basic/transformation2d.h"
#include "Graphics/bernoullilemniscate.h"
#include "Graphics/gasket.h"
#include "Graphics/plane.h"
#include "Graphics/dragonfractal.h"
#include "Graphics/hauseindimetricproection.h"
#include <Graphics/elliptichyperboloid.h>

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

private slots:
    void on_pushButton_3_clicked();

private:
    void redraw();

    void update3dTransform();

    void changePictureOnTab(int index);

private:
    Ui::MainWindow *ui_;
    QGraphicsScene *scene_;
    QChart *chart_;
    Gasket *gasket_;
    BernoulliLemniscate *bLemniscat_;
    Plane *plane_;
    DragonFractal *dragon_;
    HauseInDimetricProection *house_;
    EllipticHyperboloid *hyperboloid_;

    Transformation2D transformation2d_;
    Transformation3D transformation3d_;
};

#endif // MAINWINDOW_H
