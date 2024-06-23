#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

QString name_field;




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


void MainWindow::on_name_field_editingFinished()
{
    name_field = ui->name_field->text();
    cout<< "name_field: " << name_field.toStdString() << endl;
}

