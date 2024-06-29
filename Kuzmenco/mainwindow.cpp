#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPainter>
#include <QGraphicsScene>

using namespace std;
extern QApplication * app;
extern QPen penRed;
extern QPen penGreen;
extern QPen penBlue;
extern QPen penYellow;
extern QPen penRedLine;
extern QPen penGreenLine;
extern QPen penBlueLine;
extern QGraphicsScene * scene;

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

void MainWindow::on_dateEdit_dateChanged(const QDate &date)
{
    Date = ui->dateEdit->text();
    cout<< "Date: " << Date.toStdString() << endl;
}

void MainWindow::r1l1()
{
    if (r1 > 0)
    {
        switch (r1)
        {
            case 5:  r1y = 720; break;
            case 10: r1y = 690; break;
            case 15: r1y = 670; break;
            case 20: r1y = 645; break;
            case 25: r1y = 625; break;
            case 30: r1y = 605; break;
            case 35: r1y = 585; break;
            case 40: r1y = 565; break;
            case 45: r1y = 548; break;
            case 50: r1y = 530; break;
            case 55: r1y = 513; break;
            case 60: r1y = 493; break;
            case 65: r1y = 479; break;
            case 70: r1y = 462; break;
            case 75: r1y = 444; break;
            case 80: r1y = 427; break;
            case 85: r1y = 416; break;
            case 90: r1y = 401; break;
            case 95: r1y = 387; break;
            case 100: r1y = 373; break;
            case 105: r1y = 361; break;
            case 110: r1y = 347; break;
            case 115: r1y = 335; break;
            case 120: r1y = 321; break;
            case 125: r1y = 312; break;
            case 130: r1y = 301; break;
            case 135: r1y = 290; break;
            case 140: r1y = 278; break;
            case 145: r1y = 267; break;
            case 150: r1y = 258; break;
            case 155: r1y = 249; break;
            case 160: r1y = 238; break;
            case 165: r1y = 228; break;
            case 170: r1y = 218; break;
            case 175: r1y = 210; break;
            case 180: r1y = 201; break;
            case 185: r1y = 195; break;
            case 190: r1y = 186; break;
        }
        scene->addEllipse(r1x, r1y, 4, 4, penYellow);
    }// r1
    if (l1>0)
    {
        switch (l1)
        {
            case 5:  l1y = 720; break;
            case 10: l1y = 690; break;
            case 15: l1y = 670; break;
            case 20: l1y = 645; break;
            case 25: l1y = 625; break;
            case 30: l1y = 605; break;
            case 35: l1y = 585; break;
            case 40: l1y = 565; break;
            case 45: l1y = 548; break;
            case 50: l1y = 530; break;
            case 55: l1y = 513; break;
            case 60: l1y = 493; break;
            case 65: l1y = 479; break;
            case 70: l1y = 462; break;
            case 75: l1y = 444; break;
            case 80: l1y = 427; break;
            case 85: l1y = 416; break;
            case 90: l1y = 401; break;
            case 95: l1y = 387; break;
            case 100: l1y = 373; break;
            case 105: l1y = 361; break;
            case 110: l1y = 347; break;
            case 115: l1y = 335; break;
            case 120: l1y = 321; break;
            case 125: l1y = 312; break;
            case 130: l1y = 301; break;
            case 135: l1y = 290; break;
            case 140: l1y = 278; break;
            case 145: l1y = 267; break;
            case 150: l1y = 258; break;
            case 155: l1y = 249; break;
            case 160: l1y = 238; break;
            case 165: l1y = 228; break;
            case 170: l1y = 218; break;
            case 175: l1y = 210; break;
            case 180: l1y = 201; break;
            case 185: l1y = 195; break;
            case 190: l1y = 186; break;
        }
        scene->addEllipse(l1x, l1y, 4, 4, penYellow);
    }
    if (r1 > 0 && l1 > 0)
    {
        if (r1 == l1)
        {
            scene->addLine(r1x,r1y,l1x,l1y, penGreenLine);
            scene->addEllipse(l1x, l1y, 4, 4, penGreen);
            scene->addEllipse(r1x, r1y, 4, 4, penGreen);
        }
        if (r1 > l1)
        {
            scene->addLine(r1x,r1y,l1x,l1y, penRedLine);
            scene->addEllipse(l1x, l1y, 4, 4, penRed);
            scene->addEllipse(r1x, r1y, 4, 4, penRed);
        }
        if (r1 < l1)
        {
            scene->addLine(r1x,r1y,l1x,l1y, penBlueLine);
            scene->addEllipse(l1x, l1y, 4, 4, penBlue);
            scene->addEllipse(r1x, r1y, 4, 4, penBlue);
        }
    }
}

void MainWindow::r2l2()
{
scene->addEllipse(r2x, r2, 4, 4, penRed);
scene->addEllipse(l2x, l2, 4, 4, penRed);
//    if (r2 > 0)
//    {
//        switch (r2)
//        {
//            case 5:  r2y = 000; break;
//            case 10: r2y = 000; break;
//            case 15: r2y = 000; break;
//            case 20: r2y = 000; break;
//            case 25: r2y = 000; break;
//            case 30: r2y = 000; break;
//            case 35: r2y = 000; break;
//            case 40: r2y = 000; break;
//            case 45: r2y = 000; break;
//            case 50: r2y = 000; break;
//            case 55: r2y = 000; break;
//            case 60: r2y = 000; break;
//            case 65: r2y = 000; break;
//            case 70: r2y = 000; break;
//            case 75: r2y = 000; break;
//            case 80: r2y = 000; break;
//            case 85: r2y = 000; break;
//            case 90: r2y = 000; break;
//            case 95: r2y = 000; break;
//            case 100: r2y = 000; break;
//            case 105: r2y = 000; break;
//            case 110: r2y = 000; break;
//            case 115: r2y = 000; break;
//            case 120: r2y = 000; break;
//            case 125: r2y = 000; break;
//            case 130: r2y = 000; break;
//            case 135: r2y = 000; break;
//            case 140: r2y = 000; break;
//            case 145: r2y = 000; break;
//            case 150: r2y = 000; break;
//            case 155: r2y = 000; break;
//            case 160: r2y = 000; break;
//            case 165: r2y = 000; break;
//            case 170: r2y = 000; break;
//            case 175: r2y = 000; break;
//            case 180: r2y = 000; break;
//            case 185: r2y = 000; break;
//            case 190: r2y = 000; break;
//        }
//        scene->addEllipse(r2x, r2y, 4, 4, penYellow);
//    }// r2
//    if (l2>0)
//    {
//        switch (l2)
//        {
//            case 5:  l2y = 000; break;
//            case 10: l2y = 000; break;
//            case 15: l2y = 000; break;
//            case 20: l2y = 000; break;
//            case 25: l2y = 000; break;
//            case 30: l2y = 000; break;
//            case 35: l2y = 000; break;
//            case 40: l2y = 000; break;
//            case 45: l2y = 000; break;
//            case 50: l2y = 000; break;
//            case 55: l2y = 000; break;
//            case 60: l2y = 000; break;
//            case 65: l2y = 000; break;
//            case 70: l2y = 000; break;
//            case 75: l2y = 000; break;
//            case 80: l2y = 000; break;
//            case 85: l2y = 000; break;
//            case 90: l2y = 000; break;
//            case 95: l2y = 000; break;
//            case 100: l2y = 000; break;
//            case 105: l2y = 000; break;
//            case 110: l2y = 000; break;
//            case 115: l2y = 000; break;
//            case 120: l2y = 000; break;
//            case 125: l2y = 000; break;
//            case 130: l2y = 000; break;
//            case 135: l2y = 000; break;
//            case 140: l2y = 000; break;
//            case 145: l2y = 000; break;
//            case 150: l2y = 000; break;
//            case 155: l2y = 000; break;
//            case 160: l2y = 000; break;
//            case 165: l2y = 000; break;
//            case 170: l2y = 000; break;
//            case 175: l2y = 000; break;
//            case 180: l2y = 000; break;
//            case 185: l2y = 000; break;
//            case 190: l2y = 000; break;
//        }
//        scene->addEllipse(l2x, l2y, 4, 4, penYellow);
//    }
//    if (r2 > 0 && l2 > 0)
//    {
//        if (r2 == l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penGreenLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penGreen);
//            scene->addEllipse(r2x, r2y, 4, 4, penGreen);
//        }
//        if (r2 > l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penRedLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penRed);
//            scene->addEllipse(r2x, r2y, 4, 4, penRed);
//        }
//        if (r2 < l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penBlueLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penBlue);
//            scene->addEllipse(r2x, r2y, 4, 4, penBlue);
//        }
//    }
}

void MainWindow::r3l3()
{
scene->addEllipse(r3x, r3, 4, 4, penRed);
scene->addEllipse(l3x, l3, 4, 4, penRed);
//    if (r2 > 0)
//    {
//        switch (r2)
//        {
//            case 5:  r2y = 000; break;
//            case 10: r2y = 000; break;
//            case 15: r2y = 000; break;
//            case 20: r2y = 000; break;
//            case 25: r2y = 000; break;
//            case 30: r2y = 000; break;
//            case 35: r2y = 000; break;
//            case 40: r2y = 000; break;
//            case 45: r2y = 000; break;
//            case 50: r2y = 000; break;
//            case 55: r2y = 000; break;
//            case 60: r2y = 000; break;
//            case 65: r2y = 000; break;
//            case 70: r2y = 000; break;
//            case 75: r2y = 000; break;
//            case 80: r2y = 000; break;
//            case 85: r2y = 000; break;
//            case 90: r2y = 000; break;
//            case 95: r2y = 000; break;
//            case 100: r2y = 000; break;
//            case 105: r2y = 000; break;
//            case 110: r2y = 000; break;
//            case 115: r2y = 000; break;
//            case 120: r2y = 000; break;
//            case 125: r2y = 000; break;
//            case 130: r2y = 000; break;
//            case 135: r2y = 000; break;
//            case 140: r2y = 000; break;
//            case 145: r2y = 000; break;
//            case 150: r2y = 000; break;
//            case 155: r2y = 000; break;
//            case 160: r2y = 000; break;
//            case 165: r2y = 000; break;
//            case 170: r2y = 000; break;
//            case 175: r2y = 000; break;
//            case 180: r2y = 000; break;
//            case 185: r2y = 000; break;
//            case 190: r2y = 000; break;
//        }
//        scene->addEllipse(r2x, r2y, 4, 4, penYellow);
//    }// r2
//    if (l2>0)
//    {
//        switch (l2)
//        {
//            case 5:  l2y = 000; break;
//            case 10: l2y = 000; break;
//            case 15: l2y = 000; break;
//            case 20: l2y = 000; break;
//            case 25: l2y = 000; break;
//            case 30: l2y = 000; break;
//            case 35: l2y = 000; break;
//            case 40: l2y = 000; break;
//            case 45: l2y = 000; break;
//            case 50: l2y = 000; break;
//            case 55: l2y = 000; break;
//            case 60: l2y = 000; break;
//            case 65: l2y = 000; break;
//            case 70: l2y = 000; break;
//            case 75: l2y = 000; break;
//            case 80: l2y = 000; break;
//            case 85: l2y = 000; break;
//            case 90: l2y = 000; break;
//            case 95: l2y = 000; break;
//            case 100: l2y = 000; break;
//            case 105: l2y = 000; break;
//            case 110: l2y = 000; break;
//            case 115: l2y = 000; break;
//            case 120: l2y = 000; break;
//            case 125: l2y = 000; break;
//            case 130: l2y = 000; break;
//            case 135: l2y = 000; break;
//            case 140: l2y = 000; break;
//            case 145: l2y = 000; break;
//            case 150: l2y = 000; break;
//            case 155: l2y = 000; break;
//            case 160: l2y = 000; break;
//            case 165: l2y = 000; break;
//            case 170: l2y = 000; break;
//            case 175: l2y = 000; break;
//            case 180: l2y = 000; break;
//            case 185: l2y = 000; break;
//            case 190: l2y = 000; break;
//        }
//        scene->addEllipse(l2x, l2y, 4, 4, penYellow);
//    }
//    if (r2 > 0 && l2 > 0)
//    {
//        if (r2 == l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penGreenLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penGreen);
//            scene->addEllipse(r2x, r2y, 4, 4, penGreen);
//        }
//        if (r2 > l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penRedLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penRed);
//            scene->addEllipse(r2x, r2y, 4, 4, penRed);
//        }
//        if (r2 < l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penBlueLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penBlue);
//            scene->addEllipse(r2x, r2y, 4, 4, penBlue);
//        }
//    }
}

void MainWindow::r4l4()
{
scene->addEllipse(r4x, r4, 4, 4, penRed);
scene->addEllipse(l4x, l4, 4, 4, penRed);
//    if (r2 > 0)
//    {
//        switch (r2)
//        {
//            case 5:  r2y = 000; break;
//            case 10: r2y = 000; break;
//            case 15: r2y = 000; break;
//            case 20: r2y = 000; break;
//            case 25: r2y = 000; break;
//            case 30: r2y = 000; break;
//            case 35: r2y = 000; break;
//            case 40: r2y = 000; break;
//            case 45: r2y = 000; break;
//            case 50: r2y = 000; break;
//            case 55: r2y = 000; break;
//            case 60: r2y = 000; break;
//            case 65: r2y = 000; break;
//            case 70: r2y = 000; break;
//            case 75: r2y = 000; break;
//            case 80: r2y = 000; break;
//            case 85: r2y = 000; break;
//            case 90: r2y = 000; break;
//            case 95: r2y = 000; break;
//            case 100: r2y = 000; break;
//            case 105: r2y = 000; break;
//            case 110: r2y = 000; break;
//            case 115: r2y = 000; break;
//            case 120: r2y = 000; break;
//            case 125: r2y = 000; break;
//            case 130: r2y = 000; break;
//            case 135: r2y = 000; break;
//            case 140: r2y = 000; break;
//            case 145: r2y = 000; break;
//            case 150: r2y = 000; break;
//            case 155: r2y = 000; break;
//            case 160: r2y = 000; break;
//            case 165: r2y = 000; break;
//            case 170: r2y = 000; break;
//            case 175: r2y = 000; break;
//            case 180: r2y = 000; break;
//            case 185: r2y = 000; break;
//            case 190: r2y = 000; break;
//        }
//        scene->addEllipse(r2x, r2y, 4, 4, penYellow);
//    }// r2
//    if (l2>0)
//    {
//        switch (l2)
//        {
//            case 5:  l2y = 000; break;
//            case 10: l2y = 000; break;
//            case 15: l2y = 000; break;
//            case 20: l2y = 000; break;
//            case 25: l2y = 000; break;
//            case 30: l2y = 000; break;
//            case 35: l2y = 000; break;
//            case 40: l2y = 000; break;
//            case 45: l2y = 000; break;
//            case 50: l2y = 000; break;
//            case 55: l2y = 000; break;
//            case 60: l2y = 000; break;
//            case 65: l2y = 000; break;
//            case 70: l2y = 000; break;
//            case 75: l2y = 000; break;
//            case 80: l2y = 000; break;
//            case 85: l2y = 000; break;
//            case 90: l2y = 000; break;
//            case 95: l2y = 000; break;
//            case 100: l2y = 000; break;
//            case 105: l2y = 000; break;
//            case 110: l2y = 000; break;
//            case 115: l2y = 000; break;
//            case 120: l2y = 000; break;
//            case 125: l2y = 000; break;
//            case 130: l2y = 000; break;
//            case 135: l2y = 000; break;
//            case 140: l2y = 000; break;
//            case 145: l2y = 000; break;
//            case 150: l2y = 000; break;
//            case 155: l2y = 000; break;
//            case 160: l2y = 000; break;
//            case 165: l2y = 000; break;
//            case 170: l2y = 000; break;
//            case 175: l2y = 000; break;
//            case 180: l2y = 000; break;
//            case 185: l2y = 000; break;
//            case 190: l2y = 000; break;
//        }
//        scene->addEllipse(l2x, l2y, 4, 4, penYellow);
//    }
//    if (r2 > 0 && l2 > 0)
//    {
//        if (r2 == l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penGreenLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penGreen);
//            scene->addEllipse(r2x, r2y, 4, 4, penGreen);
//        }
//        if (r2 > l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penRedLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penRed);
//            scene->addEllipse(r2x, r2y, 4, 4, penRed);
//        }
//        if (r2 < l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penBlueLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penBlue);
//            scene->addEllipse(r2x, r2y, 4, 4, penBlue);
//        }
//    }
}

void MainWindow::r5l5()
{
scene->addEllipse(r5x, r5, 4, 4, penRed);
scene->addEllipse(l5x, l5, 4, 4, penRed);
//    if (r2 > 0)
//    {
//        switch (r2)
//        {
//            case 5:  r2y = 000; break;
//            case 10: r2y = 000; break;
//            case 15: r2y = 000; break;
//            case 20: r2y = 000; break;
//            case 25: r2y = 000; break;
//            case 30: r2y = 000; break;
//            case 35: r2y = 000; break;
//            case 40: r2y = 000; break;
//            case 45: r2y = 000; break;
//            case 50: r2y = 000; break;
//            case 55: r2y = 000; break;
//            case 60: r2y = 000; break;
//            case 65: r2y = 000; break;
//            case 70: r2y = 000; break;
//            case 75: r2y = 000; break;
//            case 80: r2y = 000; break;
//            case 85: r2y = 000; break;
//            case 90: r2y = 000; break;
//            case 95: r2y = 000; break;
//            case 100: r2y = 000; break;
//            case 105: r2y = 000; break;
//            case 110: r2y = 000; break;
//            case 115: r2y = 000; break;
//            case 120: r2y = 000; break;
//            case 125: r2y = 000; break;
//            case 130: r2y = 000; break;
//            case 135: r2y = 000; break;
//            case 140: r2y = 000; break;
//            case 145: r2y = 000; break;
//            case 150: r2y = 000; break;
//            case 155: r2y = 000; break;
//            case 160: r2y = 000; break;
//            case 165: r2y = 000; break;
//            case 170: r2y = 000; break;
//            case 175: r2y = 000; break;
//            case 180: r2y = 000; break;
//            case 185: r2y = 000; break;
//            case 190: r2y = 000; break;
//        }
//        scene->addEllipse(r2x, r2y, 4, 4, penYellow);
//    }// r2
//    if (l2>0)
//    {
//        switch (l2)
//        {
//            case 5:  l2y = 000; break;
//            case 10: l2y = 000; break;
//            case 15: l2y = 000; break;
//            case 20: l2y = 000; break;
//            case 25: l2y = 000; break;
//            case 30: l2y = 000; break;
//            case 35: l2y = 000; break;
//            case 40: l2y = 000; break;
//            case 45: l2y = 000; break;
//            case 50: l2y = 000; break;
//            case 55: l2y = 000; break;
//            case 60: l2y = 000; break;
//            case 65: l2y = 000; break;
//            case 70: l2y = 000; break;
//            case 75: l2y = 000; break;
//            case 80: l2y = 000; break;
//            case 85: l2y = 000; break;
//            case 90: l2y = 000; break;
//            case 95: l2y = 000; break;
//            case 100: l2y = 000; break;
//            case 105: l2y = 000; break;
//            case 110: l2y = 000; break;
//            case 115: l2y = 000; break;
//            case 120: l2y = 000; break;
//            case 125: l2y = 000; break;
//            case 130: l2y = 000; break;
//            case 135: l2y = 000; break;
//            case 140: l2y = 000; break;
//            case 145: l2y = 000; break;
//            case 150: l2y = 000; break;
//            case 155: l2y = 000; break;
//            case 160: l2y = 000; break;
//            case 165: l2y = 000; break;
//            case 170: l2y = 000; break;
//            case 175: l2y = 000; break;
//            case 180: l2y = 000; break;
//            case 185: l2y = 000; break;
//            case 190: l2y = 000; break;
//        }
//        scene->addEllipse(l2x, l2y, 4, 4, penYellow);
//    }
//    if (r2 > 0 && l2 > 0)
//    {
//        if (r2 == l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penGreenLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penGreen);
//            scene->addEllipse(r2x, r2y, 4, 4, penGreen);
//        }
//        if (r2 > l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penRedLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penRed);
//            scene->addEllipse(r2x, r2y, 4, 4, penRed);
//        }
//        if (r2 < l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penBlueLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penBlue);
//            scene->addEllipse(r2x, r2y, 4, 4, penBlue);
//        }
//    }
}

void MainWindow::r6l6()
{
scene->addEllipse(r6x, r6, 4, 4, penRed);
scene->addEllipse(l6x, l6, 4, 4, penRed);
//    if (r2 > 0)
//    {
//        switch (r2)
//        {
//            case 5:  r2y = 000; break;
//            case 10: r2y = 000; break;
//            case 15: r2y = 000; break;
//            case 20: r2y = 000; break;
//            case 25: r2y = 000; break;
//            case 30: r2y = 000; break;
//            case 35: r2y = 000; break;
//            case 40: r2y = 000; break;
//            case 45: r2y = 000; break;
//            case 50: r2y = 000; break;
//            case 55: r2y = 000; break;
//            case 60: r2y = 000; break;
//            case 65: r2y = 000; break;
//            case 70: r2y = 000; break;
//            case 75: r2y = 000; break;
//            case 80: r2y = 000; break;
//            case 85: r2y = 000; break;
//            case 90: r2y = 000; break;
//            case 95: r2y = 000; break;
//            case 100: r2y = 000; break;
//            case 105: r2y = 000; break;
//            case 110: r2y = 000; break;
//            case 115: r2y = 000; break;
//            case 120: r2y = 000; break;
//            case 125: r2y = 000; break;
//            case 130: r2y = 000; break;
//            case 135: r2y = 000; break;
//            case 140: r2y = 000; break;
//            case 145: r2y = 000; break;
//            case 150: r2y = 000; break;
//            case 155: r2y = 000; break;
//            case 160: r2y = 000; break;
//            case 165: r2y = 000; break;
//            case 170: r2y = 000; break;
//            case 175: r2y = 000; break;
//            case 180: r2y = 000; break;
//            case 185: r2y = 000; break;
//            case 190: r2y = 000; break;
//        }
//        scene->addEllipse(r2x, r2y, 4, 4, penYellow);
//    }// r2
//    if (l2>0)
//    {
//        switch (l2)
//        {
//            case 5:  l2y = 000; break;
//            case 10: l2y = 000; break;
//            case 15: l2y = 000; break;
//            case 20: l2y = 000; break;
//            case 25: l2y = 000; break;
//            case 30: l2y = 000; break;
//            case 35: l2y = 000; break;
//            case 40: l2y = 000; break;
//            case 45: l2y = 000; break;
//            case 50: l2y = 000; break;
//            case 55: l2y = 000; break;
//            case 60: l2y = 000; break;
//            case 65: l2y = 000; break;
//            case 70: l2y = 000; break;
//            case 75: l2y = 000; break;
//            case 80: l2y = 000; break;
//            case 85: l2y = 000; break;
//            case 90: l2y = 000; break;
//            case 95: l2y = 000; break;
//            case 100: l2y = 000; break;
//            case 105: l2y = 000; break;
//            case 110: l2y = 000; break;
//            case 115: l2y = 000; break;
//            case 120: l2y = 000; break;
//            case 125: l2y = 000; break;
//            case 130: l2y = 000; break;
//            case 135: l2y = 000; break;
//            case 140: l2y = 000; break;
//            case 145: l2y = 000; break;
//            case 150: l2y = 000; break;
//            case 155: l2y = 000; break;
//            case 160: l2y = 000; break;
//            case 165: l2y = 000; break;
//            case 170: l2y = 000; break;
//            case 175: l2y = 000; break;
//            case 180: l2y = 000; break;
//            case 185: l2y = 000; break;
//            case 190: l2y = 000; break;
//        }
//        scene->addEllipse(l2x, l2y, 4, 4, penYellow);
//    }
//    if (r2 > 0 && l2 > 0)
//    {
//        if (r2 == l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penGreenLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penGreen);
//            scene->addEllipse(r2x, r2y, 4, 4, penGreen);
//        }
//        if (r2 > l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penRedLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penRed);
//            scene->addEllipse(r2x, r2y, 4, 4, penRed);
//        }
//        if (r2 < l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penBlueLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penBlue);
//            scene->addEllipse(r2x, r2y, 4, 4, penBlue);
//        }
//    }
}

void MainWindow::r7l7()
{
scene->addEllipse(r7x, r7, 4, 4, penRed);
scene->addEllipse(l7x, l7, 4, 4, penRed);
//    if (r2 > 0)
//    {
//        switch (r2)
//        {
//            case 5:  r2y = 000; break;
//            case 10: r2y = 000; break;
//            case 15: r2y = 000; break;
//            case 20: r2y = 000; break;
//            case 25: r2y = 000; break;
//            case 30: r2y = 000; break;
//            case 35: r2y = 000; break;
//            case 40: r2y = 000; break;
//            case 45: r2y = 000; break;
//            case 50: r2y = 000; break;
//            case 55: r2y = 000; break;
//            case 60: r2y = 000; break;
//            case 65: r2y = 000; break;
//            case 70: r2y = 000; break;
//            case 75: r2y = 000; break;
//            case 80: r2y = 000; break;
//            case 85: r2y = 000; break;
//            case 90: r2y = 000; break;
//            case 95: r2y = 000; break;
//            case 100: r2y = 000; break;
//            case 105: r2y = 000; break;
//            case 110: r2y = 000; break;
//            case 115: r2y = 000; break;
//            case 120: r2y = 000; break;
//            case 125: r2y = 000; break;
//            case 130: r2y = 000; break;
//            case 135: r2y = 000; break;
//            case 140: r2y = 000; break;
//            case 145: r2y = 000; break;
//            case 150: r2y = 000; break;
//            case 155: r2y = 000; break;
//            case 160: r2y = 000; break;
//            case 165: r2y = 000; break;
//            case 170: r2y = 000; break;
//            case 175: r2y = 000; break;
//            case 180: r2y = 000; break;
//            case 185: r2y = 000; break;
//            case 190: r2y = 000; break;
//        }
//        scene->addEllipse(r2x, r2y, 4, 4, penYellow);
//    }// r2
//    if (l2>0)
//    {
//        switch (l2)
//        {
//            case 5:  l2y = 000; break;
//            case 10: l2y = 000; break;
//            case 15: l2y = 000; break;
//            case 20: l2y = 000; break;
//            case 25: l2y = 000; break;
//            case 30: l2y = 000; break;
//            case 35: l2y = 000; break;
//            case 40: l2y = 000; break;
//            case 45: l2y = 000; break;
//            case 50: l2y = 000; break;
//            case 55: l2y = 000; break;
//            case 60: l2y = 000; break;
//            case 65: l2y = 000; break;
//            case 70: l2y = 000; break;
//            case 75: l2y = 000; break;
//            case 80: l2y = 000; break;
//            case 85: l2y = 000; break;
//            case 90: l2y = 000; break;
//            case 95: l2y = 000; break;
//            case 100: l2y = 000; break;
//            case 105: l2y = 000; break;
//            case 110: l2y = 000; break;
//            case 115: l2y = 000; break;
//            case 120: l2y = 000; break;
//            case 125: l2y = 000; break;
//            case 130: l2y = 000; break;
//            case 135: l2y = 000; break;
//            case 140: l2y = 000; break;
//            case 145: l2y = 000; break;
//            case 150: l2y = 000; break;
//            case 155: l2y = 000; break;
//            case 160: l2y = 000; break;
//            case 165: l2y = 000; break;
//            case 170: l2y = 000; break;
//            case 175: l2y = 000; break;
//            case 180: l2y = 000; break;
//            case 185: l2y = 000; break;
//            case 190: l2y = 000; break;
//        }
//        scene->addEllipse(l2x, l2y, 4, 4, penYellow);
//    }
//    if (r2 > 0 && l2 > 0)
//    {
//        if (r2 == l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penGreenLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penGreen);
//            scene->addEllipse(r2x, r2y, 4, 4, penGreen);
//        }
//        if (r2 > l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penRedLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penRed);
//            scene->addEllipse(r2x, r2y, 4, 4, penRed);
//        }
//        if (r2 < l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penBlueLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penBlue);
//            scene->addEllipse(r2x, r2y, 4, 4, penBlue);
//        }
//    }
}

void MainWindow::r8l8()
{
scene->addEllipse(r8x, r8, 4, 4, penRed);
scene->addEllipse(l8x, l8, 4, 4, penRed);
//    if (r2 > 0)
//    {
//        switch (r2)
//        {
//            case 5:  r2y = 000; break;
//            case 10: r2y = 000; break;
//            case 15: r2y = 000; break;
//            case 20: r2y = 000; break;
//            case 25: r2y = 000; break;
//            case 30: r2y = 000; break;
//            case 35: r2y = 000; break;
//            case 40: r2y = 000; break;
//            case 45: r2y = 000; break;
//            case 50: r2y = 000; break;
//            case 55: r2y = 000; break;
//            case 60: r2y = 000; break;
//            case 65: r2y = 000; break;
//            case 70: r2y = 000; break;
//            case 75: r2y = 000; break;
//            case 80: r2y = 000; break;
//            case 85: r2y = 000; break;
//            case 90: r2y = 000; break;
//            case 95: r2y = 000; break;
//            case 100: r2y = 000; break;
//            case 105: r2y = 000; break;
//            case 110: r2y = 000; break;
//            case 115: r2y = 000; break;
//            case 120: r2y = 000; break;
//            case 125: r2y = 000; break;
//            case 130: r2y = 000; break;
//            case 135: r2y = 000; break;
//            case 140: r2y = 000; break;
//            case 145: r2y = 000; break;
//            case 150: r2y = 000; break;
//            case 155: r2y = 000; break;
//            case 160: r2y = 000; break;
//            case 165: r2y = 000; break;
//            case 170: r2y = 000; break;
//            case 175: r2y = 000; break;
//            case 180: r2y = 000; break;
//            case 185: r2y = 000; break;
//            case 190: r2y = 000; break;
//        }
//        scene->addEllipse(r2x, r2y, 4, 4, penYellow);
//    }// r2
//    if (l2>0)
//    {
//        switch (l2)
//        {
//            case 5:  l2y = 000; break;
//            case 10: l2y = 000; break;
//            case 15: l2y = 000; break;
//            case 20: l2y = 000; break;
//            case 25: l2y = 000; break;
//            case 30: l2y = 000; break;
//            case 35: l2y = 000; break;
//            case 40: l2y = 000; break;
//            case 45: l2y = 000; break;
//            case 50: l2y = 000; break;
//            case 55: l2y = 000; break;
//            case 60: l2y = 000; break;
//            case 65: l2y = 000; break;
//            case 70: l2y = 000; break;
//            case 75: l2y = 000; break;
//            case 80: l2y = 000; break;
//            case 85: l2y = 000; break;
//            case 90: l2y = 000; break;
//            case 95: l2y = 000; break;
//            case 100: l2y = 000; break;
//            case 105: l2y = 000; break;
//            case 110: l2y = 000; break;
//            case 115: l2y = 000; break;
//            case 120: l2y = 000; break;
//            case 125: l2y = 000; break;
//            case 130: l2y = 000; break;
//            case 135: l2y = 000; break;
//            case 140: l2y = 000; break;
//            case 145: l2y = 000; break;
//            case 150: l2y = 000; break;
//            case 155: l2y = 000; break;
//            case 160: l2y = 000; break;
//            case 165: l2y = 000; break;
//            case 170: l2y = 000; break;
//            case 175: l2y = 000; break;
//            case 180: l2y = 000; break;
//            case 185: l2y = 000; break;
//            case 190: l2y = 000; break;
//        }
//        scene->addEllipse(l2x, l2y, 4, 4, penYellow);
//    }
//    if (r2 > 0 && l2 > 0)
//    {
//        if (r2 == l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penGreenLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penGreen);
//            scene->addEllipse(r2x, r2y, 4, 4, penGreen);
//        }
//        if (r2 > l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penRedLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penRed);
//            scene->addEllipse(r2x, r2y, 4, 4, penRed);
//        }
//        if (r2 < l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penBlueLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penBlue);
//            scene->addEllipse(r2x, r2y, 4, 4, penBlue);
//        }
//    }
}

void MainWindow::r9l9()
{
scene->addEllipse(r9x, r9, 4, 4, penRed);
scene->addEllipse(l9x, l9, 4, 4, penRed);
//    if (r2 > 0)
//    {
//        switch (r2)
//        {
//            case 5:  r2y = 000; break;
//            case 10: r2y = 000; break;
//            case 15: r2y = 000; break;
//            case 20: r2y = 000; break;
//            case 25: r2y = 000; break;
//            case 30: r2y = 000; break;
//            case 35: r2y = 000; break;
//            case 40: r2y = 000; break;
//            case 45: r2y = 000; break;
//            case 50: r2y = 000; break;
//            case 55: r2y = 000; break;
//            case 60: r2y = 000; break;
//            case 65: r2y = 000; break;
//            case 70: r2y = 000; break;
//            case 75: r2y = 000; break;
//            case 80: r2y = 000; break;
//            case 85: r2y = 000; break;
//            case 90: r2y = 000; break;
//            case 95: r2y = 000; break;
//            case 100: r2y = 000; break;
//            case 105: r2y = 000; break;
//            case 110: r2y = 000; break;
//            case 115: r2y = 000; break;
//            case 120: r2y = 000; break;
//            case 125: r2y = 000; break;
//            case 130: r2y = 000; break;
//            case 135: r2y = 000; break;
//            case 140: r2y = 000; break;
//            case 145: r2y = 000; break;
//            case 150: r2y = 000; break;
//            case 155: r2y = 000; break;
//            case 160: r2y = 000; break;
//            case 165: r2y = 000; break;
//            case 170: r2y = 000; break;
//            case 175: r2y = 000; break;
//            case 180: r2y = 000; break;
//            case 185: r2y = 000; break;
//            case 190: r2y = 000; break;
//        }
//        scene->addEllipse(r2x, r2y, 4, 4, penYellow);
//    }// r2
//    if (l2>0)
//    {
//        switch (l2)
//        {
//            case 5:  l2y = 000; break;
//            case 10: l2y = 000; break;
//            case 15: l2y = 000; break;
//            case 20: l2y = 000; break;
//            case 25: l2y = 000; break;
//            case 30: l2y = 000; break;
//            case 35: l2y = 000; break;
//            case 40: l2y = 000; break;
//            case 45: l2y = 000; break;
//            case 50: l2y = 000; break;
//            case 55: l2y = 000; break;
//            case 60: l2y = 000; break;
//            case 65: l2y = 000; break;
//            case 70: l2y = 000; break;
//            case 75: l2y = 000; break;
//            case 80: l2y = 000; break;
//            case 85: l2y = 000; break;
//            case 90: l2y = 000; break;
//            case 95: l2y = 000; break;
//            case 100: l2y = 000; break;
//            case 105: l2y = 000; break;
//            case 110: l2y = 000; break;
//            case 115: l2y = 000; break;
//            case 120: l2y = 000; break;
//            case 125: l2y = 000; break;
//            case 130: l2y = 000; break;
//            case 135: l2y = 000; break;
//            case 140: l2y = 000; break;
//            case 145: l2y = 000; break;
//            case 150: l2y = 000; break;
//            case 155: l2y = 000; break;
//            case 160: l2y = 000; break;
//            case 165: l2y = 000; break;
//            case 170: l2y = 000; break;
//            case 175: l2y = 000; break;
//            case 180: l2y = 000; break;
//            case 185: l2y = 000; break;
//            case 190: l2y = 000; break;
//        }
//        scene->addEllipse(l2x, l2y, 4, 4, penYellow);
//    }
//    if (r2 > 0 && l2 > 0)
//    {
//        if (r2 == l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penGreenLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penGreen);
//            scene->addEllipse(r2x, r2y, 4, 4, penGreen);
//        }
//        if (r2 > l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penRedLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penRed);
//            scene->addEllipse(r2x, r2y, 4, 4, penRed);
//        }
//        if (r2 < l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penBlueLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penBlue);
//            scene->addEllipse(r2x, r2y, 4, 4, penBlue);
//        }
//    }
}

void MainWindow::r10l10()
{
scene->addEllipse(r10x, r10, 4, 4, penRed);
scene->addEllipse(l10x, l10, 4, 4, penRed);
//    if (r2 > 0)
//    {
//        switch (r2)
//        {
//            case 5:  r2y = 000; break;
//            case 10: r2y = 000; break;
//            case 15: r2y = 000; break;
//            case 20: r2y = 000; break;
//            case 25: r2y = 000; break;
//            case 30: r2y = 000; break;
//            case 35: r2y = 000; break;
//            case 40: r2y = 000; break;
//            case 45: r2y = 000; break;
//            case 50: r2y = 000; break;
//            case 55: r2y = 000; break;
//            case 60: r2y = 000; break;
//            case 65: r2y = 000; break;
//            case 70: r2y = 000; break;
//            case 75: r2y = 000; break;
//            case 80: r2y = 000; break;
//            case 85: r2y = 000; break;
//            case 90: r2y = 000; break;
//            case 95: r2y = 000; break;
//            case 100: r2y = 000; break;
//            case 105: r2y = 000; break;
//            case 110: r2y = 000; break;
//            case 115: r2y = 000; break;
//            case 120: r2y = 000; break;
//            case 125: r2y = 000; break;
//            case 130: r2y = 000; break;
//            case 135: r2y = 000; break;
//            case 140: r2y = 000; break;
//            case 145: r2y = 000; break;
//            case 150: r2y = 000; break;
//            case 155: r2y = 000; break;
//            case 160: r2y = 000; break;
//            case 165: r2y = 000; break;
//            case 170: r2y = 000; break;
//            case 175: r2y = 000; break;
//            case 180: r2y = 000; break;
//            case 185: r2y = 000; break;
//            case 190: r2y = 000; break;
//        }
//        scene->addEllipse(r2x, r2y, 4, 4, penYellow);
//    }// r2
//    if (l2>0)
//    {
//        switch (l2)
//        {
//            case 5:  l2y = 000; break;
//            case 10: l2y = 000; break;
//            case 15: l2y = 000; break;
//            case 20: l2y = 000; break;
//            case 25: l2y = 000; break;
//            case 30: l2y = 000; break;
//            case 35: l2y = 000; break;
//            case 40: l2y = 000; break;
//            case 45: l2y = 000; break;
//            case 50: l2y = 000; break;
//            case 55: l2y = 000; break;
//            case 60: l2y = 000; break;
//            case 65: l2y = 000; break;
//            case 70: l2y = 000; break;
//            case 75: l2y = 000; break;
//            case 80: l2y = 000; break;
//            case 85: l2y = 000; break;
//            case 90: l2y = 000; break;
//            case 95: l2y = 000; break;
//            case 100: l2y = 000; break;
//            case 105: l2y = 000; break;
//            case 110: l2y = 000; break;
//            case 115: l2y = 000; break;
//            case 120: l2y = 000; break;
//            case 125: l2y = 000; break;
//            case 130: l2y = 000; break;
//            case 135: l2y = 000; break;
//            case 140: l2y = 000; break;
//            case 145: l2y = 000; break;
//            case 150: l2y = 000; break;
//            case 155: l2y = 000; break;
//            case 160: l2y = 000; break;
//            case 165: l2y = 000; break;
//            case 170: l2y = 000; break;
//            case 175: l2y = 000; break;
//            case 180: l2y = 000; break;
//            case 185: l2y = 000; break;
//            case 190: l2y = 000; break;
//        }
//        scene->addEllipse(l2x, l2y, 4, 4, penYellow);
//    }
//    if (r2 > 0 && l2 > 0)
//    {
//        if (r2 == l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penGreenLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penGreen);
//            scene->addEllipse(r2x, r2y, 4, 4, penGreen);
//        }
//        if (r2 > l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penRedLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penRed);
//            scene->addEllipse(r2x, r2y, 4, 4, penRed);
//        }
//        if (r2 < l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penBlueLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penBlue);
//            scene->addEllipse(r2x, r2y, 4, 4, penBlue);
//        }
//    }
}

void MainWindow::r11l11()
{
scene->addEllipse(r11x, r11, 4, 4, penRed);
scene->addEllipse(l11x, l11, 4, 4, penRed);
//    if (r2 > 0)
//    {
//        switch (r2)
//        {
//            case 5:  r2y = 000; break;
//            case 10: r2y = 000; break;
//            case 15: r2y = 000; break;
//            case 20: r2y = 000; break;
//            case 25: r2y = 000; break;
//            case 30: r2y = 000; break;
//            case 35: r2y = 000; break;
//            case 40: r2y = 000; break;
//            case 45: r2y = 000; break;
//            case 50: r2y = 000; break;
//            case 55: r2y = 000; break;
//            case 60: r2y = 000; break;
//            case 65: r2y = 000; break;
//            case 70: r2y = 000; break;
//            case 75: r2y = 000; break;
//            case 80: r2y = 000; break;
//            case 85: r2y = 000; break;
//            case 90: r2y = 000; break;
//            case 95: r2y = 000; break;
//            case 100: r2y = 000; break;
//            case 105: r2y = 000; break;
//            case 110: r2y = 000; break;
//            case 115: r2y = 000; break;
//            case 120: r2y = 000; break;
//            case 125: r2y = 000; break;
//            case 130: r2y = 000; break;
//            case 135: r2y = 000; break;
//            case 140: r2y = 000; break;
//            case 145: r2y = 000; break;
//            case 150: r2y = 000; break;
//            case 155: r2y = 000; break;
//            case 160: r2y = 000; break;
//            case 165: r2y = 000; break;
//            case 170: r2y = 000; break;
//            case 175: r2y = 000; break;
//            case 180: r2y = 000; break;
//            case 185: r2y = 000; break;
//            case 190: r2y = 000; break;
//        }
//        scene->addEllipse(r2x, r2y, 4, 4, penYellow);
//    }// r2
//    if (l2>0)
//    {
//        switch (l2)
//        {
//            case 5:  l2y = 000; break;
//            case 10: l2y = 000; break;
//            case 15: l2y = 000; break;
//            case 20: l2y = 000; break;
//            case 25: l2y = 000; break;
//            case 30: l2y = 000; break;
//            case 35: l2y = 000; break;
//            case 40: l2y = 000; break;
//            case 45: l2y = 000; break;
//            case 50: l2y = 000; break;
//            case 55: l2y = 000; break;
//            case 60: l2y = 000; break;
//            case 65: l2y = 000; break;
//            case 70: l2y = 000; break;
//            case 75: l2y = 000; break;
//            case 80: l2y = 000; break;
//            case 85: l2y = 000; break;
//            case 90: l2y = 000; break;
//            case 95: l2y = 000; break;
//            case 100: l2y = 000; break;
//            case 105: l2y = 000; break;
//            case 110: l2y = 000; break;
//            case 115: l2y = 000; break;
//            case 120: l2y = 000; break;
//            case 125: l2y = 000; break;
//            case 130: l2y = 000; break;
//            case 135: l2y = 000; break;
//            case 140: l2y = 000; break;
//            case 145: l2y = 000; break;
//            case 150: l2y = 000; break;
//            case 155: l2y = 000; break;
//            case 160: l2y = 000; break;
//            case 165: l2y = 000; break;
//            case 170: l2y = 000; break;
//            case 175: l2y = 000; break;
//            case 180: l2y = 000; break;
//            case 185: l2y = 000; break;
//            case 190: l2y = 000; break;
//        }
//        scene->addEllipse(l2x, l2y, 4, 4, penYellow);
//    }
//    if (r2 > 0 && l2 > 0)
//    {
//        if (r2 == l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penGreenLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penGreen);
//            scene->addEllipse(r2x, r2y, 4, 4, penGreen);
//        }
//        if (r2 > l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penRedLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penRed);
//            scene->addEllipse(r2x, r2y, 4, 4, penRed);
//        }
//        if (r2 < l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penBlueLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penBlue);
//            scene->addEllipse(r2x, r2y, 4, 4, penBlue);
//        }
//    }
}

void MainWindow::r12l12()
{
    scene->addEllipse(r12x, r12, 4, 4, penRed);
    scene->addEllipse(l12x, l12, 4, 4, penRed);
//    if (r2 > 0)
//    {
//        switch (r2)
//        {
//            case 5:  r2y = 000; break;
//            case 10: r2y = 000; break;
//            case 15: r2y = 000; break;
//            case 20: r2y = 000; break;
//            case 25: r2y = 000; break;
//            case 30: r2y = 000; break;
//            case 35: r2y = 000; break;
//            case 40: r2y = 000; break;
//            case 45: r2y = 000; break;
//            case 50: r2y = 000; break;
//            case 55: r2y = 000; break;
//            case 60: r2y = 000; break;
//            case 65: r2y = 000; break;
//            case 70: r2y = 000; break;
//            case 75: r2y = 000; break;
//            case 80: r2y = 000; break;
//            case 85: r2y = 000; break;
//            case 90: r2y = 000; break;
//            case 95: r2y = 000; break;
//            case 100: r2y = 000; break;
//            case 105: r2y = 000; break;
//            case 110: r2y = 000; break;
//            case 115: r2y = 000; break;
//            case 120: r2y = 000; break;
//            case 125: r2y = 000; break;
//            case 130: r2y = 000; break;
//            case 135: r2y = 000; break;
//            case 140: r2y = 000; break;
//            case 145: r2y = 000; break;
//            case 150: r2y = 000; break;
//            case 155: r2y = 000; break;
//            case 160: r2y = 000; break;
//            case 165: r2y = 000; break;
//            case 170: r2y = 000; break;
//            case 175: r2y = 000; break;
//            case 180: r2y = 000; break;
//            case 185: r2y = 000; break;
//            case 190: r2y = 000; break;
//        }
//        scene->addEllipse(r2x, r2y, 4, 4, penYellow);
//    }// r2
//    if (l2>0)
//    {
//        switch (l2)
//        {
//            case 5:  l2y = 000; break;
//            case 10: l2y = 000; break;
//            case 15: l2y = 000; break;
//            case 20: l2y = 000; break;
//            case 25: l2y = 000; break;
//            case 30: l2y = 000; break;
//            case 35: l2y = 000; break;
//            case 40: l2y = 000; break;
//            case 45: l2y = 000; break;
//            case 50: l2y = 000; break;
//            case 55: l2y = 000; break;
//            case 60: l2y = 000; break;
//            case 65: l2y = 000; break;
//            case 70: l2y = 000; break;
//            case 75: l2y = 000; break;
//            case 80: l2y = 000; break;
//            case 85: l2y = 000; break;
//            case 90: l2y = 000; break;
//            case 95: l2y = 000; break;
//            case 100: l2y = 000; break;
//            case 105: l2y = 000; break;
//            case 110: l2y = 000; break;
//            case 115: l2y = 000; break;
//            case 120: l2y = 000; break;
//            case 125: l2y = 000; break;
//            case 130: l2y = 000; break;
//            case 135: l2y = 000; break;
//            case 140: l2y = 000; break;
//            case 145: l2y = 000; break;
//            case 150: l2y = 000; break;
//            case 155: l2y = 000; break;
//            case 160: l2y = 000; break;
//            case 165: l2y = 000; break;
//            case 170: l2y = 000; break;
//            case 175: l2y = 000; break;
//            case 180: l2y = 000; break;
//            case 185: l2y = 000; break;
//            case 190: l2y = 000; break;
//        }
//        scene->addEllipse(l2x, l2y, 4, 4, penYellow);
//    }
//    if (r2 > 0 && l2 > 0)
//    {
//        if (r2 == l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penGreenLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penGreen);
//            scene->addEllipse(r2x, r2y, 4, 4, penGreen);
//        }
//        if (r2 > l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penRedLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penRed);
//            scene->addEllipse(r2x, r2y, 4, 4, penRed);
//        }
//        if (r2 < l2)
//        {
//            scene->addLine(r2x,r2y,l2x,l2y, penBlueLine);
//            scene->addEllipse(l2x, l2y, 4, 4, penBlue);
//            scene->addEllipse(r2x, r2y, 4, 4, penBlue);
//        }
//    }
}


void MainWindow::drawPoints()
{
    //        scene->addEllipse(123,r1,4,4,penRed);

    scene->clear();
    r1l1();
    r2l2();
    r3l3();
    r4l4();
    r5l5();
    r6l6();
    r7l7();
    r8l8();
    r9l9();
    r10l10();
    r11l11();
    r12l12();
}

void MainWindow::on_r_1_editingFinished()
{
    r1 = ui->r_1->text().toInt();
    cout<< "r1: " << r1 << endl;
    drawPoints();
}
void MainWindow::on_r_2_editingFinished()
{
    r2 = ui->r_2->text().toInt();
    cout<< "r2: " << r2 << endl;
    drawPoints();
}
void MainWindow::on_r_3_editingFinished()
{
    r3 = ui->r_3->text().toInt();
    cout<< "r3: " << r3 << endl;
    drawPoints();
}
void MainWindow::on_r_4_editingFinished()
{
    r4 = ui->r_4->text().toInt();
    cout<< "r4: " << r4 << endl;
    drawPoints();
}
void MainWindow::on_r_5_editingFinished()
{
    r5 = ui->r_5->text().toInt();
    cout<< "r5: " << r5 << endl;
    drawPoints();
}
void MainWindow::on_r_6_editingFinished()
{
    r6 = ui->r_6->text().toInt();
    cout<< "r6: " << r6 << endl;
    drawPoints();
}
void MainWindow::on_r_7_editingFinished()
{
    r7 = ui->r_7->text().toInt();
    cout<< "r7: " << r7 << endl;
    drawPoints();
}
void MainWindow::on_r_8_editingFinished()
{
    r8 = ui->r_8->text().toInt();
    cout<< "r8: " << r8 << endl;
    drawPoints();
}
void MainWindow::on_r_9_editingFinished()
{
    r9 = ui->r_9->text().toInt();
    cout<< "r9: " << r9 << endl;
    drawPoints();
}
void MainWindow::on_r_10_editingFinished()
{
    r10 = ui->r_10->text().toInt();
    cout<< "r10: " << r10 << endl;
    drawPoints();
}
void MainWindow::on_r_11_editingFinished()
{
    r11 = ui->r_11->text().toInt();
    cout<< "r11: " << r11 << endl;
    drawPoints();
}
void MainWindow::on_r_12_editingFinished()
{
    r12 = ui->r_12->text().toInt();
    cout<< "r12: " << r12 << endl;
    drawPoints();
}

void MainWindow::on_l_1_editingFinished()
{
    l1 = ui->l_1->text().toInt();
    cout<< "l1: " << l1 << endl;
    drawPoints();
}
void MainWindow::on_l_2_editingFinished()
{
    l2 = ui->l_2->text().toInt();
    cout<< "l2: " << l2 << endl;
    drawPoints();
}
void MainWindow::on_l_3_editingFinished()
{
    l3 = ui->l_3->text().toInt();
    cout<< "l3: " << l3 << endl;
    drawPoints();
}
void MainWindow::on_l_4_editingFinished()
{
    l4 = ui->l_4->text().toInt();
    cout<< "l4: " << l4 << endl;
    drawPoints();
}
void MainWindow::on_l_5_editingFinished()
{
    l5 = ui->l_5->text().toInt();
    cout<< "l5: " << l5 << endl;
    drawPoints();
}
void MainWindow::on_l_6_editingFinished()
{
    l6 = ui->l_6->text().toInt();
    cout<< "l6: " << l6 << endl;
    drawPoints();
}
void MainWindow::on_l_7_editingFinished()
{
    l7 = ui->l_7->text().toInt();
    cout<< "l7: " << l7 << endl;
    drawPoints();
}
void MainWindow::on_l_8_editingFinished()
{
    l8 = ui->l_8->text().toInt();
    cout<< "l8: " << l8 << endl;
    drawPoints();
}
void MainWindow::on_l_9_editingFinished()
{
    l9 = ui->l_9->text().toInt();
    cout<< "l9: " << l9 << endl;
    drawPoints();
}
void MainWindow::on_l_10_editingFinished()
{
    l10 = ui->l_10->text().toInt();
    cout<< "l10: " << l10 << endl;
    drawPoints();
}
void MainWindow::on_l_11_editingFinished()
{
    l11 = ui->l_11->text().toInt();
    cout<< "l11: " << l11 << endl;
    drawPoints();
}
void MainWindow::on_l_12_editingFinished()
{
    l12 = ui->l_12->text().toInt();
    cout<< "l12: " << l12 << endl;
    drawPoints();
}

void MainWindow::on_button_exit_clicked()
{
    app->exit();
}

void MainWindow::on_name_field_textActivated(const QString &arg1)
{
    name_field = arg1;
    cout<< "name_field: " << name_field.toStdString() << endl;
    repaint();
    update();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
//    QPainter p(this);
//    p.setPen(Qt::green);
//    p.drawText(10,10,"hello");
}
