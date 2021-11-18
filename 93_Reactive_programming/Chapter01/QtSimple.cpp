#include "QtSimple.h"

MyApp::MyApp(QObject* )
    : button(this)
{
    button.setText("Hello world!");
    button.resize(100, 30);

    // When the button is clicked, run button_clicked
    connect(&button,&QPushButton::clicked, this, &MyApp::button_clicked);
}
void MyApp::button_clicked()
{
    QMessageBox box;
    box.setWindowTitle("Howdy");
    box.setText("You clicked the button");
    box.show();
    box.exec();
}



int main(int argc, char** argv) {
	QApplication app(argc, argv);
	MyApp myapp;
	myapp.show();
	return app.exec();
}


