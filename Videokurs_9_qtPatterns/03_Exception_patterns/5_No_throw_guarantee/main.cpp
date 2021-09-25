#include <QCoreApplication>

/*
 What:
 Exception safety
 https://en.wikipedia.org/wiki/Exception_safety

 Decription:
  No exception safety
  Basic exception safety
  Strong exception safety
  No-throw guarantee

 Why:
 Bad things happen!!

 Example:
 No-throw guarantee
 The no-fail (or, "no-throw") guarantee is the strongest guarantee that a function can provide.
 It states that the function will not throw an exception or allow one to propagate.
 However, you cannot reliably provide such a guarantee unless
(a) you know that all the functions that this function calls are also no-fail, or
(b) you know that any exceptions that are thrown are caught before they reach this function, or
(c) you know how to catch and correctly handle all exceptions that might reach this function.

I'd like to point out, this is almost impossible, even this example could still have lots of hidden issues!
What if the memory is going bad
What if we are out of memory
What if the user enters a unicode string of 100000000000000 chars
 */


#include <QTextStream>
#include <QList>
#include <QString>
#include <QDebug>


//Live in the real world...
bool userIO(QTextStream &stream, QList<QString> &list)
{
    qInfo() << "Enter a number and a name (1 Bryan)";

    QString value = stream.readLine(255);
    if(value.isEmpty()) return false;

    int id = 0;
    QString name = "";


    QStringList items = value.split(" ");
    if(items.length() < 2) return false;

    bool ok = false;
    id = items.at(0).toInt(&ok);
    if(!ok) return false;

    name = items.at(1);

    if(id < list.length())
    {
        list.insert(id,name);
    }
    else
    {
        list.append(name);
        id = list.length();
    }

    qInfo() << id << " = " << name;

    return true;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<QString> list;
    QTextStream stream(stdin); //Memory leak and potential crash

   while(userIO(stream,list))
   {
       qInfo() << "Do it again...";
   }
   qInfo() << "Complete";

    return a.exec();
}
