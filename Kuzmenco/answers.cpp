#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <curses.h>
#include <ncursesw/ncurses.h>
#include <math.h>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
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

void main_logic()
{
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

    WHITE
    string nam(name);
    string dat(date);
    string num(to_string(number));

    ofstream fout;
    fout.open("../Измерения/" + nam + "   " + dat + "  № " + num);
    fout <<" Имя: "<< name <<" / Дата: "<<date <<" / Измерение № "<<number<<endl<<endl;
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
}



std::string current_time_and_date()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

void answer(uint num, string qw1, string qw2, string qw3, string qw4)
{
    WHITE
    echo();

//    bool ret = true;
//    bool ex = false;
//    uint numCharEntered = 0;
//    wint_t tmp;
//    wint_t c1;
//    wint_t c2;
//    wint_t c3;

    char str[100];
    if (num == 1)
    {
        mvprintw(num, 0, qw4.c_str());
        MAGENTA
        getstr(name);
        YELLOW
        mvprintw(num, 0, "Имя:          ");
        mvprintw(num, 10, name);
        clrtoeol();
    }
    if (num == 2)
    {
        mvprintw(num, 0, qw4.c_str());
        GREEN
        mvprintw(num, 10, current_time_and_date().c_str());
        MAGENTA
        getstr(date);
        string dat(date);
        if (dat == "")
        {
            YELLOW
            mvprintw(num, 0, "Дата:           ");
            mvprintw(num, 10, current_time_and_date().c_str());
            clrtoeol();
        }
        else
        {
            YELLOW
            mvprintw(num, 0, "Дата:           ");
            mvprintw(num, 10, date);
            clrtoeol();
        }
    }
    if (num == 3)
    {
        mvprintw(num, 0, qw4.c_str());
        MAGENTA
        getstr(str);
        YELLOW
        mvprintw(num, 0, "Номер:            ");
        number = atoi(str);
        mvprintw(num, 10, str);
        clrtoeol();
    }
    //Правая рука
    if (num == 4)
    {
        auto start_line = num+1;
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        mvprintw(start_line, 30, qw3.c_str());
        mvprintw(start_line, 48, qw4.c_str());
        MAGENTA
        getstr(str);
        r_1 = atoi(str);
        YELLOW
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        RED
        clrtoeol();
        mvprintw(start_line, 30, str);
    }
    if (num == 5)
    {
        auto start_line = num+1;
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        mvprintw(start_line, 30, qw3.c_str());
        mvprintw(start_line, 48, qw4.c_str());
        MAGENTA
        getstr(str);
        r_2 = atoi(str);
        YELLOW
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        RED
        clrtoeol();
        mvprintw(start_line, 30, str);
    }
    if (num == 6)
    {
        auto start_line = num+1;
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        mvprintw(start_line, 30, qw3.c_str());
        mvprintw(start_line, 48, qw4.c_str());
        MAGENTA
        getstr(str);
        r_3 = atoi(str);
        YELLOW
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        RED
        clrtoeol();
        mvprintw(start_line, 30, str);
    }
    if (num == 7)
    {
        auto start_line = num+1;
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        mvprintw(start_line, 30, qw3.c_str());
        mvprintw(start_line, 48, qw4.c_str());
        MAGENTA
        getstr(str);
        r_4 = atoi(str);
        YELLOW
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        RED
        clrtoeol();
        mvprintw(start_line, 30, str);
    }
    if (num == 8)
    {
        auto start_line = num+1;
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        mvprintw(start_line, 30, qw3.c_str());
        mvprintw(start_line, 48, qw4.c_str());
        MAGENTA
        getstr(str);
        r_5 = atoi(str);
        YELLOW
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        RED
        clrtoeol();
        mvprintw(start_line, 30, str);
    }
    if (num == 9)
    {
        auto start_line = num+1;
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        mvprintw(start_line, 30, qw3.c_str());
        mvprintw(start_line, 48, qw4.c_str());
        MAGENTA
        getstr(str);
        r_6 = atoi(str);
        YELLOW
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        RED
        clrtoeol();
        mvprintw(start_line, 30, str);
    }
    //Левая рука
    if (num == 10)
    {
        mvprintw(11, 0, qw1.c_str());
        mvprintw(11, 4, qw2.c_str());
        mvprintw(11, 30, qw3.c_str());
        mvprintw(11, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_1 = atoi(str);
        RED
        mvprintw(num - 5, 35, str);
    }
    if (num == 11)
    {
        mvprintw(11, 0, qw1.c_str());
        mvprintw(11, 4, qw2.c_str());
        mvprintw(11, 30, qw3.c_str());
        mvprintw(11, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_2 = atoi(str);
        RED
        mvprintw(num - 5, 35, str);
    }
    if (num == 12)
    {
        mvprintw(11, 0, qw1.c_str());
        mvprintw(11, 4, qw2.c_str());
        mvprintw(11, 30, qw3.c_str());
        mvprintw(11, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_3 = atoi(str);
        RED
        mvprintw(num - 5, 35, str);
    }
    if (num == 13)
    {
        mvprintw(11, 0, qw1.c_str());
        mvprintw(11, 4, qw2.c_str());
        mvprintw(11, 30, qw3.c_str());
        mvprintw(11, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_4 = atoi(str);
        RED
        mvprintw(num - 5, 35, str);
    }
    if (num == 14)
    {
        mvprintw(11, 0, qw1.c_str());
        mvprintw(11, 4, qw2.c_str());
        mvprintw(11, 30, qw3.c_str());
        mvprintw(11, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_5 = atoi(str);
        RED
        mvprintw(num - 5, 35, str);
    }
    if (num == 15)
    {
        mvprintw(11, 0, qw1.c_str());
        mvprintw(11, 4, qw2.c_str());
        mvprintw(11, 30, qw3.c_str());
        mvprintw(11, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_6 = atoi(str);
        RED
        mvprintw(num - 5, 35, str);
    }

    mvprintw(11, 0, " ");clrtoeol();

    //Правая нога
    if (num == 16)
    {
        auto start_line = num - 4;
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        mvprintw(start_line, 30, qw3.c_str());
        mvprintw(start_line, 48, qw4.c_str());
        MAGENTA
        getstr(str);
        r_7 = atoi(str);
        YELLOW
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        RED
        clrtoeol();
        mvprintw(start_line, 30, str);
    }
    if (num == 17)
    {
        auto start_line = num - 4;
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        mvprintw(start_line, 30, qw3.c_str());
        mvprintw(start_line, 48, qw4.c_str());
        MAGENTA
        getstr(str);
        r_8 = atoi(str);
        YELLOW
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        RED
        clrtoeol();
        mvprintw(start_line, 30, str);
    }
    if (num == 18)
    {
        auto start_line = num - 4;
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        mvprintw(start_line, 30, qw3.c_str());
        mvprintw(start_line, 48, qw4.c_str());
        MAGENTA
        getstr(str);
        r_9 = atoi(str);
        YELLOW
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        RED
        clrtoeol();
        mvprintw(start_line, 30, str);
    }
    if (num == 19)
    {
        auto start_line = num - 4;
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        mvprintw(start_line, 30, qw3.c_str());
        mvprintw(start_line, 48, qw4.c_str());
        MAGENTA
        getstr(str);
        r_10 = atoi(str);
        YELLOW
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        RED
        clrtoeol();
        mvprintw(start_line, 30, str);
    }
    if (num == 20)
    {
        auto start_line = num - 4;
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        mvprintw(start_line, 30, qw3.c_str());
        mvprintw(start_line, 48, qw4.c_str());
        MAGENTA
        getstr(str);
        r_11 = atoi(str);
        YELLOW
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        RED
        clrtoeol();
        mvprintw(start_line, 30, str);
    }
    if (num == 21)
    {
        auto start_line = num - 4;
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        mvprintw(start_line, 30, qw3.c_str());
        mvprintw(start_line, 48, qw4.c_str());
        MAGENTA
        getstr(str);
        r_12 = atoi(str);
        YELLOW
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 4, qw2.c_str());
        RED
        clrtoeol();
        mvprintw(start_line, 30, str);
    }
    //Левая нога
    if (num == 22)
    {
        mvprintw(18, 0, qw1.c_str());
        mvprintw(18, 4, qw2.c_str());
        mvprintw(18, 30, qw3.c_str());
        mvprintw(18, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_7 = atoi(str);
        RED
        mvprintw(num - 10, 35, str);
    }
    if (num == 23)
    {
        mvprintw(18, 0, qw1.c_str());
        mvprintw(18, 4, qw2.c_str());
        mvprintw(18, 30, qw3.c_str());
        mvprintw(18, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_8 = atoi(str);
        RED
        mvprintw(num - 10, 35, str);
    }
    if (num == 24)
    {
        mvprintw(18, 0, qw1.c_str());
        mvprintw(18, 4, qw2.c_str());
        mvprintw(18, 30, qw3.c_str());
        mvprintw(18, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_9 = atoi(str);
        RED
        mvprintw(num - 10, 35, str);
    }
    if (num == 25)
    {
        mvprintw(18, 0, qw1.c_str());
        mvprintw(18, 4, qw2.c_str());
        mvprintw(18, 30, qw3.c_str());
        mvprintw(18, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_10 = atoi(str);
        RED
        mvprintw(num - 10, 35, str);
    }
    if (num == 26)
    {
        mvprintw(18, 0, qw1.c_str());
        mvprintw(18, 4, qw2.c_str());
        mvprintw(18, 30, qw3.c_str());
        mvprintw(18, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_11 = atoi(str);
        RED
        mvprintw(num - 10, 35, str);
    }
    if (num == 27)
    {
        mvprintw(18, 0, qw1.c_str());
        mvprintw(18, 4, qw2.c_str());
        mvprintw(18, 30, qw3.c_str());
        mvprintw(18, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_12 = atoi(str);
        RED
        mvprintw(num - 10, 35, str);
    }
    mvprintw(18, 0, " ");clrtoeol();

    refresh(); //Выводим на настоящий экран
    endwin();
}

void answers(){
    answer(1, "","","","Введите имя тестируемого  ");
    answer(2, "","","","Дата  ");
    answer(3, "","","","Введите номер тестирования  ");
    answer(4, "P ","Легкие ", "Правая рука ", "Введите измеренное значение  ");
    answer(5, "MC ","Перикард ", "Правая рука ", "Введите измеренное значение  ");
    answer(6, "С ","Сердце ", "Правая рука ", "Введите измеренное значение  ");
    answer(7, "IG ","Тонкий кишечник ", "Правая рука ", "Введите измеренное значение  ");
    answer(8, "TR ","Гормональная система ", "Правая рука ", "Введите измеренное значение  ");
    answer(9, "GI ","Толстый кишечник ", "Правая рука ", "Введите измеренное значение  ");

    answer(10, "P ","Легкие ", "Левая рука ", "Введите измеренное значение  ");
    answer(11, "MC ","Перикард ", "Левая рука ", "Введите измеренное значение  ");
    answer(12, "С ","Сердце ", "Левая рука ", "Введите измеренное значение  ");
    answer(13, "IG ","Тонкий кишечник ", "Левая рука ", "Введите измеренное значение  ");
    answer(14, "TR ","Гормональная система ", "Левая рука ", "Введите измеренное значение  ");
    answer(15, "GI ","Толстый кишечник ", "Левая рука ", "Введите измеренное значение  ");

    answer(16, "RP ","Селез., Поджел. ", "Правая нога ", "Введите измеренное значение  ");
    answer(17, "F ","Печень ", "Правая нога ", "Введите измеренное значение  ");
    answer(18, "R ","Почки ", "Правая нога ", "Введите измеренное значение  ");
    answer(19, "V ","Мочевой пузырь ", "Правая нога ", "Введите измеренное значение  ");
    answer(20, "VB ","Желчный пузырь ", "Правая нога ", "Введите измеренное значение  ");
    answer(21, "E ","Желудок ", "Правая нога ", "Введите измеренное значение  ");

    answer(22, "RP ","Селез., Поджел. ", "Левая нога ", "Введите измеренное значение  ");
    answer(23, "F ","Печень ", "Правая нога ", "Введите измеренное значение  ");
    answer(24, "R ","Почки ", "Правая нога ", "Введите измеренное значение  ");
    answer(25, "V ","Мочевой пузырь ", "Левая нога ", "Введите измеренное значение  ");
    answer(26, "VB ","Желчный пузырь ", "Левая нога ", "Введите измеренное значение  ");
    answer(27, "E ","Желудок ", "Левая нога ", "Введите измеренное значение  ");

    WHITE
    mvprintw(18, 0, "");
    summ = l_1+l_2+l_3+l_4+l_5+l_6+l_7+l_8+l_9+l_10+l_11+l_12+
            r_1+r_2+r_3+r_4+r_5+r_6+r_7+r_8+r_9+r_10+r_11+r_12;
    average = floorf((float)summ/24 * 10) / 10;
    hight = average + 7.f;
    low = average - 7.f;
    mvprintw(19, 0, "Коридор нормы верх");
    mvprintw(19, 30, "%4.0f", average + 7);
    mvprintw(20, 0, "Коридор нормы низ");
    mvprintw(20, 30, "%4.0f", average - 7);

}

string letter(int r, int l , float k)
{
    if( r == l)
    {
        GREEN
        if (abs(k * r  - hight) < 0.6) return "B+1";
        if (((hight - k * r) > 0.6) && (k * r > low)) return "B0";
        if (abs(k * r - low) < 0.6) return "B-1";
        if ((k * r - hight ) >= 0.6) return "B+2";
        if ((low - k * r ) >= 0.6) return "B-2";
        return "Err";
    }
    if( r < l)
    {
        BLUE
        if ((k * r - hight ) >= 0.6) return "A+2";
        if ((k * r < hight ) && (k * r > low ) && (k * l > hight )) return "A+1";
        if ((k * r > low ) && (k * l < hight )) return "A0";
        if ((k * l > low ) && (k * l < hight )) return "A-1";
        if ((low - k * l ) >= 0.6) return "A-2";
        if ((k * r < low) && (k * l > hight)) return "OK";
        return "Err";
    }
    if( r > l)
    {
        RED
        if ((k * l - hight ) >= 0.6) return "C+2";
        if ((k * l < hight ) && (k * l > low ) && (k * r > hight )) return "C+1";
        if ((k * l > low ) && (k * r < hight )) return "A0";
        if ((k * r > low ) && (k * r < hight )) return "C-1";
        if ((low - k * r ) >= 0.6) return "C-2";
        if ((k * l < low) && (k * r > hight)) return "OП";
        return "Err";
    }
    return "---";
}
