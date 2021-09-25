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
 No exception safety
 Enter an invalid number and see...
 Where to begin...

 */

#include <QTextStream>
#include <QList>
#include <QString>
#include <QDebug>

//perfect code that never fails...
int getInt(QString data)
{
    bool ok;
    int value = data.toInt(&ok);
    if(!ok) return 0;
    return value;
}

//Live in the real world...
void userIO(QTextStream *stream, QList<QString> *list)
{
    qInfo() << "Enter a number and a name (1 Bryan)";
    QString value = stream->readLine(); //assume it exists!
    QStringList items = value.split(" "); //assuming this is included

    int id = items.at(0).toInt(); //what if its not an int
    QString name = items.at(1); //assuming  this exists

    list->insert(id,name); //Assuming we made it this far
    qInfo() << "You entered:" << list->at(id); // ASSERT failure in QList<T>::at: "index out of range"
    userIO(stream,list); //recursive function. will kick out a warning
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<QString> list;
    QTextStream *stream = new QTextStream(stdin); //Memory leak and potential crash

    userIO(stream,&list);//recursive function. will kick out a warning

    return a.exec();
}
