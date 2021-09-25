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
 Strong exception safety
The strong guarantee states that if a function goes out of scope because of an exception,
it will not leak memory and program state will not be modified.
A function that provides a strong guarantee is essentially a transaction
that has commit or rollback semantics: either it completely succeeds or it has no effect.

 */

#include <QTextStream>
#include <QList>
#include <QString>
#include <QDebug>


//Live in the real world...
void userIO(QTextStream *stream, QList<QString> *list)
{

    try {
        if(!stream)
        {
            qWarning() << "stream not set";
            userIO(stream,list);
            return;
        }

        if(!list)
        {
            qWarning() << "list not set";
            userIO(stream,list);
            return;
        }


        qInfo() << "Enter a number and a name (1 Bryan)";
        QString value = stream->readLine(255); //forever or 255 chars
        if(value.isEmpty())
        {
            qWarning() << "No line read!";
            userIO(stream,list);
            return;
        }

        QStringList items = value.split(" "); //assuming this is included

        if(items.length() < 2)
        {
            qWarning() << "Not enough items!";
            userIO(stream,list);
            return;
        }

        bool ok;
        int id = items.at(0).toInt(&ok); //what if its not an int
        if(!ok)
        {
            qWarning() << "Not a number";
            userIO(stream,list);
            return;
        }

        if(id <= list->length())
        {
            QString name = items.at(1); //assuming  this exists

            list->insert(id,name); //Assuming we made it this far

            qInfo() << "You entered:" << list->at(id);
        }


        userIO(stream,list); //we live here forever - or until the user breaks it
    }
    catch (const std::out_of_range& ex)
    {
        qInfo() << "Out of range" << ex.what();
        userIO(stream,list);
    }
    catch (const std::exception& ex)
    {
        qInfo() << "Error:" << ex.what();
        userIO(stream,list);
    }
    catch (...) {
        qInfo() << "Unknown error";
        userIO(stream,list);
    }

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<QString> list;
    QTextStream stream(stdin); //Memory leak and potential crash

    userIO(&stream,&list);//recursive function. will kick out a warning

    return a.exec();
}
