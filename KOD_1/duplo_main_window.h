#ifndef DUPLO_MAIN_WINDOW_H
#define DUPLO_MAIN_WINDOW_H

// Qt
#include <QMainWindow>

//library
#include "duplo_dispatcher.h"

// widgets
#include "violation_order_widget.h"

using Dispatcher = sadko::DuploDispatcher;

class DuploMainWindow : public QMainWindow
{
public:
    explicit DuploMainWindow(QWidget *parent = nullptr);

   void SetConnectParam(const QString &host);
   void Init();

private:
   Dispatcher _dispatcher;


//Обьявляем структуру _widgets типа Widgets
   struct Widgets
   {
      ViolationOrderWidget *violation_order = nullptr;
   } _widgets;
};

#endif // DUPLO_MAIN_WINDOW_H
