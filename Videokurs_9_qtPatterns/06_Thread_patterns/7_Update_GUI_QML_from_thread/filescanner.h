#ifndef FILESCANNER_H
#define FILESCANNER_H

#include <QObject>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QThread>
#include <QThreadPool>
#include <QTimer>
#include "scanner.h"

class FileScanner : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString path READ path)
public:
    explicit FileScanner(QObject *parent = nullptr);


    QString path();

signals:
    void scanStarted();
    void scanUpdated(int value);
    void scanFinished(int value);

public slots:
    void scan(QString path);

private slots:
    void started();
    void updated(int value);
    void finished(int value);
    void timeout();


private:
    QTimer m_timer;
    int m_count;

};

#endif // FILESCANNER_H
