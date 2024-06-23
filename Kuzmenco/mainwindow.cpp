#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPainter>

using namespace std;
extern QApplication * app;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}

void MainWindow::setUi(Ui::MainWindow *newUi)
{
    ui = newUi;
}

void MainWindow::on_name_field_editingFinished()
{
    name_field = ui->name_field->text();
    cout<< "name_field: " << name_field.toStdString() << endl;
    repaint();
    update();
}

void MainWindow::on_dateEdit_dateChanged(const QDate &date)
{
    Date = ui->dateEdit->text();
    cout<< "Date: " << Date.toStdString() << endl;
}

void MainWindow::on_r_1_editingFinished()
{
    r1 = ui->r_1->text().toInt();
    cout<< "r1: " << r1 << endl;
}
void MainWindow::on_r_2_editingFinished()
{
    r2 = ui->r_2->text().toInt();
    cout<< "r2: " << r2 << endl;
}
void MainWindow::on_r_3_editingFinished()
{
    r3 = ui->r_3->text().toInt();
    cout<< "r3: " << r3 << endl;
}
void MainWindow::on_r_4_editingFinished()
{
    r4 = ui->r_4->text().toInt();
    cout<< "r4: " << r4 << endl;
}
void MainWindow::on_r_5_editingFinished()
{
    r5 = ui->r_5->text().toInt();
    cout<< "r5: " << r5 << endl;
}
void MainWindow::on_r_6_editingFinished()
{
    r6 = ui->r_6->text().toInt();
    cout<< "r6: " << r6 << endl;
}
void MainWindow::on_r_7_editingFinished()
{
    r7 = ui->r_7->text().toInt();
    cout<< "r7: " << r7 << endl;
}
void MainWindow::on_r_8_editingFinished()
{
    r8 = ui->r_8->text().toInt();
    cout<< "r8: " << r8 << endl;
}
void MainWindow::on_r_9_editingFinished()
{
    r9 = ui->r_9->text().toInt();
    cout<< "r9: " << r9 << endl;
}
void MainWindow::on_r_10_editingFinished()
{
    r10 = ui->r_10->text().toInt();
    cout<< "r10: " << r10 << endl;
}
void MainWindow::on_r_11_editingFinished()
{
    r11 = ui->r_11->text().toInt();
    cout<< "r11: " << r11 << endl;
}
void MainWindow::on_r_12_editingFinished()
{
    r12 = ui->r_12->text().toInt();
    cout<< "r12: " << r12 << endl;
}

void MainWindow::on_l_1_editingFinished()
{
    l1 = ui->l_1->text().toInt();
    cout<< "l1: " << l1 << endl;
}
void MainWindow::on_l_2_editingFinished()
{
    l2 = ui->l_2->text().toInt();
    cout<< "l2: " << l2 << endl;
}
void MainWindow::on_l_3_editingFinished()
{
    l3 = ui->l_3->text().toInt();
    cout<< "l3: " << l3 << endl;
}
void MainWindow::on_l_4_editingFinished()
{
    l4 = ui->l_4->text().toInt();
    cout<< "l4: " << l4 << endl;
}
void MainWindow::on_l_5_editingFinished()
{
    l5 = ui->l_5->text().toInt();
    cout<< "l5: " << l5 << endl;
}
void MainWindow::on_l_6_editingFinished()
{
    l6 = ui->l_6->text().toInt();
    cout<< "l6: " << l6 << endl;
}
void MainWindow::on_l_7_editingFinished()
{
    l7 = ui->l_7->text().toInt();
    cout<< "l7: " << l7 << endl;
}
void MainWindow::on_l_8_editingFinished()
{
    l8 = ui->l_8->text().toInt();
    cout<< "l8: " << l8 << endl;
}
void MainWindow::on_l_9_editingFinished()
{
    l9 = ui->l_9->text().toInt();
    cout<< "l9: " << l9 << endl;
}
void MainWindow::on_l_10_editingFinished()
{
    l10 = ui->l_10->text().toInt();
    cout<< "l10: " << l10 << endl;
}
void MainWindow::on_l_11_editingFinished()
{
    l11 = ui->l_11->text().toInt();
    cout<< "l11: " << l11 << endl;
}
void MainWindow::on_l_12_editingFinished()
{
    l12 = ui->l_12->text().toInt();
    cout<< "l12: " << l12 << endl;
}

void MainWindow::on_button_exit_clicked()
{
    app->exit();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(ui->widget); // Создаём объект отрисовщика
painter.begin(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.drawEllipse(100, 50, 150, 150);

}
#if 0
            #include <QMainWindow>
            #include <QScrollArea>
            #include <QLabel>
            #include <QApplication>
            #include <QPainter>

            class MyLabel : public QLabel {
            protected:
                virtual void paintEvent(QPaintEvent* e) {
                    QLabel::paintEvent(e);

                    QPainter p(this);

                    p.setPen(Qt::green);
                    p.drawLine(0, 0, 100, 100);
                }
            };

            class ImageView : public QMainWindow {
            public:

                ImageView() : QMainWindow() {
                    QScrollArea* scr = new QScrollArea();
                    setCentralWidget( scr );

                    QLabel* label = new MyLabel();
                    label->setPixmap(QPixmap("./moon_from_andrey.jpg"));
                    scr->setWidget(label);
                }
            };


            int main(int argc, char* argv[]) {
                QApplication app(argc, argv);

                ImageView view;
                view.setGeometry(100, 100, 500, 400);
                view.show();

                return app.exec();
            }
#endif
