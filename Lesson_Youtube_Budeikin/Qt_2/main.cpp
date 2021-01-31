#include <QtWidgets>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QLabel lbl("Привет<br> <b style=color:red>мир!!! </b>");
    lbl.show();
    return a.exec();
}
