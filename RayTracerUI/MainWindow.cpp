#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "RenderArea.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setRendererSimpleRTf()
{
    ui->renderArea->setRendererType(RenderArea::RendererType::SimpleRTf);
}

void MainWindow::setRendererSimpleRTd()
{
    ui->renderArea->setRendererType(RenderArea::RendererType::SimpleRTd);
}
