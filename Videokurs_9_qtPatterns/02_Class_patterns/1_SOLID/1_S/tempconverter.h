#ifndef TEMPCONVERTER_H
#define TEMPCONVERTER_H

#include <QObject>

class TempConverter : public QObject {
    Q_OBJECT
public:
    explicit TempConverter(QObject* parent = nullptr);

    int celciusToFarengeit(int val);
    int farengeiyToCelcius(int val);

signals:
};

#endif // TEMPCONVERTER_H
