#include <QCoreApplication>

/*

  What
  Decorator pattern

  Description
  Dynamically add functionality at run time

  Why
  Flexible alternative to subclassing

  Example
  HTML tags
  https://sourcemaking.com/design_patterns/decorator


 */

#include <QString>
#include <QDebug>
#include "text.h"
#include "boldtext.h"
#include "italictext.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString value = "text";
    Text t(new BoldText(new ItalicText(&a)));
    t.process(value);

    qInfo() << value;


    return a.exec();
}
