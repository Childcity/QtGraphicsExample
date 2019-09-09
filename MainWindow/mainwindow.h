#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gasket.h"

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
    Ui::MainWindow *_ui;
    QGraphicsScene *_scene;
    QChart *_chart;
    Gasket *_gasket;
};

#endif // MAINWINDOW_H
