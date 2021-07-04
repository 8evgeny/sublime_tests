/*Liskov's notion of a behavioural subtype defines a notion of substitutability for objects; that is, if S
is a subtype of T, then objects of type T in a program may be replaced with objects of type S without altering
any of the desirable properties of that program*/


#include <QCoreApplication>


int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);



    a.exit(0);
//    return a.exec();
}
