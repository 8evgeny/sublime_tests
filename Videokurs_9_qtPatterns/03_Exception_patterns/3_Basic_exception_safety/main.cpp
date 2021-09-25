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
 Basic exception safety
The basic guarantee is the weakest of the three.
However, it might be the best choice when a strong guarantee is too expensive in memory consumption or in performance.
The basic guarantee states that if an exception occurs, no memory is leaked and the object is still in a usable state even though the data might have been modified.

 */

#include <QTextStream>
#include <QList>
#include <QString>
#include <QDebug>


//Live in the real world...
void userIO(QTextStream *stream, QList<QString> *list)
{
    if(!stream)
    {
        qWarning() << "stream not set";
        return;
    }

    if(!list)
    {
        qWarning() << "list not set";
        return;
    }


    qInfo() << "Enter a number and a name (1 Bryan)";
    QString value = stream->readLine(255); //forever or 255 chars
    if(value.isEmpty())
    {
        qWarning() << "No line read!";
        return;
    }

    QStringList items = value.split(" "); //assuming this is included

    if(items.length() < 2)
    {
        qWarning() << "Not enough items!";
        return;
    }

    bool ok;
    int id = items.at(0).toInt(&ok); //what if its not an int
    if(!ok)
    {
        qWarning() << "Not a number";
        return;
    }

    QString name = items.at(1); //assuming  this exists

    list->insert(id,name); //Assuming we made it this far
    qInfo() << "You entered:" << list->last();

    userIO(stream,list); //we live here forever - or until the user breaks it
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<QString> list;
    QTextStream *stream = new QTextStream(stdin); //Memory leak and potential crash

    userIO(stream,&list);//recursive function. will kick out a warning

    return a.exec();
}
