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
#include <QPainter>


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
//    QRect rect(20,20,1800,1080);
//    w->getUi()->horizontalLayout->setGeometry(rect);
//w->getUi()->horizontalLayout->setAlignment(w->getUi()->widget,Qt::Alignment(Qt::LeftToRight));
    w->getUi()->widget->setPalette(pal);
    w->getUi()->widget->setAutoFillBackground(true);
    w->getUi()->widget->setFixedSize(pix.width(), pix.height() );

//    QPainter painter(w->getUi()->graphicsView); // Создаём объект отрисовщика
//graphicsView
//painter.drawLine(0,0,100,100);
//w->getUi()->graphicsView->setBackgroundBrush(QBrush(pix));
//w->getUi()->widget->setScene(scene);
    QGraphicsScene *scene = new QGraphicsScene(w->getUi()->widget);
    //Это как раз создана сцена. Сцена - это класс для работы с 2D графикой.
    //Теперь, раз это график, то построим координатные оси X и Y.
    QPen pen(Qt::green);//Просто выбираем цвет для карандашика
    scene->addLine(0,90,180,90,pen);//x
    scene->addLine(90,0,90,180,pen);//y

//    main_logic();

    w->showFullScreen();
    app->exec();
}







