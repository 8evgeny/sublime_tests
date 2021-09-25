#ifndef ITALICTEXT_H
#define ITALICTEXT_H

#include <QObject>
#include "text.h"

class ItalicText : public Text
{
    Q_OBJECT
public:
    explicit ItalicText(QObject *parent = nullptr);
    void process(QString &input) override;
signals:



};

#endif // ITALICTEXT_H
