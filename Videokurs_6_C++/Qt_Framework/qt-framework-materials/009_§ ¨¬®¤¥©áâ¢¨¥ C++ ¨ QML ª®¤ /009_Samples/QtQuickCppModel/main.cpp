#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "AnimalModel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    AnimalModel modelModel;
    modelModel.addAnimal(Animal("Wolf", "Medium"));
    modelModel.addAnimal(Animal("Polar bear", "Large"));
    modelModel.addAnimal(Animal("Quoll", "Small"));

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("animalModel", &modelModel);
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
