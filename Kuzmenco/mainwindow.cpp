#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPainter>
#include <QGraphicsScene>

using namespace std;
extern QApplication * app;
extern QPen penRed;
extern QPen penGreen;
extern QPen penBlue;
extern QPen penTransparent;
extern QGraphicsScene * scene;

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

void MainWindow::on_dateEdit_dateChanged(const QDate &date)
{
    Date = ui->dateEdit->text();
    cout<< "Date: " << Date.toStdString() << endl;
}

void MainWindow::drawPoints()
{
    scene->clear();
    if (r1>0)
    {
//        scene->addEllipse(123,r1,4,4,penRed);
        switch (r1)
        {
            case 5: scene->addEllipse(123,720,4,4,penRed);break;
            case 10: scene->addEllipse(123,690,4,4,penRed);break;
            case 15: scene->addEllipse(123,670,4,4,penRed);break;
            case 20: scene->addEllipse(123,645,4,4,penRed);break;
            case 25: scene->addEllipse(123,625,4,4,penRed);break;
            case 30: scene->addEllipse(123,605,4,4,penRed);break;
            case 35: scene->addEllipse(123,585,4,4,penRed);break;
            case 40: scene->addEllipse(123,565,4,4,penRed);break;
            case 45: scene->addEllipse(123,548,4,4,penRed);break;
            case 50: scene->addEllipse(123,530,4,4,penRed);break;
            case 55: scene->addEllipse(123,513,4,4,penRed);break;
            case 60: scene->addEllipse(123,493,4,4,penRed);break;
            case 65: scene->addEllipse(123,479,4,4,penRed);break;
            case 70: scene->addEllipse(123,462,4,4,penRed);break;
            case 75: scene->addEllipse(123,444,4,4,penRed);break;
            case 80: scene->addEllipse(123,427,4,4,penRed);break;
            case 85: scene->addEllipse(123,416,4,4,penRed);break;
            case 90: scene->addEllipse(123,401,4,4,penRed);break;
            case 95: scene->addEllipse(123,387,4,4,penRed);break;
            case 100: scene->addEllipse(123,373,4,4,penRed);break;
            case 105: scene->addEllipse(123,361,4,4,penRed);break;
            case 110: scene->addEllipse(123,347,4,4,penRed);break;
            case 115: scene->addEllipse(123,335,4,4,penRed);break;
            case 120: scene->addEllipse(123,321,4,4,penRed);break;
            case 125: scene->addEllipse(123,312,4,4,penRed);break;
            case 130: scene->addEllipse(123,301,4,4,penRed);break;
            case 135: scene->addEllipse(123,290,4,4,penRed);break;
            case 140: scene->addEllipse(123,278,4,4,penRed);break;
            case 145: scene->addEllipse(123,267,4,4,penRed);break;
            case 150: scene->addEllipse(123,258,4,4,penRed);break;
            case 155: scene->addEllipse(123,249,4,4,penRed);break;
            case 160: scene->addEllipse(123,238,4,4,penRed);break;
            case 165: scene->addEllipse(123,228,4,4,penRed);break;
            case 170: scene->addEllipse(123,218,4,4,penRed);break;
            case 175: scene->addEllipse(123,210,4,4,penRed);break;
            case 180: scene->addEllipse(123,201,4,4,penRed);break;
            case 185: scene->addEllipse(123,195,4,4,penRed);break;
            case 190: scene->addEllipse(123,186,4,4,penRed);break;
        }
    }
    if (l1>0)
    {
        switch (l1)
        {
            case 5: scene->addEllipse(181,720,4,4,penRed);break;
            case 10: scene->addEllipse(181,690,4,4,penRed);break;
            case 15: scene->addEllipse(181,670,4,4,penRed);break;
            case 20: scene->addEllipse(181,645,4,4,penRed);break;
            case 25: scene->addEllipse(181,625,4,4,penRed);break;
            case 30: scene->addEllipse(181,605,4,4,penRed);break;
            case 35: scene->addEllipse(181,585,4,4,penRed);break;
            case 40: scene->addEllipse(181,565,4,4,penRed);break;
            case 45: scene->addEllipse(181,548,4,4,penRed);break;
            case 50: scene->addEllipse(181,530,4,4,penRed);break;
            case 55: scene->addEllipse(181,513,4,4,penRed);break;
            case 60: scene->addEllipse(181,493,4,4,penRed);break;
            case 65: scene->addEllipse(181,479,4,4,penRed);break;
            case 70: scene->addEllipse(181,462,4,4,penRed);break;
            case 75: scene->addEllipse(181,444,4,4,penRed);break;
            case 80: scene->addEllipse(181,427,4,4,penRed);break;
            case 85: scene->addEllipse(181,416,4,4,penRed);break;
            case 90: scene->addEllipse(181,401,4,4,penRed);break;
            case 95: scene->addEllipse(181,387,4,4,penRed);break;
            case 100: scene->addEllipse(181,373,4,4,penRed);break;
            case 105: scene->addEllipse(181,361,4,4,penRed);break;
            case 110: scene->addEllipse(181,347,4,4,penRed);break;
            case 115: scene->addEllipse(181,335,4,4,penRed);break;
            case 120: scene->addEllipse(181,321,4,4,penRed);break;
            case 125: scene->addEllipse(181,312,4,4,penRed);break;
            case 130: scene->addEllipse(181,301,4,4,penRed);break;
            case 135: scene->addEllipse(181,290,4,4,penRed);break;
            case 140: scene->addEllipse(181,278,4,4,penRed);break;
            case 145: scene->addEllipse(181,267,4,4,penRed);break;
            case 150: scene->addEllipse(181,258,4,4,penRed);break;
            case 155: scene->addEllipse(181,249,4,4,penRed);break;
            case 160: scene->addEllipse(181,238,4,4,penRed);break;
            case 165: scene->addEllipse(181,228,4,4,penRed);break;
            case 170: scene->addEllipse(181,218,4,4,penRed);break;
            case 175: scene->addEllipse(181,210,4,4,penRed);break;
            case 180: scene->addEllipse(181,201,4,4,penRed);break;
            case 185: scene->addEllipse(181,195,4,4,penRed);break;
            case 190: scene->addEllipse(181,186,4,4,penRed);break;
        }
    }






}
void MainWindow::on_r_1_editingFinished()
{
    r1 = ui->r_1->text().toInt();
    cout<< "r1: " << r1 << endl;
    drawPoints();
}
void MainWindow::on_r_2_editingFinished()
{
    r2 = ui->r_2->text().toInt();
    cout<< "r2: " << r2 << endl;
    drawPoints();
}
void MainWindow::on_r_3_editingFinished()
{
    r3 = ui->r_3->text().toInt();
    cout<< "r3: " << r3 << endl;
    drawPoints();
}
void MainWindow::on_r_4_editingFinished()
{
    r4 = ui->r_4->text().toInt();
    cout<< "r4: " << r4 << endl;
    drawPoints();
}
void MainWindow::on_r_5_editingFinished()
{
    r5 = ui->r_5->text().toInt();
    cout<< "r5: " << r5 << endl;
    drawPoints();
}
void MainWindow::on_r_6_editingFinished()
{
    r6 = ui->r_6->text().toInt();
    cout<< "r6: " << r6 << endl;
    drawPoints();
}
void MainWindow::on_r_7_editingFinished()
{
    r7 = ui->r_7->text().toInt();
    cout<< "r7: " << r7 << endl;
    drawPoints();
}
void MainWindow::on_r_8_editingFinished()
{
    r8 = ui->r_8->text().toInt();
    cout<< "r8: " << r8 << endl;
    drawPoints();
}
void MainWindow::on_r_9_editingFinished()
{
    r9 = ui->r_9->text().toInt();
    cout<< "r9: " << r9 << endl;
    drawPoints();
}
void MainWindow::on_r_10_editingFinished()
{
    r10 = ui->r_10->text().toInt();
    cout<< "r10: " << r10 << endl;
    drawPoints();
}
void MainWindow::on_r_11_editingFinished()
{
    r11 = ui->r_11->text().toInt();
    cout<< "r11: " << r11 << endl;
    drawPoints();
}
void MainWindow::on_r_12_editingFinished()
{
    r12 = ui->r_12->text().toInt();
    cout<< "r12: " << r12 << endl;
    drawPoints();
}

void MainWindow::on_l_1_editingFinished()
{
    l1 = ui->l_1->text().toInt();
    cout<< "l1: " << l1 << endl;
    drawPoints();
}
void MainWindow::on_l_2_editingFinished()
{
    l2 = ui->l_2->text().toInt();
    cout<< "l2: " << l2 << endl;
    drawPoints();
}
void MainWindow::on_l_3_editingFinished()
{
    l3 = ui->l_3->text().toInt();
    cout<< "l3: " << l3 << endl;
    drawPoints();
}
void MainWindow::on_l_4_editingFinished()
{
    l4 = ui->l_4->text().toInt();
    cout<< "l4: " << l4 << endl;
    drawPoints();
}
void MainWindow::on_l_5_editingFinished()
{
    l5 = ui->l_5->text().toInt();
    cout<< "l5: " << l5 << endl;
    drawPoints();
}
void MainWindow::on_l_6_editingFinished()
{
    l6 = ui->l_6->text().toInt();
    cout<< "l6: " << l6 << endl;
    drawPoints();
}
void MainWindow::on_l_7_editingFinished()
{
    l7 = ui->l_7->text().toInt();
    cout<< "l7: " << l7 << endl;
    drawPoints();
}
void MainWindow::on_l_8_editingFinished()
{
    l8 = ui->l_8->text().toInt();
    cout<< "l8: " << l8 << endl;
    drawPoints();
}
void MainWindow::on_l_9_editingFinished()
{
    l9 = ui->l_9->text().toInt();
    cout<< "l9: " << l9 << endl;
    drawPoints();
}
void MainWindow::on_l_10_editingFinished()
{
    l10 = ui->l_10->text().toInt();
    cout<< "l10: " << l10 << endl;
    drawPoints();
}
void MainWindow::on_l_11_editingFinished()
{
    l11 = ui->l_11->text().toInt();
    cout<< "l11: " << l11 << endl;
    drawPoints();
}
void MainWindow::on_l_12_editingFinished()
{
    l12 = ui->l_12->text().toInt();
    cout<< "l12: " << l12 << endl;
    drawPoints();
}

void MainWindow::on_button_exit_clicked()
{
    app->exit();
}

void MainWindow::on_name_field_textActivated(const QString &arg1)
{
    name_field = arg1;
    cout<< "name_field: " << name_field.toStdString() << endl;
    repaint();
    update();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
//    QPainter p(this);
//    p.setPen(Qt::green);
//    p.drawText(10,10,"hello");
}
