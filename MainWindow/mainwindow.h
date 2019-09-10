#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    Ui::MainWindow *ui_;
    QGraphicsScene *scene_;
    QChart *chart_;
    Gasket *gasket_;
};

#endif // MAINWINDOW_H
