#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter : public QObject {
    Q_OBJECT
    Q_PROPERTY(int value READ getValue WRITE setValue NOTIFY valueChanged)
public:
    explicit Counter(QObject* parent = nullptr);

    int getValue() const;

signals:
    void valueChanged(int value);

public slots:
    void setValue(int value);

protected:
    void timerEvent(QTimerEvent* event) override;

private:
    int mValue;
};

#endif // COUNTER_H
