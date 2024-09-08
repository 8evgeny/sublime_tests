#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>
#include <fstream>
#include <stdexcept>
#include <QInputDialog>
#include <QDebug>
#include <QTextCodec>

using namespace std;
extern QApplication * app;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    cout<<"delta = "<< delta <<endl;

    QDir dirr=QDir::current();
    dirr.cdUp();
    QString path =  dirr.absolutePath() + "/Сlients.txt";
//    qDebug()<<path;
    QFile textFile(path);
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
    string name = QString(nameOutFile + ".txt").toStdString();
// cout << name <<endl;
    QFile outputFile(name.c_str());
    if (outputFile.open(QIODevice::WriteOnly))
    {
        QString line1 = " Имя: " + name_field + " / Дата: " + Date + " / Измерение № " + QString::number(izmereniye) + "\n";
        QByteArray block1(line1.toStdString().c_str());
        outputFile.write(block1);
        QString line2 = " P   Легкие                   " + QString::number(r1) + "\t" + QString::number(l1) + "\t" + QString::fromStdString(Channel_P) + "\n";
        QByteArray block2(line2.toStdString().c_str());
        outputFile.write(block2);
        QString line3 = " MC  Перикард                 " + QString::number(r2) + "\t" + QString::number(l2) + "\t" + QString::fromStdString(Channel_MC) + "\n";
        QByteArray block3(line3.toStdString().c_str());
        outputFile.write(block3);
        QString line4 = " С   Сердце                   " + QString::number(r3) + "\t" + QString::number(l3) + "\t" + QString::fromStdString(Channel_C) + "\n";
        QByteArray block4(line4.toStdString().c_str());
        outputFile.write(block4);
        QString line5 = " IG  Тонкий кишечник          " + QString::number(r4) + "\t" + QString::number(l4) + "\t" + QString::fromStdString(Channel_C) + "\n";
        QByteArray block5(line5.toStdString().c_str());
        outputFile.write(block5);
        QString line6 = " TR  Гормональная система     " + QString::number(r5) + "\t" + QString::number(l5) + "\t" + QString::fromStdString(Channel_TR) + "\n";
        QByteArray block6(line6.toStdString().c_str());
        outputFile.write(block6);
        QString line7 = " GI  Толстый кишечник         " + QString::number(r6) + "\t" + QString::number(l6) + "\t" + QString::fromStdString(Channel_GI) + "\n\n";
        QByteArray block7(line7.toStdString().c_str());
        outputFile.write(block7);

        QString line8 = " RP  Селезенка, Поджелудочная " + QString::number(r7) + "\t" + QString::number(l7) + "\t" + QString::fromStdString(Channel_RP) + "\n";
        QByteArray block8(line8.toStdString().c_str());
        outputFile.write(block8);
        QString line9 = " F   Печень                   " + QString::number(r8) + "\t" + QString::number(l8) + "\t" + QString::fromStdString(Channel_F) + "\n";
        QByteArray block9(line9.toStdString().c_str());
        outputFile.write(block9);
        QString line10 = " R   Почки                    " + QString::number(r9) + "\t" + QString::number(l9) + "\t" + QString::fromStdString(Channel_R) + "\n";
        QByteArray block10(line10.toStdString().c_str());
        outputFile.write(block10);
        QString line11 = " V   Мочевой пузырь           " + QString::number(r10) + "\t" + QString::number(l10) + "\t" + QString::fromStdString(Channel_V) + "\n";
        QByteArray block11(line11.toStdString().c_str());
        outputFile.write(block11);
        QString line12 = " VB  Желчный пузырь           " + QString::number(r11) + "\t" + QString::number(l11) + "\t" + QString::fromStdString(Channel_VB) + "\n";
        QByteArray block12(line12.toStdString().c_str());
        outputFile.write(block12);
        QString line13 = " E   Желудок                  " + QString::number(r12) + "\t" + QString::number(l12) + "\t" + QString::fromStdString(Channel_E) + "\n\n";
        QByteArray block13(line13.toStdString().c_str());
        outputFile.write(block13);
        //comment
        QString line14 = comment_message;
        QByteArray block14(line14.toStdString().c_str());
        outputFile.write("Комментарий:\n");
        outputFile.write(block14);
        //diagn
        QString line15 = QString::fromStdString(diagnosic_message);
        QByteArray block15(line15.toStdString().c_str());
        outputFile.write(block15);
        outputFile.close();
    }
    else cout << "error open file!!!" <<endl;

    string data = QString(nameOutFile + ".dat").toStdString();
    QFile dataFile(data.c_str());
    if (dataFile.open(QIODevice::WriteOnly))
    {
        QString linedata =
                QString::number(r1) + " " + QString::number(r2) + " " + QString::number(r3) + " " +
                QString::number(r4) + " " + QString::number(r5) + " " + QString::number(r6) + " " +
                QString::number(r7) + " " + QString::number(r8) + " " + QString::number(r9) + " " +
                QString::number(r10) + " " + QString::number(r11) + " " + QString::number(r12) + " " +
                QString::number(l1) + " " + QString::number(l2) + " " + QString::number(l3) + " " +
                QString::number(l4) + " " + QString::number(l5) + " " + QString::number(l6) + " " +
                QString::number(l7) + " " + QString::number(l8) + " " + QString::number(l9) + " " +
                QString::number(l10) + " " + QString::number(l11) + " " + QString::number(l12) + " " +
                name_field.replace(" ", "@") + " " + QString::number(ui->dateEdit->date().toJulianDay()) + " " +
                ui->Izmereniye->text() + "\n";
        QByteArray blockData(linedata.toStdString().c_str());
        dataFile.write(blockData);
        QString commentData = ui->textEdit->toPlainText();
        QByteArray blockComment(commentData.toStdString().c_str());
        dataFile.write(blockComment);
        dataFile.close();
    }
    else cout << "error open file!!!" <<endl;
}

QStringList unpack(QString const& string)
{
    return string.split(" ");
}

QString russian(QString text)
 {
    string tmp = text.toStdString();
    QByteArray encodedString = QByteArray::fromStdString(tmp);
    QTextCodec *codec = QTextCodec::codecForName("CP1251");
    return codec->fromUnicode(encodedString);
 }

void MainWindow::on_button_load_clicked()
{
     QString fileName = "";
    fileName = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),
                                QDir::currentPath().append("/../Data/"),
                                "data (*.dat );;All files (*.*)");

    QStringList comment;
    QString data;
    if(fileName != "")
    {
        QFile inputFile(fileName);

        if (inputFile.open(QIODevice::ReadOnly))
        {
            bool firstLine = true;
            QTextStream in(&inputFile);
            while (!in.atEnd())
            {
                if (firstLine)
                {
                    data = in.readLine();
                    firstLine = false;
                }
                else
                {
                    comment.push_back(in.readLine());
                }
            }
            inputFile.close();
        }
        else cout << "error open file!!!" <<endl;

        int julianDate;
        QStringList dataList = unpack(data);
    //    qDebug()<<dataList;
    //    qDebug()<<comment;
        r1 = dataList[0].toInt();
        r2 = dataList[1].toInt();
        r3 = dataList[2].toInt();
        r4 = dataList[3].toInt();
        r5 = dataList[4].toInt();
        r6 = dataList[5].toInt();
        r7 = dataList[6].toInt();
        r8 = dataList[7].toInt();
        r9 = dataList[8].toInt();
        r10 = dataList[9].toInt();
        r11 = dataList[10].toInt();
        r12 = dataList[11].toInt();

        l1 = dataList[12].toInt();
        l2 = dataList[13].toInt();
        l3 = dataList[14].toInt();
        l4 = dataList[15].toInt();
        l5 = dataList[16].toInt();
        l6 = dataList[17].toInt();
        l7 = dataList[18].toInt();
        l8 = dataList[19].toInt();
        l9 = dataList[20].toInt();
        l10 = dataList[21].toInt();
        l11 = dataList[22].toInt();
        l12 = dataList[23].toInt();

        name_field = dataList[24];
//        name_field = russian(dataList[24]);
        julianDate = dataList[25].toInt();
        QString number = dataList[26];
        name_field = name_field.replace("@", " ");
        string text_comment;
        int numLineComment = comment.size();

        for (int i = 0; i < numLineComment; ++i)
        {
            string line = comment[i].toStdString();
            text_comment.append(line);
            text_comment.append("\n");
        }
    //    cout<<text_comment<<endl;

        ui->textEdit->setText(QString::fromStdString(text_comment));
        ui->Izmereniye->setText(number);
        izmereniye = number.toInt();
        ui->name_field->setCurrentText(name_field);
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
    }//END  if(fileName != "")
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

//void MainWindow::on_name_field_textActivated(const QString &arg1)
//{
//    name_field = arg1;
////    qDebug()<< "name_field: " << name_field;
//    repaint();
//    update();
//    if (name_field == "Новый клиент")
//    {
//        addNewClient();
//    }
//}

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

     QDir dirr=QDir::current();
     dirr.cdUp();
     QString path =  dirr.absolutePath() + "/Сlients.txt";
     QFile textFile(path);
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
    comment_message = ui->textEdit->toPlainText();
}



void MainWindow::on_name_field_activated(const QString &arg1)
{
    name_field = arg1;
//    qDebug()<< "name_field: " << name_field;
    repaint();
    update();
    if (name_field == "Новый клиент")
    {
        addNewClient();
    }
}
