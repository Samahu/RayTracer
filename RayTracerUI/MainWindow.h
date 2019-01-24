#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class RenderArea;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setRendererSimpleRTf();
    void setRendererSimpleRTd();

private:
    Ui::MainWindow *ui;
    // RenderArea* renderArea;
};

#endif // MAINWINDOW_H
