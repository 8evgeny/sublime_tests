#ifndef CAFFINATOR3000_H
#define CAFFINATOR3000_H

#include "interfaces/iBrew.h"
#include <QDebug>
#include <QObject>
#include <QStringList>

class caffinator3000 : public QObject, public iBrew {
    Q_OBJECT
public:
    explicit caffinator3000(QObject* parent = nullptr);

signals:

    // iBrew interface
public:
    void addIngredients(QStringList& list) override;
    void brew() override;
    void marketing();
};

#endif // CAFFINATOR3000_H
