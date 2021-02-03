#include <QtWidgets>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QPushButton *button = new QPushButton("Завершить работу программы");
    button->show();
    QObject::connect(button, SIGNAL(clicked(bool)), &a, SLOT(quit()));
    return a.exec();
}
