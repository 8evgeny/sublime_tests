#include "Counter.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<Counter>("com.ruslan.counter", 1, 0, "Counter");
    QQmlApplicationEngine engine;
    Counter c;
    engine.rootContext()->setContextProperty("counterObject", &c);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    auto qmlObject = engine.rootObjects().at(0)->findChild<QObject*>("setValueButton");
    if (qmlObject) {
        qDebug() << qmlObject->property("text");
    }

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
