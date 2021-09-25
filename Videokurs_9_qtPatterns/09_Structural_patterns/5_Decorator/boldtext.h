#ifndef BOLDTEXT_H
#define BOLDTEXT_H

#include <QObject>
#include "text.h"

class BoldText : public Text
{
    Q_OBJECT
public:
    explicit BoldText(QObject *parent = nullptr);
    void process(QString &input) override;
signals:




};

#endif // BOLDTEXT_H
