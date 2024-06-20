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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow * w = new MainWindow;
    w->getUi()->centralwidget->setFixedSize(1850,1000);

    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth = desktop->width();
    int screenHeight = desktop->height();
    int x = (screenWidth - w->width()) / 2;
    int y = (screenHeight - w->height()) / 2;
    w->move(x, y);


    QPixmap      pix("/home/user/SOFT/Github/Sublime_tests/Kuzmenco/table.png");

    QPalette pal;
    pal.setBrush(w->backgroundRole(), QBrush(pix));
    w->getUi()->centralwidget->setGeometry(0,0,1920,1080);

    w->getUi()->frame->setPalette(pal);
    w->getUi()->frame->setAutoFillBackground(true);
    w->getUi()->frame->setFixedSize(pix.width(), pix.height());



//    main_logic();

    w->show();
    a.exec();
}







