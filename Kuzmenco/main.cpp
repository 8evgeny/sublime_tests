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

    auto scene=new QGraphicsScene(w->getUi()->widget); //allocate your scene to your main widget
    auto view=new QGraphicsView(scene, w->getUi()->widget);//here is your view
    view->viewport()->setAutoFillBackground(false);
    auto pixmap=new QPixmap(QSize(2000,1000));// paint device
    QPen pen(Qt::red);//Просто выбираем цвет для карандашика
    pen.setWidth(5);
    scene->addLine(0,190,500,90,pen);//x
    scene->addLine(500,0,500,180,pen);//y

//    main_logic();

    w->showFullScreen();
    app->exec();
}







