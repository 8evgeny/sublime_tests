#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <curses.h>
#include <ncursesw/ncurses.h>
#include <math.h>

using namespace std;
char name[100];
char date[100];
int number{0}, summ{0};
int r_1{0}, r_2{0}, r_3{0}, r_4{0}, r_5{0}, r_6{0}, l_1{0}, l_2{0}, l_3{0}, l_4{0}, l_5{0}, l_6{0};
int r_7{0}, r_8{0}, r_9{0}, r_10{0}, r_11{0}, r_12{0}, l_7{0}, l_8{0}, l_9{0}, l_10{0}, l_11{0},l_12{0};
float average{0.0};
#define YELLOW attron(COLOR_PAIR(1));
#define GREEN attron(COLOR_PAIR(2));
#define WHITE attron(COLOR_PAIR(3));
#define RED attron(COLOR_PAIR(4));
#define BLUE attron(COLOR_PAIR(5));
#define MAGENTA attron(COLOR_PAIR(6));
#define CYAN attron(COLOR_PAIR(7));

bool answer(uint num, string qw1, string qw2, string qw3, string qw4);
//void colorMsg(uint num, vector<string> & qw);


bool answers(){
    if (!answer(1, "","","","Введите имя тестируемого  "))
        return false;
    if (!answer(2, "","","","Введите дату тестирования  "))
        return false;
    if (!answer(3, "","","","Введите номер тестирования  "))
        return false;
    if (!answer(4, "P ","Легкие ", "Правая рука ", "Введите измеренное значение  "))
        return false;
    if (!answer(5, "MC ","Перикард ", "Правая рука ", "Введите измеренное значение  "))
        return false;
    if (!answer(6, "С ","Сердце ", "Правая рука ", "Введите измеренное значение  "))
        return false;
    if (!answer(7, "IG ","Тонкий кишечник ", "Правая рука ", "Введите измеренное значение  "))
        return false;
    if (!answer(8, "TR ","Гормональная система ", "Правая рука ", "Введите измеренное значение  "))
        return false;
    if (!answer(9, "GI ","Толстый кишечник ", "Правая рука ", "Введите измеренное значение  "))
        return false;

    if (!answer(10, "P ","Легкие ", "Левая рука ", "Введите измеренное значение  "))
        return false;
    if (!answer(11, "MC ","Перикард ", "Левая рука ", "Введите измеренное значение  "))
        return false;
    if (!answer(12, "С ","Сердце ", "Левая рука ", "Введите измеренное значение  "))
        return false;
    if (!answer(13, "IG ","Тонкий кишечник ", "Левая рука ", "Введите измеренное значение  "))
        return false;
    if (!answer(14, "TR ","Гормональная система ", "Левая рука ", "Введите измеренное значение  "))
        return false;
    if (!answer(15, "GI ","Толстый кишечник ", "Левая рука ", "Введите измеренное значение  "))
        return false;

    if (!answer(16, "P ","Легкие ", "Правая нога ", "Введите измеренное значение  "))
        return false;
    if (!answer(17, "MC ","Перикард ", "Правая нога ", "Введите измеренное значение  "))
        return false;
    if (!answer(18, "С ","Сердце ", "Правая нога ", "Введите измеренное значение  "))
        return false;
    if (!answer(19, "IG ","Тонкий кишечник ", "Правая нога ", "Введите измеренное значение  "))
        return false;
    if (!answer(20, "TR ","Гормональная система ", "Правая нога ", "Введите измеренное значение  "))
        return false;
    if (!answer(21, "GI ","Толстый кишечник ", "Правая нога ", "Введите измеренное значение  "))
        return false;

    if (!answer(22, "P ","Легкие ", "Левая нога ", "Введите измеренное значение  "))
        return false;
    if (!answer(23, "MC ","Перикард ", "Левая нога ", "Введите измеренное значение  "))
        return false;
    if (!answer(24, "С ","Сердце ", "Левая нога ", "Введите измеренное значение  "))
        return false;
    if (!answer(25, "IG ","Тонкий кишечник ", "Левая нога ", "Введите измеренное значение  "))
        return false;
    if (!answer(26, "TR ","Гормональная система ", "Левая нога ", "Введите измеренное значение  "))
        return false;
    if (!answer(27, "GI ","Толстый кишечник ", "Левая нога ", "Введите измеренное значение  "))
        return false;

    WHITE
    mvprintw(18, 0, "");
    summ = l_1+l_2+l_3+l_4+l_5+l_6+l_7+l_8+l_9+l_10+l_11+l_12+
            r_1+r_2+r_3+r_4+r_5+r_6+r_7+r_8+r_9+r_10+r_11+r_12;
    average = floorf((float)summ/24 * 10) / 10;

    mvprintw(19, 0, "Коридор нормы верх");
    mvprintw(19, 30, "%4.1f", average + 7);
    mvprintw(20, 0, "Коридор нормы низ");
    mvprintw(20, 30, "%4.1f", average - 7);
  char tmp[10] ;
  getstr(tmp);


     return true;
}

bool answer(uint num, string qw1, string qw2, string qw3, string qw4)
{
    WHITE
    echo();

    halfdelay(100);         //Устанавливаем ограничение по времени ожидания getch() в 10 сек
    bool ret = true;
    bool ex = false;
    uint numCharEntered = 0;
    wint_t tmp;
    wint_t c1;
    wint_t c2;
    wint_t c3;

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
        MAGENTA
        getstr(date);
        YELLOW
        mvprintw(num, 0, "Дата:           ");
        mvprintw(num, 10, date);
        clrtoeol();
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

 return ret;
}

//void colorMsg(uint num, vector<string> & qw)
//{
//    mvprintw(num*2-2, 0, qw[0].c_str());
//    attron(COLOR_PAIR(1));
//    printw(qw[1].c_str());
//    attron(COLOR_PAIR(3));
//    printw(qw[2].c_str());
//    attron(COLOR_PAIR(2));
//    printw(qw[3].c_str());
//    attron(COLOR_PAIR(3));
//    printw(qw[4].c_str());
//}


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
    bkgdset(COLOR_PAIR(2));
    if (!answers()){
        cout << "\nИсправьте ИУЛ !!!\n" <<endl;
        return 0;
    }
    cout<<"Имя: "<<name<<endl;
    cout<<"Дата: "<<date<<endl;
    cout<<"Номер: "<<number<<endl;
    cout<< "Среднее" <<average<<endl;

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
