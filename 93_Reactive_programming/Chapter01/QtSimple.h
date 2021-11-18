#include <qapplication.h>
#include <qdialog.h>
#include <qmessagebox.h>
#include <qobject.h>
#include <qpushbutton.h>


class MyApp : public QDialog
{
    Q_OBJECT
     public:
    MyApp(QObject* /*parent*/ = 0);

//        public slots:
    Q_SLOT void button_clicked();
    protected:
        QPushButton button;
};

