#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Graphics/bernoullilemniscate.h"
#include "Graphics/transformation.h"
#include "Graphics/gasket.h"

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
    void resizeEvent(QResizeEvent* event) override;

private:
    void redraw();

private:
    Ui::MainWindow *ui_;
    QGraphicsScene *scene_;
    QChart *chart_;
    Gasket *gasket_;
    BernoulliLemniscate *bLemniscat_;
    Transformation *transformation_;
};

#endif // MAINWINDOW_H
