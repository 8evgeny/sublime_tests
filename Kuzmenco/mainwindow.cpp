#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;
extern QApplication * app;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->name_field->setCurrentIndex(2);
    name_field = ui->name_field->currentText();
    ui->Izmereniye->insert("1");
    ui->r_1->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}

void MainWindow::on_dateEdit_dateChanged(const QDate &date)
{
    Date = ui->dateEdit->text();
    cout<< "Date: " << Date.toStdString() << endl;
}
void MainWindow::on_r_1_editingFinished()
{
    if (ui->r_1->text().toInt()%5 == 0)
    {
        r1 = ui->r_1->text().toInt();
        drawPoints();
    }
    else
    {
        ui->r_1->setText("");
    }
}
void MainWindow::on_r_2_editingFinished()
{
    if (ui->r_2->text().toInt()%5 == 0)
    {
        r2 = ui->r_2->text().toInt();
        drawPoints();
    }
    else
    {
        ui->r_2->setText("");
    }
}
void MainWindow::on_r_3_editingFinished()
{
    if (ui->r_3->text().toInt()%5 == 0)
    {
        r3 = ui->r_3->text().toInt();
        drawPoints();
    }
    else
    {
        ui->r_3->setText("");
    }
}
void MainWindow::on_r_4_editingFinished()
{
    if (ui->r_4->text().toInt()%5 == 0)
    {
        r4 = ui->r_4->text().toInt();
        drawPoints();
    }
    else
    {
        ui->r_4->setText("");
    }
}
void MainWindow::on_r_5_editingFinished()
{
    if (ui->r_5->text().toInt()%5 == 0)
    {
        r5 = ui->r_5->text().toInt();
        drawPoints();
    }
    else
    {
        ui->r_5->setText("");
    }
}
void MainWindow::on_r_6_editingFinished()
{
    if (ui->r_6->text().toInt()%5 == 0)
    {
        r6 = ui->r_6->text().toInt();
        drawPoints();
    }
    else
    {
        ui->r_6->setText("");
    }
}
void MainWindow::on_r_7_editingFinished()
{
    if (ui->r_7->text().toInt()%5 == 0)
    {
        r7 = ui->r_7->text().toInt();
        drawPoints();
    }
    else
    {
        ui->r_7->setText("");
    }
}
void MainWindow::on_r_8_editingFinished()
{
    if (ui->r_8->text().toInt()%5 == 0)
    {
        r8 = ui->r_8->text().toInt();
        drawPoints();
    }
    else
    {
        ui->r_8->setText("");
    }
}
void MainWindow::on_r_9_editingFinished()
{
    if (ui->r_9->text().toInt()%5 == 0)
    {
        r9 = ui->r_9->text().toInt();
        drawPoints();
    }
    else
    {
        ui->r_9->setText("");
    }
}
void MainWindow::on_r_10_editingFinished()
{
    if (ui->r_10->text().toInt()%5 == 0)
    {
        r10 = ui->r_10->text().toInt();
        drawPoints();
    }
    else
    {
        ui->r_10->setText("");
    }
}
void MainWindow::on_r_11_editingFinished()
{
    if (ui->r_11->text().toInt()%5 == 0)
    {
        r11 = ui->r_11->text().toInt();
        drawPoints();
    }
    else
    {
        ui->r_11->setText("");
    }
}
void MainWindow::on_r_12_editingFinished()
{
    if (ui->r_12->text().toInt()%5 == 0)
    {
        r12 = ui->r_12->text().toInt();
        drawPoints();
    }
    else
    {
        ui->r_12->setText("");
    }
}

void MainWindow::on_l_1_editingFinished()
{
    if (ui->l_1->text().toInt()%5 == 0)
    {
        l1 = ui->l_1->text().toInt();
        drawPoints();
    }
    else
    {
        ui->l_1->setText("");
    }
}
void MainWindow::on_l_2_editingFinished()
{
    if (ui->l_2->text().toInt()%5 == 0)
    {
        l2 = ui->l_2->text().toInt();
        drawPoints();
    }
    else
    {
        ui->l_2->setText("");
    }
}
void MainWindow::on_l_3_editingFinished()
{
    if (ui->l_3->text().toInt()%5 == 0)
    {
        l3 = ui->l_3->text().toInt();
        drawPoints();
    }
    else
    {
        ui->l_3->setText("");
    }
}
void MainWindow::on_l_4_editingFinished()
{
    if (ui->l_4->text().toInt()%5 == 0)
    {
        l4 = ui->l_4->text().toInt();
        drawPoints();
    }
    else
    {
        ui->l_4->setText("");
    }
}
void MainWindow::on_l_5_editingFinished()
{
    if (ui->l_5->text().toInt()%5 == 0)
    {
        l5 = ui->l_5->text().toInt();
        drawPoints();
    }
    else
    {
        ui->l_5->setText("");
    }
}
void MainWindow::on_l_6_editingFinished()
{
    if (ui->l_6->text().toInt()%5 == 0)
    {
        l6 = ui->l_6->text().toInt();
        drawPoints();
    }
    else
    {
        ui->l_6->setText("");
    }
}
void MainWindow::on_l_7_editingFinished()
{
    if (ui->l_7->text().toInt()%5 == 0)
    {
        l7 = ui->l_7->text().toInt();
        drawPoints();
    }
    else
    {
        ui->l_7->setText("");
    }
}
void MainWindow::on_l_8_editingFinished()
{
    if (ui->l_8->text().toInt()%5 == 0)
    {
        l8 = ui->l_8->text().toInt();
        drawPoints();
    }
    else
    {
        ui->l_8->setText("");
    }
}
void MainWindow::on_l_9_editingFinished()
{
    if (ui->l_9->text().toInt()%5 == 0)
    {
        l9 = ui->l_9->text().toInt();
        drawPoints();
    }
    else
    {
        ui->l_9->setText("");
    }
}
void MainWindow::on_l_10_editingFinished()
{
    if (ui->l_10->text().toInt()%5 == 0)
    {
        l10 = ui->l_10->text().toInt();
        drawPoints();
    }
    else
    {
        ui->l_10->setText("");
    }
}
void MainWindow::on_l_11_editingFinished()
{
    if (ui->l_11->text().toInt()%5 == 0)
    {
        l11 = ui->l_11->text().toInt();
        drawPoints();
    }
    else
    {
        ui->l_11->setText("");
    }
}
void MainWindow::on_l_12_editingFinished()
{
    if (ui->l_12->text().toInt()%5 == 0)
    {
        l12 = ui->l_12->text().toInt();
        drawPoints();
    }
    else
    {
        ui->l_12->setText("");
    }
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

void MainWindow::on_Izmereniye_editingFinished()
{
    izmereniye = ui->Izmereniye->text().toInt();
}


void MainWindow::on_pushButton_3_clicked()
{
    cout<< "button Clear: "<<endl;
        drawPoints();
}

