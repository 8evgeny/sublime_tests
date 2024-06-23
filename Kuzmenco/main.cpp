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


    QPixmap      pix("../table.png");
    QPalette pal;
    pal.setBrush(w->backgroundRole(), QBrush(pix));
//    QRect rect(20,20,1800,1080);
//    w->getUi()->horizontalLayout->setGeometry(rect);
//w->getUi()->horizontalLayout->setAlignment(w->getUi()->widget,Qt::Alignment(Qt::LeftToRight));
    w->getUi()->widget->setPalette(pal);
    w->getUi()->widget->setAutoFillBackground(true);
    w->getUi()->widget->setFixedSize(pix.width(), pix.height() );



//    main_logic();

    w->showFullScreen();
//    w->show();
    app->exec();
}







