#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <curses.h>
#include <ncursesw/ncurses.h>
using namespace std;
char name[100];
char date[100];
int number,r_1,r_2,r_3,r_4,r_5,r_6,l_1,l_2,l_3,l_4,l_5,l_6;

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
    if (!answer(4, "P ","Легкие ", "Правая сторона ", "Введите измеренное значение  "))
        return false;
    if (!answer(5, "MC ","Перикард ", "Правая сторона ", "Введите измеренное значение  "))
        return false;
    if (!answer(6, "С ","Сердце ", "Правая сторона ", "Введите измеренное значение  "))
        return false;
    if (!answer(7, "IG ","Тонкий кишечник ", "Правая сторона ", "Введите измеренное значение  "))
        return false;
    if (!answer(8, "TR ","Гормональная система ", "Правая сторона ", "Введите измеренное значение  "))
        return false;
    if (!answer(9, "GI ","Толстый кишечник ", "Правая сторона ", "Введите измеренное значение  "))
        return false;

    if (!answer(10, "P ","Легкие ", "Левая сторона ", "Введите измеренное значение  "))
        return false;
    if (!answer(11, "MC ","Перикард ", "Левая сторона ", "Введите измеренное значение  "))
        return false;
    if (!answer(12, "С ","Сердце ", "Левая сторона ", "Введите измеренное значение  "))
        return false;
    if (!answer(13, "IG ","Тонкий кишечник ", "Левая сторона ", "Введите измеренное значение  "))
        return false;
    if (!answer(14, "TR ","Гормональная система ", "Левая сторона ", "Введите измеренное значение  "))
        return false;
    if (!answer(15, "GI ","Толстый кишечник ", "Левая сторона ", "Введите измеренное значение  "))
        return false;
    mvprintw(11, 0, "");

  char tmp[10] ;
  getstr(tmp);



     return true;
}

bool answer(uint num, string qw1, string qw2, string qw3, string qw4)
{
    WHITE

    noecho();
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
        echo();
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
        echo();
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
        echo();
        mvprintw(num, 0, qw4.c_str());
        MAGENTA
        getstr(str);
        YELLOW
        mvprintw(num, 0, "Номер:            ");
        number = atoi(str);
        mvprintw(num, 10, str);
        clrtoeol();
    }
    if (num == 4)
    {
        auto start_line = num+1;
        echo();
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
        echo();
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
        echo();
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
        echo();
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
        echo();
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
        echo();
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
    if (num == 10)
    {
        echo();
        mvprintw(11, 0, qw1.c_str());
        mvprintw(11, 4, qw2.c_str());
        mvprintw(11, 30, qw3.c_str());
        mvprintw(11, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_1 = atoi(str);
        RED
        mvprintw(5, 35, str);
    }
    if (num == 11)
    {
        echo();
        mvprintw(11, 0, qw1.c_str());
        mvprintw(11, 4, qw2.c_str());
        mvprintw(11, 30, qw3.c_str());
        mvprintw(11, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_2 = atoi(str);
        RED
        mvprintw(6, 35, str);
    }
    if (num == 12)
    {
        echo();
        mvprintw(11, 0, qw1.c_str());
        mvprintw(11, 4, qw2.c_str());
        mvprintw(11, 30, qw3.c_str());
        mvprintw(11, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_3 = atoi(str);
        RED
        mvprintw(7, 35, str);
    }
    if (num == 13)
    {
        echo();
        mvprintw(11, 0, qw1.c_str());
        mvprintw(11, 4, qw2.c_str());
        mvprintw(11, 30, qw3.c_str());
        mvprintw(11, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_4 = atoi(str);
        RED
        mvprintw(8, 35, str);
    }
    if (num == 14)
    {
        echo();
        mvprintw(11, 0, qw1.c_str());
        mvprintw(11, 4, qw2.c_str());
        mvprintw(11, 30, qw3.c_str());
        mvprintw(11, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_5 = atoi(str);
        RED
        mvprintw(9, 35, str);
    }
    if (num == 15)
    {
        echo();
        mvprintw(11, 0, qw1.c_str());
        mvprintw(11, 4, qw2.c_str());
        mvprintw(11, 30, qw3.c_str());
        mvprintw(11, 48, qw4.c_str());
        MAGENTA
        clrtoeol();
        getstr(str);
        l_6 = atoi(str);
        RED
        mvprintw(10, 35, str);
    }





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
    cout<< "Ответы на вопросы ... OK" <<endl;

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
