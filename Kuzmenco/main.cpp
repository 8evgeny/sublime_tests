#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <curses.h>
#include <ncursesw/ncurses.h>
#include <math.h>
#include <QLabel>
#include <QStyle>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QPixmap>

using namespace std::chrono;
using namespace std;

QApplication * app;



int main(int argc, char *argv[])
{
    app = new QApplication(argc, argv);
    MainWindow * w = new MainWindow;
//    w->getUi()->centralwidget->setFixedSize(1920,1080);

//    QDesktopWidget *desktop = QApplication::desktop();
//    QRect screenres = QApplication::desktop()->screenGeometry(1/*screenNumber*/);
//    int screenWidth = desktop->width();
//    int screenHeight = desktop->height();
//    int x = (screenWidth - w->width()) / 2;
//    int y = (screenHeight - w->height()) / 2;
//    w->move(x, y);


    QPixmap      pix("table.png");
    QPalette pal;
    pal.setBrush(w->backgroundRole(), QBrush(pix));

    w->getUi()->widget->setPalette(pal);
    w->getUi()->widget->setAutoFillBackground(true);
    w->getUi()->widget->setFixedSize(pix.width(), pix.height() );
    w->getUi()->dateEdit->setDate(QDate::currentDate());

    auto scene=new QGraphicsScene(w->getUi()->widget);
    QRect rect(20,20,1200,800);
    scene->setSceneRect(rect);
    auto view=new QGraphicsView(scene, w->getUi()->widget);
    view->viewport()->setAutoFillBackground(false);
    QPen pen(Qt::red);
    pen.setWidth(5);

    scene->addLine(0,190,500,90,pen);
    scene->addLine(500,0,500,180,pen);
    scene->addLine(200,200,500,500,pen);

//    main_logic();

    w->showFullScreen();
    app->exec();
}







