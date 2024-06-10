#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <curses.h>
#include <ncursesw/ncurses.h>
using namespace std;
char name[100];
char date[100];
int number,r_1,r_2,r_3,r_4,r_5,r_6,l_1,l_2,l_3,l_4,l_5,l_6;
bool answer(uint num, string qw1, string qw2, string qw3, string qw4);
//void colorMsg(uint num, vector<string> & qw);


bool answers(){
    if (!answer(1, "","","","Введите имя тестируемого  "))
        return false;
    if (!answer(2, "","","","Введите дату тестирования  "))
        return false;
    if (!answer(3, "","","","Введите номер тестирования  "))
        return false;
    if (!answer(4, "P ","Канал легких, ", "Правая сторона. ", "Введите измеренное значение  "))
        return false;

     return true;
}

bool answer(uint num, string qw1, string qw2, string qw3, string qw4)
{
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(3));

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
        getstr(name);
        mvprintw(num, 0, "                                               ");
        mvprintw(num, 0, name);
    }
    if (num == 2)
    {
        echo();
        mvprintw(num, 0, qw4.c_str());
        getstr(date);
        mvprintw(num, 0, "                                               ");
        mvprintw(num, 0, date);
    }
    if (num == 3)
    {
        echo();
        mvprintw(num, 0, qw4.c_str());
        getstr(str);
        mvprintw(num, 0, "                                               ");
        number = atoi(str);
        mvprintw(num, 0, str);
    }
    if (num == 4)
    {
        auto start_line = num+1;
        echo();
        mvprintw(start_line, 0, qw1.c_str());
        mvprintw(start_line, 5, qw2.c_str());
        mvprintw(start_line, 22, qw3.c_str());
        mvprintw(start_line, 42, qw4.c_str());
        getstr(str);
        r_1 = atoi(str);
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
