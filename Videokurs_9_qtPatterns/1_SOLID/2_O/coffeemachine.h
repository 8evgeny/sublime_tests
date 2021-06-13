#ifndef COFFEEMACHINE_H
#define COFFEEMACHINE_H

#include "interfaces/iBrew.h"
#include <QDebug>
#include <QObject>
#include <QStringList>

class CoffeeMachine : public QObject, public iBrew {
    Q_OBJECT
public:
    explicit CoffeeMachine(QObject* parent = nullptr);

signals:

    // iBrew interface
public:
    void addIngredients(QStringList& list) override;
    void brew() override;
};

#endif // COFFEEMACHINE_H
