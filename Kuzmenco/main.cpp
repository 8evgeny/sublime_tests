#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <curses.h>
#include <ncursesw/ncurses.h>
#include <math.h>
#include <fstream>

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
//void answer(uint num, string qw1, string qw2, string qw3, string qw4);
string letter(int r, int l );
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);

    answers();

    mvprintw(5, 45, letter(r_1, l_1, k1).c_str());
    mvprintw(6, 45, letter(r_2, l_2, k2).c_str());
    mvprintw(7, 45, letter(r_3, l_3, k3).c_str());
    mvprintw(8, 45, letter(r_4, l_4, k4).c_str());
    mvprintw(9, 45, letter(r_5, l_5, k5).c_str());
    mvprintw(10, 45, letter(r_6, l_6, k6).c_str());

    mvprintw(12, 45, letter(r_7, l_7, k7).c_str());
    mvprintw(13, 45, letter(r_8, l_8, k8).c_str());
    mvprintw(14, 45, letter(r_9, l_9, k9).c_str());
    mvprintw(15, 45, letter(r_10, l_10, k10).c_str());
    mvprintw(16, 45, letter(r_11, l_11, k11).c_str());
    mvprintw(17, 45, letter(r_12, l_12, k12).c_str());

    string nam(name);
    string dat(date);
    string num(to_string(number));

    ofstream fout;
    fout.open(nam + "_" + dat + "_" + num);
    fout <<"Имя: "<< name <<" / Дата: "<<date <<" / №"<<number<<endl<<endl;
    fout << " P\t Легкие\t\t\t\t"<< r_1 <<"\t" << l_1 <<"\t"<< letter(r_1, l_1, k1) << endl;
    fout << " MC\t Перикард\t\t\t"<< r_2 <<"\t" << l_2 <<"\t"<< letter(r_2, l_2, k2) << endl;
    fout << " С\t Сердце\t\t\t\t"<< r_3 <<"\t" << l_3 <<"\t"<< letter(r_3, l_3, k3) << endl;
    fout << " IG\t Тонкий кишечник\t\t"<< r_4 <<"\t" << l_4 <<"\t"<< letter(r_4, l_4, k4) << endl;
    fout << " TR\t Гормональная система\t\t"<< r_5 <<"\t" << l_5 <<"\t"<< letter(r_5, l_5, k5) << endl;
    fout << " GI\t Толстый кишечник\t\t"<< r_6 <<"\t" << l_6 <<"\t"<< letter(r_6, l_6, k6) << endl;
    fout << " " << endl;
    fout << " RP\t Селезенка, Поджелудочная\t"<< r_7 <<"\t" << l_7 <<"\t"<< letter(r_7, l_7, k7) << endl;
    fout << " F\t Печень\t\t\t\t"<< r_8 <<"\t" << l_8 <<"\t"<< letter(r_8, l_8, k8) << endl;
    fout << " R\t Почки\t\t\t\t"<< r_9 <<"\t" << l_9 <<"\t"<< letter(r_9, l_9, k9) << endl;
    fout << " V\t Мочевой пузырь\t\t\t"<< r_10 <<"\t" << l_10 <<"\t"<< letter(r_10, l_10, k10) << endl;
    fout << " VB\t Желчный пузырь\t\t\t"<< r_11 <<"\t" << l_11 <<"\t"<< letter(r_11, l_11, k11) << endl;
    fout << " E\t Желудок\t\t\t"<< r_12 <<"\t" << l_12 <<"\t"<< letter(r_12, l_12, k12) << endl;
    fout << endl<<" Коридор нормы верх: " << average + 7 <<endl;
    fout << " Коридор нормы низ: " << average - 7 <<endl;
    fout << " " << endl;
//    fout << k1 << endl;
//    fout << k2 << endl;
//    fout << k3 << endl;
//    fout << k4 << endl;
//    fout << k5 << endl;
//    fout << k6 << endl;
//    fout << k7 << endl;
//    fout << k8 << endl;
//    fout << k9 << endl;
//    fout << k10 << endl;
//    fout << k11 << endl;
//    fout << k12 << endl;
    fout.close();



    GREEN
//    mvprintw(22, 0, "Для выхода нажмите Ctr-C");

    char tmp[10] ;
    getstr(tmp);

    return a.exec();
}













//    while ( !ex ) {
//        int rc = get_wch(&tmp);
//        if (rc==OK) {
//          ++numCharEntered;
//        }
//        switch (numCharEntered) {
//        case 1:
//            c1 = tmp;
//            if ((c1 != L'д') && (c1 != L'н')){
////            colorMsg(num, qw);
//            mvprintw(num*2-1, 0, "Введите да  или  нет");
//            numCharEntered = 0;
//            }
//            if ((c1 == L'д') || (c1 == L'н')){
////            colorMsg(num, qw);
//            mvprintw(num*2-1, 0, "                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
//            if (c1 == L'д')
//                mvprintw(num*2-1, 0, "д");
//            if (c1 == L'н')
//                mvprintw(num*2-1, 0, "н");
//            }
//            break;

//        case 2:
//            c2 = tmp;
//            if ((c1 == L'д') && (c2 == L'а')){
//                mvprintw(num*2-1, 1, "а");
//            ex = true;
//            }
//            if ((c1 == L'д') && (c2 != L'а')){
////            colorMsg(num, qw);
//            mvprintw(num*2-1, 0, "Введите да  или  нет");
//            numCharEntered = 0;
//            }
//            if ((c1 == L'н') && (c2 == L'е')){
//            mvprintw(num*2-1, 1, "е");
//            }
//            break;
//        case 3:
//            c3 = tmp;
//            if ((c1 == L'н') && (c2 == L'е') && (c3 == L'т')){
//            ex = true;
//            ret = false;
//            }
//            if ((c1 == L'н') && (c2 != L'e')){
////            colorMsg(num, qw);
//            mvprintw(num*2-1, 0, "Введите да  или  нет");
//            numCharEntered = 0;
//            }
//            if ((c1 == L'н') && (c2 == L'e') && (c3 != L'т')){
////            colorMsg(num, qw);
//            mvprintw(num*2-1, 0, "Введите да  или  нет");
//            numCharEntered = 0;
//            }
//            break;
//        default:
//            break;
//        }
//    }
