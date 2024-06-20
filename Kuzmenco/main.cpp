#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <curses.h>
#include <ncursesw/ncurses.h>
#include <math.h>
#include <QLabel>

using namespace std::chrono;
using namespace std;

char name[100];
char date[100];
int number{0}, summ{0};
int r_1{0}, r_2{0}, r_3{0}, r_4{0}, r_5{0}, r_6{0}, l_1{0}, l_2{0}, l_3{0}, l_4{0}, l_5{0}, l_6{0};
int r_7{0}, r_8{0}, r_9{0}, r_10{0}, r_11{0}, r_12{0}, l_7{0}, l_8{0}, l_9{0}, l_10{0}, l_11{0},l_12{0};
float k1 = 90.f/105;
float k2 = 130.f/140.f;
float k3 = 100.f/90;
float k4 = 105.f/110;
float k5 = 110.f/135.f;
float k6 = 110.f/135.f;
float k7 = 1;
float k8 = 75.f/60;
float k9 = 1;
float k10 = 110.f/100;
float k11 = 75.f/60;
float k12 = 90.f/80;
float average{0.0};
float hight{0.0};
float low{0.0};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow * w = new MainWindow;
    w->getUi()->centralwidget->setFixedSize(1850,1000);
//    w.getUi()->centralwidget->

    QPixmap      pix("/home/user/SOFT/Github/Sublime_tests/Kuzmenco/table.png");

    QPalette pal;
    pal.setBrush(w->backgroundRole(), QBrush(pix));
    w->getUi()->frame->setPalette(pal);
    w->getUi()->frame->setAutoFillBackground(true);
    w->getUi()->frame->setFixedSize(pix.width(), pix.height());
//    w->getUi()->centralwidget->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);





//    main_logic();





    w->show();
    a.exec();
}







