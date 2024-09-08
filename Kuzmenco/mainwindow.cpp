#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>
#include <fstream>
//#include <regex>
#include <QInputDialog>
#include <QDebug>
using namespace std;
extern QApplication * app;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    cout<<"delta = "<< delta <<endl;
    QFile textFile("../Сlients.txt");
    textFile.open(QIODevice::ReadOnly);
    while(!textFile.atEnd())
    {
        clients.append(textFile.readLine());
    }
    textFile.close();
    for (auto &i:clients)
        i.chop(1);

    ui->name_field->insertItems(0, clients);
    ui->name_field->insertItem(0, "Новый клиент");
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

void MainWindow::saveData()
{
    ofstream fout;
    fout.open(nameOutFile + ".txt");
    fout <<" Имя: "<< name_field.toStdString() <<" / Дата: "<<Date.toStdString() <<" / Измерение № "<<to_string(izmereniye)<<endl<<endl;
    fout << " P   Легкие                   "<< r1 <<"\t" << l1 <<"\t" << Channel_P <<endl;
    fout << " MC  Перикард                 "<< r2 <<"\t" << l2 <<"\t" << Channel_MC <<endl;
    fout << " С   Сердце                   "<< r3 <<"\t" << l3 <<"\t" << Channel_C <<endl;
    fout << " IG  Тонкий кишечник          "<< r4 <<"\t" << l4 <<"\t" << Channel_IG <<endl;
    fout << " TR  Гормональная система     "<< r5 <<"\t" << l5 <<"\t" << Channel_TR <<endl;
    fout << " GI  Толстый кишечник         "<< r6 <<"\t" << l6 <<"\t" << Channel_GI <<endl;
    fout << " " << endl;
    fout << " RP  Селезенка, Поджелудочная "<< r7 <<"\t" << l7 <<"\t" << Channel_RP <<endl;
    fout << " F   Печень                   "<< r8 <<"\t" << l8 <<"\t"<< Channel_F <<endl;
    fout << " R   Почки                    "<< r9 <<"\t" << l9 <<"\t" << Channel_R <<endl;
    fout << " V   Мочевой пузырь           "<< r10 <<"\t" << l10 <<"\t" << Channel_V <<endl;
    fout << " VB  Желчный пузырь           "<< r11 <<"\t" << l11 <<"\t" << Channel_VB <<endl;
    fout << " E   Желудок                  "<< r12 <<"\t" << l12 <<"\t" << Channel_E <<endl;

    fout <<"\nКомментарий:\n"<<comment_message<<endl<<endl;
    fout <<diagnosic_message<<endl;
    fout.close();

    ofstream fout2;
    fout2.open(nameOutFile + ".dat");
    string text_comment = ui->textEdit->toPlainText().toStdString();
//    text_comment = regex_replace(text_comment, std::regex("\n\n"), "\n.\n");
    fout2<<r1<<" "<<r2<<" "<<r3<<" "<<r4<<" "<<r5<<" "<<r6<<" "<<r7<<" "<<r8<<" "<<r9<<" "<<r10<<" "<<r11<<" "<<r12<<" "
            <<l1<<" "<<l2<<" "<<l3<<" "<<l4<<" "<<l5<<" "<<l6<<" "<<l7<<" "<<l8<<" "<<l9<<" "<<l10<<" "<<l11<<" "<<l12
            <<" "<<replace_whitespace(name_field, " ", "@").toStdString()<<" "
            <<ui->dateEdit->date().toJulianDay()<<" "
            <<ui->Izmereniye->text().toStdString()<<" \n"
            <<text_comment;
    fout2.close();
}


void MainWindow::on_button_load_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath().append("/../Data/"),
                                "data (*.dat );;All files (*.*)");
    ifstream fin;
    fin.open(fileName.toStdString());
    string name;
    string number;
    string comment_line1, comment_line2, comment_line3, comment_line4, comment_line5, comment_line6, comment_line7, comment_line8, comment_line9;

//    QFile inputFile(fileName);
//    if (inputFile.open(QIODevice::ReadOnly))
//    {
//       QTextStream in(&inputFile);
//       while (!in.atEnd())
//       {
//          QString line = in.readLine();
//          ...
//       }
//       inputFile.close();
//    }


    int julianDate;
    fin>>r1>>r2>>r3>>r4>>r5>>r6>>r7>>r8>>r9>>r10>>r11>>r12>>
         l1>>l2>>l3>>l4>>l5>>l6>>l7>>l8>>l9>>l10>>l11>>l12>>name>>julianDate>>number;
    QString replased(name.c_str());
    replased = replace_whitespace(replased, "@", " ");
    name = replased.toStdString();
    bool ex = false;
    string text_comment;
    getline(fin, comment_line1); //Надо 2 раза
    if (!ex)
    {
        getline(fin, comment_line1);
        if (comment_line1 != "")
        {
            text_comment.append(comment_line1);
        }
        else ex = true;
    }
    if (!ex)
    {
        getline(fin, comment_line2);
        if (comment_line2 != "")
        {
            text_comment.append("\n");
            text_comment.append(comment_line2);
        }
        else ex = true;
    }
    if (!ex)
    {
        getline(fin, comment_line3);
        if (comment_line3 != "")
        {
            text_comment.append("\n");
            text_comment.append(comment_line3);
        }
        else ex = true;
    }
    if (!ex)
    {
        getline(fin, comment_line4);
        if (comment_line4 != "")
        {
            text_comment.append("\n");
            text_comment.append(comment_line4);
        }
        else ex = true;
    }
    if (!ex)
    {
        getline(fin, comment_line5);
        if (comment_line5 != "")
        {
            text_comment.append("\n");
            text_comment.append(comment_line5);
        }
        else ex = true;
    }
    if (!ex)
    {
        getline(fin, comment_line6);
        if (comment_line6 != "")
        {
            text_comment.append("\n");
            text_comment.append(comment_line6);
        }
        else ex = true;
    }
    if (!ex)
    {
        getline(fin, comment_line7);
        if (comment_line7 != "")
        {
            text_comment.append("\n");
            text_comment.append(comment_line7);
        }
        else ex = true;
    }
    if (!ex)
    {
        getline(fin, comment_line8);
        if (comment_line8 != "")
        {
            text_comment.append("\n");
            text_comment.append(comment_line8);
        }
        else ex = true;
    }
    if (!ex)
    {
        getline(fin, comment_line9);
        if (comment_line9 != "")
        {
            text_comment.append("\n");
            text_comment.append(comment_line9);
        }
        else ex = true;
    }
    fin.close();

    ui->textEdit->setText(QString::fromStdString(text_comment));
    ui->Izmereniye->setText(QString::fromStdString(number));
    izmereniye = atoi(number.c_str());
    ui->name_field->setCurrentText(QString::fromStdString(name));
    name_field = QString::fromStdString(name);
    ui->dateEdit->setDate(QDate::fromJulianDay(julianDate));
    ui->r_1->setText(QString::number(r1));
    ui->r_2->setText(QString::number(r2));
    ui->r_3->setText(QString::number(r3));
    ui->r_4->setText(QString::number(r4));
    ui->r_5->setText(QString::number(r5));
    ui->r_6->setText(QString::number(r6));
    ui->r_7->setText(QString::number(r7));
    ui->r_8->setText(QString::number(r8));
    ui->r_9->setText(QString::number(r9));
    ui->r_10->setText(QString::number(r10));
    ui->r_11->setText(QString::number(r11));
    ui->r_12->setText(QString::number(r12));
    ui->l_1->setText(QString::number(l1));
    ui->l_2->setText(QString::number(l2));
    ui->l_3->setText(QString::number(l3));
    ui->l_4->setText(QString::number(l4));
    ui->l_5->setText(QString::number(l5));
    ui->l_6->setText(QString::number(l6));
    ui->l_7->setText(QString::number(l7));
    ui->l_8->setText(QString::number(l8));
    ui->l_9->setText(QString::number(l9));
    ui->l_10->setText(QString::number(l10));
    ui->l_11->setText(QString::number(l11));
    ui->l_12->setText(QString::number(l12));
    diagnostic_end = false;
    drawPoints();
}

void MainWindow::on_dateEdit_dateChanged(const QDate &date)
{
    Date = ui->dateEdit->text();
//    cout<< "Date: " << Date.toStdString() << endl;
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
//    cout<< "name_field: " << name_field.toStdString() << endl;
    repaint();
    update();
    if (name_field == "Новый клиент")
    {
        addNewClient();
    }
}

void MainWindow::addNewClient()
{
    bool ok;
     QString text = QInputDialog::getText(this, tr("Добавление клиента"),
                                          tr("Введите имя:"), QLineEdit::Normal,
                                          QDir::home().dirName(), &ok);
     if (ok && !text.isEmpty())
         ui->name_field->insertItem(1, text);
     clients.append(text);
     clients.sort();

     QFile textFile("../Сlients.txt");
     textFile.open(QIODevice::WriteOnly);
     for (auto &i:clients)
     {
         if (i != "")
         {
             textFile.write(i.toUtf8());
             textFile.write("\n");
         }
     }
     textFile.close();
}

void MainWindow::on_Izmereniye_editingFinished()
{
    izmereniye = ui->Izmereniye->text().toInt();
}

void MainWindow::on_textEdit_textChanged()
{
    comment_message = ui->textEdit->toPlainText().toStdString();
}


