﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QMainWindow>
//#include <curses.h>
//#include <ncursesw/ncurses.h>
#include <math.h>
#include <QLabel>
#include <QStyle>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QPixmap>
#include <QScreen>

using namespace std::chrono;
using namespace std;

QApplication * app;
QPen penRed(Qt::red);
QPen penGreen(Qt::green);
QPen penBlue(Qt::blue);
QPen penYellow(Qt::darkYellow);
QPen penRedLine(Qt::red);
QPen penGreenLine(Qt::green);
QPen penBlueLine(Qt::blue);
QPen penBlack(Qt::black);
QPen penTriangle(Qt::black);
QGraphicsScene * scene;
QScreen *screenMain;

int main(int argc, char *argv[])
{
    app = new QApplication(argc, argv);
    screenMain = app->primaryScreen();

    MainWindow * w = new MainWindow;
    QPixmap      pix("table.png");

    QPalette pal;
    pal.setBrush(w->backgroundRole(), QBrush(pix));

    w->getUi()->widget->setPalette(pal);
    w->getUi()->widget->setAutoFillBackground(true);
    w->getUi()->widget->setFixedSize(pix.width(), pix.height() );
    w->getUi()->dateEdit->setDate(QDate::currentDate());

    scene = new QGraphicsScene(w->getUi()->widget);

    QRect rect(20,20,1200,800);
    scene->setSceneRect(rect);
    auto view=new QGraphicsView(scene, w->getUi()->widget);
    view->viewport()->setAutoFillBackground(false);

    penRed.setWidth(4);
    penGreen.setWidth(4);
    penBlue.setWidth(4);
    penYellow.setWidth(2);
    penRedLine.setWidth(3);
    penGreenLine.setWidth(3);
    penBlueLine.setWidth(3);
    penBlack.setWidth(1);
    penTriangle.setWidth(8);
//    main_logic();

    w->showFullScreen();
    app->exec();
}







