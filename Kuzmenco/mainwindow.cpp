#include "mainwindow.h"
#include "ui_mainwindow.h"

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

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}

void MainWindow::setUi(Ui::MainWindow *newUi)
{
    ui = newUi;
}

