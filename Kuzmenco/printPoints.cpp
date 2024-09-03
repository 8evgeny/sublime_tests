#include "mainwindow.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QFile>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QRect>
#include <QScreen>
#include <fstream>
#include <iostream>


using namespace std;
extern QScreen *screenMain;
extern QPen penRed;
extern QPen penGreen;
extern QPen penBlue;
extern QPen penYellow;
extern QPen penRedLine;
extern QPen penGreenLine;
extern QPen penBlueLine;
extern QPen penBlack;
extern QGraphicsScene * scene;
extern QPen penTriangle;

float MainWindow::calcCornerLine(float in)
{
    if (in > 0 && in < 5) return (712.0f + (5.0f - in) * 4.4f);
    if (in > 5 && in <= 10) return (684.0f + (10.0f - in) * 5.6f);
    if (in > 10 && in <= 15) return (661.0f + (15.0f - in) * 4.6f);
    if (in > 15 && in <= 20) return (635.0f + (20.0f - in) * 5.2f);
    if (in > 20 && in <= 25) return (612.0f + (25.0f - in) * 4.8f);
    if (in > 25 && in <= 30) return (589.0f + (30.0f - in) * 4.6f);
    if (in > 30 && in <= 35) return 566.0f + (35.0f - in) * 4.6f;
    if (in > 35 && in <= 40) return 544.0f + (40.0f - in) * 4.4f;
    if (in > 40 && in <= 45) return 523 + (45.0f - in) * 4.2f;
    if (in > 45 && in <= 50) return 503 + (50.0f - in) * 4.0f;
    if (in > 50 && in <= 55) return 483 + (55.0f - in) * 4.0f;
    if (in > 55 && in <= 60) return 463 + (60.0f - in) * 4.0f;
    if (in > 60 && in <= 65) return 443 + (65.0f - in) * 4.0f;
    if (in > 65 && in <= 70) return 423 + (70.0f - in) * 4.0f;
    if (in > 70 && in <= 75) return 409 + (75.0f - in) * 2.8f;
    if (in > 75 && in <= 80) return 394 + (80.0f - in) * 3.0f;
    if (in > 80 && in <= 85) return 380 + (85.0f - in) * 2.8f;
    if (in > 85 && in <= 90) return 363 + (90.0f - in) * 3.4f;
    if (in > 90 && in <= 95) return 349 + (95.0f - in) * 2.8f;
    if (in > 95 && in <= 100) return 334 + (100.0f - in) * 3.0f;
    if (in > 100 && in <= 105) return 323 + (105.0f - in) * 2.2f;
    if (in > 105 && in <= 110) return 309 + (110.0f - in) * 2.8f;
    if (in > 110 && in <= 115) return 295 + (115.0f - in) * 2.8f;
    if (in > 115 && in <= 120) return 283 + (120.0f - in) * 2.4f;
    if (in > 120 && in <= 125) return 269 + (125.0f - in) * 2.8f;
    if (in > 125 && in <= 130) return 254 + (130.0f - in) * 3.0f;
    if (in > 130 && in <= 135) return 245 + (135.0f - in) * 1.8f;
    if (in > 135 && in <= 140) return 234 + (140.0f - in) * 2.2f;
    return 734;
}

string MainWindow::calculateLetter(float r1, float l1)
{
    float r = 1000.0f - r1;
    float l = 1000.0f - l1;
    float hightY = 1000.0f - calcCornerLine(hight - delta);
    float lowY = 1000.0f - calcCornerLine(low + delta);
if (r < l)
{
    if (r < lowY && l > hightY) return "OK";
    if (l<lowY) return "A/-2";
    if (r<lowY && l>=lowY && l<=hightY) return "A/-1";
    if (r>=lowY && r<hightY && l<=hightY) return "A/0";
    if (r>=lowY && r<=hightY && l>hightY) return "A/1";
    if (r>hightY) return "A/2";
    return "ERR1";
}
if (r == l)
{
    if (r<lowY) return "B/-2";
    if (r == lowY) return "B/-1";
    if (r>lowY && r<hightY) return "B/0";
    if (r == hightY) return "B/1";
    if (r>hightY ) return "B/2";
    return "ERR2";
}
if (r > l)
{
    if (l<lowY && r>hightY) return "OP";
    if (r<lowY) return "C/-2";

    if (r>=lowY && r <=hightY && l<lowY ) return "C/-1";
    if (r<=hightY && l>=lowY) return "C/0";
    if (r>hightY && l<=hightY ) return "C/1";
    if (l>hightY) return "A/2";
    return "ERR3";
}
return "ERR";
}

void MainWindow::calculateLetters()
{
    Channel_P = calculateLetter((float)r1y, (float)l1y);
    Channel_MC = calculateLetter((float)r2y, (float)l2y);
    Channel_C = calculateLetter((float)r3y, (float)l3y);
    Channel_IG = calculateLetter((float)r4y, (float)l4y);
    Channel_TR = calculateLetter((float)r5y, (float)l5y);
    Channel_GI = calculateLetter((float)r6y, (float)l6y);
    Channel_RP = calculateLetter((float)r7y, (float)l7y);
    Channel_F = calculateLetter((float)r8y, (float)l8y);
    Channel_R = calculateLetter((float)r9y, (float)l9y);
    Channel_V = calculateLetter((float)r10y, (float)l10y);
    Channel_VB = calculateLetter((float)r11y, (float)l11y);
    Channel_E = calculateLetter((float)r12y, (float)l12y);
}

void MainWindow::drawPoints()
{
    scene->clear();
    r1l1();
    r2l2();
    r3l3();
    r4l4();
    r5l5();
    r6l6();
    r7l7();
    r8l8();
    r9l9();
    r10l10();
    r11l11();
    r12l12();
    QWidget::repaint();
    averadge = (float)(r1+r2+r3+r4+r5+r6+r7+r8+r9+r10+r11+r12+
                l1+l2+l3+l4+l5+l6+l7+l8+l9+l10+l11+l12)/24;

    hight = averadge + 7;
    low = averadge - 7;
    cout<<"hight: "<<hight<<endl;
    cout<<"low: "<<low<<endl;
    if (low < 0) low = 0;

    //Проверка что все значения введены
    if (r1>0 && r2>0 && r3>0 && r4>0 && r5>0 && r6>0 && r7>0 && r8>0 && r9>0 && r10>0 && r11>0 && r12>0 &&
        l1>0 && l2>0 && l3>0 && l4>0 && l5>0 && l6>0 && l7>0 && l8>0 && l9>0 && l10>0 && l11>0 && l12>0)
    {
        scene->addLine(corner_x_begin, calcCornerLine(hight), corner_x_end, calcCornerLine(hight), penYellow);
        scene->addLine(corner_x_begin, calcCornerLine(low), corner_x_end, calcCornerLine(low), penYellow);
        calculateLetters();
        diagnostic();
    }
}



void MainWindow::on_button_save_clicked()
{
    string cmd = "mkdir -p ../Data/" + name_field.toStdString();
    system(cmd.c_str());

    QString path = "../Data/" + name_field + "/" + name_field + "_" + Date + "_№" + to_string(izmereniye).c_str();
    nameOutFile = path.toStdString() ;

    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
    image.load("table.png");

    QPixmap screenshot = screenMain->grabWindow(0);
//    QPixmap screenShot = screenMain->grabWindow(0, 100, 100, 1000, 800);
    QFile file("screenshot.png");
    file.open(QIODevice::WriteOnly);
    screenshot.save(&file, "PNG");
    file.close();
//    QImage image;
//    image.load("screenshot.png");
    QPainter painter(&image);
    scene->render(&painter);

    image.save(QString::fromStdString(nameOutFile + ".png"));
    saveData();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    //        QGraphicsTextItem * io = new QGraphicsTextItem;
    //        io->setDefaultTextColor(Qt::red);
    //        QFont font;
    //        font.setPixelSize(20);
    //        font.setBold(false);
    //        font.setFamily("Calibri");
    //        io->setPos(r1x + 8 ,700);
    //        io->setFont(font);
    //        io->setPlainText("A0");
    //        scene->addItem(io);

}

void MainWindow::r1l1() //P
{
    if (r1 > 0)
    {
        switch (r1)
        {
            case 5:  r1y = 720; break;
            case 10: r1y = 690; break;
            case 15: r1y = 670; break;
            case 20: r1y = 645; break;
            case 25: r1y = 625; break;
            case 30: r1y = 605; break;
            case 35: r1y = 585; break;
            case 40: r1y = 565; break;
            case 45: r1y = 548; break;
            case 50: r1y = 530; break;
            case 55: r1y = 513; break;
            case 60: r1y = 493; break;
            case 65: r1y = 479; break;
            case 70: r1y = 462; break;
            case 75: r1y = 444; break;
            case 80: r1y = 427; break;
            case 85: r1y = 416; break;
            case 90: r1y = 401; break;
            case 95: r1y = 387; break;
            case 100: r1y = 373; break;
            case 105: r1y = 361; break;
            case 110: r1y = 347; break;
            case 115: r1y = 335; break;
            case 120: r1y = 321; break;
            case 125: r1y = 312; break;
            case 130: r1y = 301; break;
            case 135: r1y = 290; break;
            case 140: r1y = 278; break;
            case 145: r1y = 267; break;
            case 150: r1y = 258; break;
            case 155: r1y = 249; break;
            case 160: r1y = 238; break;
            case 165: r1y = 228; break;
            case 170: r1y = 218; break;
            case 175: r1y = 210; break;
            case 180: r1y = 201; break;
            case 185: r1y = 195; break;
            case 190: r1y = 186; break;
        }
        scene->addEllipse(r1x, r1y, 4, 4, penYellow);
    }// r1
    if (l1>0)
    {
        switch (l1)
        {
            case 5:  l1y = 720; break;
            case 10: l1y = 690; break;
            case 15: l1y = 670; break;
            case 20: l1y = 645; break;
            case 25: l1y = 625; break;
            case 30: l1y = 605; break;
            case 35: l1y = 585; break;
            case 40: l1y = 565; break;
            case 45: l1y = 548; break;
            case 50: l1y = 530; break;
            case 55: l1y = 513; break;
            case 60: l1y = 493; break;
            case 65: l1y = 479; break;
            case 70: l1y = 462; break;
            case 75: l1y = 444; break;
            case 80: l1y = 427; break;
            case 85: l1y = 416; break;
            case 90: l1y = 401; break;
            case 95: l1y = 387; break;
            case 100: l1y = 373; break;
            case 105: l1y = 361; break;
            case 110: l1y = 347; break;
            case 115: l1y = 335; break;
            case 120: l1y = 321; break;
            case 125: l1y = 312; break;
            case 130: l1y = 301; break;
            case 135: l1y = 290; break;
            case 140: l1y = 278; break;
            case 145: l1y = 267; break;
            case 150: l1y = 258; break;
            case 155: l1y = 249; break;
            case 160: l1y = 238; break;
            case 165: l1y = 228; break;
            case 170: l1y = 218; break;
            case 175: l1y = 210; break;
            case 180: l1y = 201; break;
            case 185: l1y = 195; break;
            case 190: l1y = 186; break;
        }
        scene->addEllipse(l1x, l1y, 4, 4, penYellow);
    }
    if (r1 > 0 && l1 > 0)
    {
        if (r1 == l1)
        {
            scene->addLine(r1x,r1y,l1x,l1y, penGreenLine);
            scene->addEllipse(l1x, l1y, 4, 4, penGreen);
            scene->addEllipse(r1x, r1y, 4, 4, penGreen);
        }
        if (r1 > l1)
        {
            scene->addLine(r1x,r1y,l1x,l1y, penRedLine);
            scene->addEllipse(l1x, l1y, 4, 4, penRed);
            scene->addEllipse(r1x, r1y, 4, 4, penRed);
        }
        if (r1 < l1)
        {
            scene->addLine(r1x,r1y,l1x,l1y, penBlueLine);
            scene->addEllipse(l1x, l1y, 4, 4, penBlue);
            scene->addEllipse(r1x, r1y, 4, 4, penBlue);
        }
    }
}

void MainWindow::r2l2() //MC
{
    if (r2 > 0)
    {
        switch (r2)
        {
            case 5:  r2y = 714; break;
            case 10: r2y = 685; break;
            case 15: r2y = 662; break;
            case 20: r2y = 639; break;
            case 25: r2y = 616; break;
            case 30: r2y = 593; break;
            case 35: r2y = 570; break;
            case 40: r2y = 550; break;
            case 45: r2y = 530; break;
            case 50: r2y = 513; break;
            case 55: r2y = 493; break;
            case 60: r2y = 476; break;
            case 65: r2y = 456; break;
            case 70: r2y = 439; break;
            case 75: r2y = 424; break;
            case 80: r2y = 407; break;
            case 85: r2y = 393; break;
            case 90: r2y = 379; break;
            case 95: r2y = 364; break;
            case 100: r2y = 350; break;
            case 105: r2y = 335; break;
            case 110: r2y = 321; break;
            case 115: r2y = 310; break;
            case 120: r2y = 298; break;
            case 125: r2y = 287; break;
            case 130: r2y = 275; break;
            case 135: r2y = 264; break;
            case 140: r2y = 252; break;
            case 145: r2y = 241; break;
            case 150: r2y = 229; break;
            case 155: r2y = 219; break;
            case 160: r2y = 209; break;
            case 165: r2y = 201; break;
            case 170: r2y = 192; break;
        }
        scene->addEllipse(r2x, r2y, 4, 4, penYellow);
    }// r2
    if (l2>0)
    {
        switch (l2)
        {
        case 5:  l2y = 714; break;
        case 10: l2y = 685; break;
        case 15: l2y = 662; break;
        case 20: l2y = 639; break;
        case 25: l2y = 616; break;
        case 30: l2y = 593; break;
        case 35: l2y = 570; break;
        case 40: l2y = 550; break;
        case 45: l2y = 530; break;
        case 50: l2y = 513; break;
        case 55: l2y = 493; break;
        case 60: l2y = 476; break;
        case 65: l2y = 456; break;
        case 70: l2y = 439; break;
        case 75: l2y = 424; break;
        case 80: l2y = 407; break;
        case 85: l2y = 393; break;
        case 90: l2y = 379; break;
        case 95: l2y = 364; break;
        case 100: l2y = 350; break;
        case 105: l2y = 335; break;
        case 110: l2y = 321; break;
        case 115: l2y = 310; break;
        case 120: l2y = 298; break;
        case 125: l2y = 287; break;
        case 130: l2y = 275; break;
        case 135: l2y = 264; break;
        case 140: l2y = 252; break;
        case 145: l2y = 241; break;
        case 150: l2y = 229; break;
        case 155: l2y = 219; break;
        case 160: l2y = 209; break;
        case 165: l2y = 201; break;
        case 170: l2y = 192; break;
        }
        scene->addEllipse(l2x, l2y, 4, 4, penYellow);
    }
    if (r2 > 0 && l2 > 0)
    {
        if (r2 == l2)
        {
            scene->addLine(r2x,r2y,l2x,l2y, penGreenLine);
            scene->addEllipse(l2x, l2y, 4, 4, penGreen);
            scene->addEllipse(r2x, r2y, 4, 4, penGreen);
        }
        if (r2 > l2)
        {
            scene->addLine(r2x,r2y,l2x,l2y, penRedLine);
            scene->addEllipse(l2x, l2y, 4, 4, penRed);
            scene->addEllipse(r2x, r2y, 4, 4, penRed);
        }
        if (r2 < l2)
        {
            scene->addLine(r2x,r2y,l2x,l2y, penBlueLine);
            scene->addEllipse(l2x, l2y, 4, 4, penBlue);
            scene->addEllipse(r2x, r2y, 4, 4, penBlue);
        }
    }
}

void MainWindow::r3l3() //C
{
    if (r3 > 0)
    {
        switch (r3)
        {
            case 5:  r3y = 708; break;
            case 10: r3y = 679; break;
            case 15: r3y = 651; break;
            case 20: r3y = 625; break;
            case 25: r3y = 599; break;
            case 30: r3y = 571; break;
            case 35: r3y = 548; break;
            case 40: r3y = 525; break;
            case 45: r3y = 499; break;
            case 50: r3y = 476; break;
            case 55: r3y = 456; break;
            case 60: r3y = 436; break;
            case 65: r3y = 419; break;
            case 70: r3y = 398; break;
            case 75: r3y = 379; break;
            case 80: r3y = 361; break;
            case 85: r3y = 347; break;
            case 90: r3y = 333; break;
            case 95: r3y = 316; break;
            case 100: r3y = 301; break;
            case 105: r3y = 287; break;
            case 110: r3y = 273; break;
            case 115: r3y = 258; break;
            case 120: r3y = 244; break;
            case 125: r3y = 232; break;
            case 130: r3y = 221; break;
            case 135: r3y = 210; break;
            case 140: r3y = 198; break;
        }
        scene->addEllipse(r3x, r3y, 4, 4, penYellow);
    }// r3
    if (l3>0)
    {
        switch (l3)
        {
        case 5:  l3y = 708; break;
        case 10: l3y = 679; break;
        case 15: l3y = 651; break;
        case 20: l3y = 625; break;
        case 25: l3y = 599; break;
        case 30: l3y = 571; break;
        case 35: l3y = 548; break;
        case 40: l3y = 525; break;
        case 45: l3y = 499; break;
        case 50: l3y = 476; break;
        case 55: l3y = 456; break;
        case 60: l3y = 436; break;
        case 65: l3y = 419; break;
        case 70: l3y = 398; break;
        case 75: l3y = 379; break;
        case 80: l3y = 361; break;
        case 85: l3y = 347; break;
        case 90: l3y = 333; break;
        case 95: l3y = 316; break;
        case 100: l3y = 301; break;
        case 105: l3y = 287; break;
        case 110: l3y = 273; break;
        case 115: l3y = 258; break;
        case 120: l3y = 244; break;
        case 125: l3y = 232; break;
        case 130: l3y = 221; break;
        case 135: l3y = 210; break;
        case 140: l3y = 198; break;
        }
        scene->addEllipse(l3x, l3y, 4, 4, penYellow);
    }
    if (r3 > 0 && l3 > 0)
    {
        if (r3 == l3)
        {
            scene->addLine(r3x,r3y,l3x,l3y, penGreenLine);
            scene->addEllipse(l3x, l3y, 4, 4, penGreen);
            scene->addEllipse(r3x, r3y, 4, 4, penGreen);
        }
        if (r3 > l3)
        {
            scene->addLine(r3x,r3y,l3x,l3y, penRedLine);
            scene->addEllipse(l3x, l3y, 4, 4, penRed);
            scene->addEllipse(r3x, r3y, 4, 4, penRed);
        }
        if (r3 < l3)
        {
            scene->addLine(r3x,r3y,l3x,l3y, penBlueLine);
            scene->addEllipse(l3x, l3y, 4, 4, penBlue);
            scene->addEllipse(r3x, r3y, 4, 4, penBlue);
        }
    }
}

void MainWindow::r4l4() //IG
{
    if (r4 > 0)
    {
        switch (r4)
        {
        case 5:  r4y = 714; break;
        case 10: r4y = 685; break;
        case 15: r4y = 662; break;
        case 20: r4y = 639; break;
        case 25: r4y = 616; break;
        case 30: r4y = 593; break;
        case 35: r4y = 570; break;
        case 40: r4y = 550; break;
        case 45: r4y = 530; break;
        case 50: r4y = 513; break;
        case 55: r4y = 493; break;
        case 60: r4y = 476; break;
        case 65: r4y = 456; break;
        case 70: r4y = 439; break;
        case 75: r4y = 424; break;
        case 80: r4y = 407; break;
        case 85: r4y = 393; break;
        case 90: r4y = 379; break;
        case 95: r4y = 364; break;
        case 100: r4y = 350; break;
        case 105: r4y = 335; break;
        case 110: r4y = 321; break;
        case 115: r4y = 310; break;
        case 120: r4y = 298; break;
        case 125: r4y = 287; break;
        case 130: r4y = 275; break;
        case 135: r4y = 264; break;
        case 140: r4y = 252; break;
        case 145: r4y = 241; break;
        case 150: r4y = 229; break;
        case 155: r4y = 219; break;
        case 160: r4y = 209; break;
        case 165: r4y = 201; break;
        case 170: r4y = 192; break;
        }
        scene->addEllipse(r4x, r4y, 4, 4, penYellow);
    }// r4
    if (l4>0)
    {
        switch (l4)
        {
        case 5:  l4y = 714; break;
        case 10: l4y = 685; break;
        case 15: l4y = 662; break;
        case 20: l4y = 639; break;
        case 25: l4y = 616; break;
        case 30: l4y = 593; break;
        case 35: l4y = 570; break;
        case 40: l4y = 550; break;
        case 45: l4y = 530; break;
        case 50: l4y = 513; break;
        case 55: l4y = 493; break;
        case 60: l4y = 476; break;
        case 65: l4y = 456; break;
        case 70: l4y = 439; break;
        case 75: l4y = 424; break;
        case 80: l4y = 407; break;
        case 85: l4y = 393; break;
        case 90: l4y = 379; break;
        case 95: l4y = 364; break;
        case 100: l4y = 350; break;
        case 105: l4y = 335; break;
        case 110: l4y = 321; break;
        case 115: l4y = 310; break;
        case 120: l4y = 298; break;
        case 125: l4y = 287; break;
        case 130: l4y = 275; break;
        case 135: l4y = 264; break;
        case 140: l4y = 252; break;
        case 145: l4y = 241; break;
        case 150: l4y = 229; break;
        case 155: l4y = 219; break;
        case 160: l4y = 209; break;
        case 165: l4y = 201; break;
        case 170: l4y = 192; break;
        }
        scene->addEllipse(l4x, l4y, 4, 4, penYellow);
    }
    if (r4 > 0 && l4 > 0)
    {
        if (r4 == l4)
        {
            scene->addLine(r4x,r4y,l4x,l4y, penGreenLine);
            scene->addEllipse(l4x, l4y, 4, 4, penGreen);
            scene->addEllipse(r4x, r4y, 4, 4, penGreen);
        }
        if (r4 > l4)
        {
            scene->addLine(r4x,r4y,l4x,l4y, penRedLine);
            scene->addEllipse(l4x, l4y, 4, 4, penRed);
            scene->addEllipse(r4x, r4y, 4, 4, penRed);
        }
        if (r4 < l4)
        {
            scene->addLine(r4x,r4y,l4x,l4y, penBlueLine);
            scene->addEllipse(l4x, l4y, 4, 4, penBlue);
            scene->addEllipse(r4x, r4y, 4, 4, penBlue);
        }
    }
}

void MainWindow::r5l5() //TR
{
    if (r5 > 0)
    {
        switch (r5)
        {
            case 5:  r5y = 722; break;
            case 10: r5y = 694; break;
            case 15: r5y = 671; break;
            case 20: r5y = 651; break;
            case 25: r5y = 634; break;
            case 30: r5y = 614; break;
            case 35: r5y = 593; break;
            case 40: r5y = 576; break;
            case 45: r5y = 556; break;
            case 50: r5y = 539; break;
            case 55: r5y = 522; break;
            case 60: r5y = 505; break;
            case 65: r5y = 487; break;
            case 70: r5y = 473; break;
            case 75: r5y = 459; break;
            case 80: r5y = 442; break;
            case 85: r5y = 427; break;
            case 90: r5y = 416; break;
            case 95: r5y = 401; break;
            case 100: r5y = 387; break;
            case 105: r5y = 376; break;
            case 110: r5y = 361; break;
            case 115: r5y = 352; break;
            case 120: r5y = 341; break;
            case 125: r5y = 330; break;
            case 130: r5y = 318; break;
            case 135: r5y = 307; break;
            case 140: r5y = 296; break;
            case 145: r5y = 284; break;
            case 150: r5y = 272; break;
            case 155: r5y = 264; break;
            case 160: r5y = 255; break;
            case 165: r5y = 246; break;
            case 170: r5y = 235; break;
            case 175: r5y = 227; break;
            case 180: r5y = 218; break;
            case 185: r5y = 211; break;
            case 190: r5y = 204; break;
            case 195: r5y = 198; break;
            case 200: r5y = 192; break;
        }
        scene->addEllipse(r5x, r5y, 4, 4, penYellow);
    }// r5
    if (l5>0)
    {
        switch (l5)
        {
        case 5:  l5y = 722; break;
        case 10: l5y = 694; break;
        case 15: l5y = 671; break;
        case 20: l5y = 651; break;
        case 25: l5y = 634; break;
        case 30: l5y = 614; break;
        case 35: l5y = 593; break;
        case 40: l5y = 576; break;
        case 45: l5y = 556; break;
        case 50: l5y = 539; break;
        case 55: l5y = 522; break;
        case 60: l5y = 505; break;
        case 65: l5y = 487; break;
        case 70: l5y = 473; break;
        case 75: l5y = 459; break;
        case 80: l5y = 442; break;
        case 85: l5y = 427; break;
        case 90: l5y = 416; break;
        case 95: l5y = 401; break;
        case 100: l5y = 387; break;
        case 105: l5y = 376; break;
        case 110: l5y = 361; break;
        case 115: l5y = 352; break;
        case 120: l5y = 341; break;
        case 125: l5y = 330; break;
        case 130: l5y = 318; break;
        case 135: l5y = 307; break;
        case 140: l5y = 296; break;
        case 145: l5y = 284; break;
        case 150: l5y = 272; break;
        case 155: l5y = 264; break;
        case 160: l5y = 255; break;
        case 165: l5y = 246; break;
        case 170: l5y = 235; break;
        case 175: l5y = 227; break;
        case 180: l5y = 218; break;
        case 185: l5y = 211; break;
        case 190: l5y = 204; break;
        case 195: l5y = 198; break;
        case 200: l5y = 192; break;
        }
        scene->addEllipse(l5x, l5y, 4, 4, penYellow);
    }
    if (r5 > 0 && l5 > 0)
    {
        if (r5 == l5)
        {
            scene->addLine(r5x,r5y,l5x,l5y, penGreenLine);
            scene->addEllipse(l5x, l5y, 4, 4, penGreen);
            scene->addEllipse(r5x, r5y, 4, 4, penGreen);
        }
        if (r5 > l5)
        {
            scene->addLine(r5x,r5y,l5x,l5y, penRedLine);
            scene->addEllipse(l5x, l5y, 4, 4, penRed);
            scene->addEllipse(r5x, r5y, 4, 4, penRed);
        }
        if (r5 < l5)
        {
            scene->addLine(r5x,r5y,l5x,l5y, penBlueLine);
            scene->addEllipse(l5x, l5y, 4, 4, penBlue);
            scene->addEllipse(r5x, r5y, 4, 4, penBlue);
        }
    }
}

void MainWindow::r6l6() //GI
{
    if (r6 > 0)
    {
        switch (r6)
        {
        case 5:  r6y = 722; break;
        case 10: r6y = 694; break;
        case 15: r6y = 671; break;
        case 20: r6y = 651; break;
        case 25: r6y = 634; break;
        case 30: r6y = 614; break;
        case 35: r6y = 593; break;
        case 40: r6y = 576; break;
        case 45: r6y = 556; break;
        case 50: r6y = 539; break;
        case 55: r6y = 522; break;
        case 60: r6y = 505; break;
        case 65: r6y = 487; break;
        case 70: r6y = 473; break;
        case 75: r6y = 459; break;
        case 80: r6y = 442; break;
        case 85: r6y = 427; break;
        case 90: r6y = 416; break;
        case 95: r6y = 401; break;
        case 100: r6y = 387; break;
        case 105: r6y = 376; break;
        case 110: r6y = 361; break;
        case 115: r6y = 352; break;
        case 120: r6y = 341; break;
        case 125: r6y = 330; break;
        case 130: r6y = 318; break;
        case 135: r6y = 307; break;
        case 140: r6y = 296; break;
        case 145: r6y = 284; break;
        case 150: r6y = 272; break;
        case 155: r6y = 264; break;
        case 160: r6y = 255; break;
        case 165: r6y = 246; break;
        case 170: r6y = 235; break;
        case 175: r6y = 227; break;
        case 180: r6y = 218; break;
        case 185: r6y = 211; break;
        case 190: r6y = 204; break;
        case 195: r6y = 198; break;
        case 200: r6y = 192; break;
        }
        scene->addEllipse(r6x, r6y, 4, 4, penYellow);
    }// r6
    if (l6>0)
    {
        switch (l6)
        {
        case 5:  l6y = 722; break;
        case 10: l6y = 694; break;
        case 15: l6y = 671; break;
        case 20: l6y = 651; break;
        case 25: l6y = 634; break;
        case 30: l6y = 614; break;
        case 35: l6y = 593; break;
        case 40: l6y = 576; break;
        case 45: l6y = 556; break;
        case 50: l6y = 539; break;
        case 55: l6y = 522; break;
        case 60: l6y = 505; break;
        case 65: l6y = 487; break;
        case 70: l6y = 473; break;
        case 75: l6y = 459; break;
        case 80: l6y = 442; break;
        case 85: l6y = 427; break;
        case 90: l6y = 416; break;
        case 95: l6y = 401; break;
        case 100: l6y = 387; break;
        case 105: l6y = 376; break;
        case 110: l6y = 361; break;
        case 115: l6y = 352; break;
        case 120: l6y = 341; break;
        case 125: l6y = 330; break;
        case 130: l6y = 318; break;
        case 135: l6y = 307; break;
        case 140: l6y = 296; break;
        case 145: l6y = 284; break;
        case 150: l6y = 272; break;
        case 155: l6y = 264; break;
        case 160: l6y = 255; break;
        case 165: l6y = 246; break;
        case 170: l6y = 235; break;
        case 175: l6y = 227; break;
        case 180: l6y = 218; break;
        case 185: l6y = 211; break;
        case 190: l6y = 204; break;
        case 195: l6y = 198; break;
        case 200: l6y = 192; break;
        }
        scene->addEllipse(l6x, l6y, 4, 4, penYellow);
    }
    if (r6 > 0 && l6 > 0)
    {
        if (r6 == l6)
        {
            scene->addLine(r6x,r6y,l6x,l6y, penGreenLine);
            scene->addEllipse(l6x, l6y, 4, 4, penGreen);
            scene->addEllipse(r6x, r6y, 4, 4, penGreen);
        }
        if (r6 > l6)
        {
            scene->addLine(r6x,r6y,l6x,l6y, penRedLine);
            scene->addEllipse(l6x, l6y, 4, 4, penRed);
            scene->addEllipse(r6x, r6y, 4, 4, penRed);
        }
        if (r6 < l6)
        {
            scene->addLine(r6x,r6y,l6x,l6y, penBlueLine);
            scene->addEllipse(l6x, l6y, 4, 4, penBlue);
            scene->addEllipse(r6x, r6y, 4, 4, penBlue);
        }
    }
}

void MainWindow::r7l7() //RP
{
    if (r7 > 0)
    {
        switch (r7)
        {
            case 5:  r7y = 710; break;
            case 10: r7y = 682; break;
            case 15: r7y = 659; break;
            case 20: r7y = 633; break;
            case 25: r7y = 607; break;
            case 30: r7y = 584; break;
            case 35: r7y = 561; break;
            case 40: r7y = 541; break;
            case 45: r7y = 518; break;
            case 50: r7y = 498; break;
            case 55: r7y = 481; break;
            case 60: r7y = 461; break;
            case 65: r7y = 441; break;
            case 70: r7y = 424; break;
            case 75: r7y = 410; break;
            case 80: r7y = 389; break;
            case 85: r7y = 375; break;
            case 90: r7y = 361; break;
            case 95: r7y = 347; break;
            case 100: r7y = 332; break;
            case 105: r7y = 318; break;
            case 110: r7y = 304; break;
            case 115: r7y = 292; break;
            case 120: r7y = 278; break;
            case 125: r7y = 266; break;
            case 130: r7y = 252; break;
            case 135: r7y = 241; break;
            case 140: r7y = 229; break;
            case 145: r7y = 218; break;
            case 150: r7y = 206; break;
            case 155: r7y = 197; break;
            case 160: r7y = 189; break;
        }
        scene->addEllipse(r7x, r7y, 4, 4, penYellow);
    }// r7
    if (l7>0)
    {
        switch (l7)
        {
        case 5:  l7y = 710; break;
        case 10: l7y = 682; break;
        case 15: l7y = 659; break;
        case 20: l7y = 633; break;
        case 25: l7y = 607; break;
        case 30: l7y = 584; break;
        case 35: l7y = 561; break;
        case 40: l7y = 541; break;
        case 45: l7y = 518; break;
        case 50: l7y = 498; break;
        case 55: l7y = 481; break;
        case 60: l7y = 461; break;
        case 65: l7y = 441; break;
        case 70: l7y = 424; break;
        case 75: l7y = 410; break;
        case 80: l7y = 389; break;
        case 85: l7y = 375; break;
        case 90: l7y = 361; break;
        case 95: l7y = 347; break;
        case 100: l7y = 332; break;
        case 105: l7y = 318; break;
        case 110: l7y = 304; break;
        case 115: l7y = 292; break;
        case 120: l7y = 278; break;
        case 125: l7y = 266; break;
        case 130: l7y = 252; break;
        case 135: l7y = 241; break;
        case 140: l7y = 229; break;
        case 145: l7y = 218; break;
        case 150: l7y = 206; break;
        case 155: l7y = 197; break;
        case 160: l7y = 189; break;
        }
        scene->addEllipse(l7x, l7y, 4, 4, penYellow);
    }
    if (r7 > 0 && l7 > 0)
    {
        if (r7 == l7)
        {
            scene->addLine(r7x,r7y,l7x,l7y, penGreenLine);
            scene->addEllipse(l7x, l7y, 4, 4, penGreen);
            scene->addEllipse(r7x, r7y, 4, 4, penGreen);
        }
        if (r7 > l7)
        {
            scene->addLine(r7x,r7y,l7x,l7y, penRedLine);
            scene->addEllipse(l7x, l7y, 4, 4, penRed);
            scene->addEllipse(r7x, r7y, 4, 4, penRed);
        }
        if (r7 < l7)
        {
            scene->addLine(r7x,r7y,l7x,l7y, penBlueLine);
            scene->addEllipse(l7x, l7y, 4, 4, penBlue);
            scene->addEllipse(r7x, r7y, 4, 4, penBlue);
        }
    }
}

void MainWindow::r8l8() //F
{
    if (r8 > 0)
    {
        switch (r8)
        {
            case 5:  r8y = 708; break;
            case 10: r8y = 673; break;
            case 15: r8y = 639; break;
            case 20: r8y = 607; break;
            case 25: r8y = 579; break;
            case 30: r8y = 553; break;
            case 35: r8y = 524; break;
            case 40: r8y = 496; break;
            case 45: r8y = 473; break;
            case 50: r8y = 447; break;
            case 55: r8y = 427; break;
            case 60: r8y = 407; break;
            case 65: r8y = 387; break;
            case 70: r8y = 367; break;
            case 75: r8y = 347; break;
            case 80: r8y = 326; break;
            case 85: r8y = 309; break;
            case 90: r8y = 295; break;
            case 95: r8y = 278; break;
            case 100: r8y = 263; break;
            case 105: r8y = 246; break;
            case 110: r8y = 232; break;
            case 115: r8y = 218; break;
            case 120: r8y = 206; break;
            case 125: r8y = 198; break;
            case 130: r8y = 189; break;
        }
        scene->addEllipse(r8x, r8y, 4, 4, penYellow);
    }// r8
    if (l8>0)
    {
        switch (l8)
        {
        case 5:  l8y = 708; break;
        case 10: l8y = 673; break;
        case 15: l8y = 639; break;
        case 20: l8y = 607; break;
        case 25: l8y = 579; break;
        case 30: l8y = 553; break;
        case 35: l8y = 524; break;
        case 40: l8y = 496; break;
        case 45: l8y = 473; break;
        case 50: l8y = 447; break;
        case 55: l8y = 427; break;
        case 60: l8y = 407; break;
        case 65: l8y = 387; break;
        case 70: l8y = 367; break;
        case 75: l8y = 347; break;
        case 80: l8y = 326; break;
        case 85: l8y = 309; break;
        case 90: l8y = 295; break;
        case 95: l8y = 278; break;
        case 100: l8y = 263; break;
        case 105: l8y = 246; break;
        case 110: l8y = 232; break;
        case 115: l8y = 218; break;
        case 120: l8y = 206; break;
        case 125: l8y = 198; break;
        case 130: l8y = 189; break;
        }
        scene->addEllipse(l8x, l8y, 4, 4, penYellow);
    }
    if (r8 > 0 && l8 > 0)
    {
        if (r8 == l8)
        {
            scene->addLine(r8x,r8y,l8x,l8y, penGreenLine);
            scene->addEllipse(l8x, l8y, 4, 4, penGreen);
            scene->addEllipse(r8x, r8y, 4, 4, penGreen);
        }
        if (r8 > l8)
        {
            scene->addLine(r8x,r8y,l8x,l8y, penRedLine);
            scene->addEllipse(l8x, l8y, 4, 4, penRed);
            scene->addEllipse(r8x, r8y, 4, 4, penRed);
        }
        if (r8 < l8)
        {
            scene->addLine(r8x,r8y,l8x,l8y, penBlueLine);
            scene->addEllipse(l8x, l8y, 4, 4, penBlue);
            scene->addEllipse(r8x, r8y, 4, 4, penBlue);
        }
    }
}

void MainWindow::r9l9() //R
{
    if (r9 > 0)
    {
        switch (r9)
        {
        case 5:  r9y = 710; break;
        case 10: r9y = 682; break;
        case 15: r9y = 659; break;
        case 20: r9y = 633; break;
        case 25: r9y = 607; break;
        case 30: r9y = 584; break;
        case 35: r9y = 561; break;
        case 40: r9y = 541; break;
        case 45: r9y = 518; break;
        case 50: r9y = 498; break;
        case 55: r9y = 481; break;
        case 60: r9y = 461; break;
        case 65: r9y = 441; break;
        case 70: r9y = 424; break;
        case 75: r9y = 410; break;
        case 80: r9y = 389; break;
        case 85: r9y = 375; break;
        case 90: r9y = 361; break;
        case 95: r9y = 347; break;
        case 100: r9y = 332; break;
        case 105: r9y = 318; break;
        case 110: r9y = 304; break;
        case 115: r9y = 292; break;
        case 120: r9y = 278; break;
        case 125: r9y = 266; break;
        case 130: r9y = 252; break;
        case 135: r9y = 241; break;
        case 140: r9y = 229; break;
        case 145: r9y = 218; break;
        case 150: r9y = 206; break;
        case 155: r9y = 197; break;
        case 160: r9y = 189; break;
        }
        scene->addEllipse(r9x, r9y, 4, 4, penYellow);
    }// r9
    if (l9>0)
    {
        switch (l9)
        {
        case 5:  l9y = 710; break;
        case 10: l9y = 682; break;
        case 15: l9y = 659; break;
        case 20: l9y = 633; break;
        case 25: l9y = 607; break;
        case 30: l9y = 584; break;
        case 35: l9y = 561; break;
        case 40: l9y = 541; break;
        case 45: l9y = 518; break;
        case 50: l9y = 498; break;
        case 55: l9y = 481; break;
        case 60: l9y = 461; break;
        case 65: l9y = 441; break;
        case 70: l9y = 424; break;
        case 75: l9y = 410; break;
        case 80: l9y = 389; break;
        case 85: l9y = 375; break;
        case 90: l9y = 361; break;
        case 95: l9y = 347; break;
        case 100: l9y = 332; break;
        case 105: l9y = 318; break;
        case 110: l9y = 304; break;
        case 115: l9y = 292; break;
        case 120: l9y = 278; break;
        case 125: l9y = 266; break;
        case 130: l9y = 252; break;
        case 135: l9y = 241; break;
        case 140: l9y = 229; break;
        case 145: l9y = 218; break;
        case 150: l9y = 206; break;
        case 155: l9y = 197; break;
        case 160: l9y = 189; break;
        }
        scene->addEllipse(l9x, l9y, 4, 4, penYellow);
    }
    if (r9 > 0 && l9 > 0)
    {
        if (r9 == l9)
        {
            scene->addLine(r9x,r9y,l9x,l9y, penGreenLine);
            scene->addEllipse(l9x, l9y, 4, 4, penGreen);
            scene->addEllipse(r9x, r9y, 4, 4, penGreen);
        }
        if (r9 > l9)
        {
            scene->addLine(r9x,r9y,l9x,l9y, penRedLine);
            scene->addEllipse(l9x, l9y, 4, 4, penRed);
            scene->addEllipse(r9x, r9y, 4, 4, penRed);
        }
        if (r9 < l9)
        {
            scene->addLine(r9x,r9y,l9x,l9y, penBlueLine);
            scene->addEllipse(l9x, l9y, 4, 4, penBlue);
            scene->addEllipse(r9x, r9y, 4, 4, penBlue);
        }
    }
}

void MainWindow::r10l10() //V
{
    if (r10 > 0)
    {
        switch (r10)
        {
            case 5:  r10y = 707; break;
            case 10: r10y = 679; break;
            case 15: r10y = 650; break;
            case 20: r10y = 624; break;
            case 25: r10y = 602; break;
            case 30: r10y = 576; break;
            case 35: r10y = 553; break;
            case 40: r10y = 527; break;
            case 45: r10y = 504; break;
            case 50: r10y = 481; break;
            case 55: r10y = 461; break;
            case 60: r10y = 441; break;
            case 65: r10y = 424; break;
            case 70: r10y = 407; break;
            case 75: r10y = 387; break;
            case 80: r10y = 370; break;
            case 85: r10y = 355; break;
            case 90: r10y = 338; break;
            case 95: r10y = 321; break;
            case 100: r10y = 306; break;
            case 105: r10y = 292; break;
            case 110: r10y = 281; break;
            case 115: r10y = 266; break;
            case 120: r10y = 252; break;
            case 125: r10y = 241; break;
            case 130: r10y = 229; break;
            case 135: r10y = 218; break;
            case 140: r10y = 206; break;
            case 145: r10y = 197; break;
            case 150: r10y = 186; break;
        }
        scene->addEllipse(r10x, r10y, 4, 4, penYellow);
    }// r10
    if (l10>0)
    {
        switch (l10)
        {
        case 5:  l10y = 707; break;
        case 10: l10y = 679; break;
        case 15: l10y = 650; break;
        case 20: l10y = 624; break;
        case 25: l10y = 602; break;
        case 30: l10y = 576; break;
        case 35: l10y = 553; break;
        case 40: l10y = 527; break;
        case 45: l10y = 504; break;
        case 50: l10y = 481; break;
        case 55: l10y = 461; break;
        case 60: l10y = 441; break;
        case 65: l10y = 424; break;
        case 70: l10y = 407; break;
        case 75: l10y = 387; break;
        case 80: l10y = 370; break;
        case 85: l10y = 355; break;
        case 90: l10y = 338; break;
        case 95: l10y = 321; break;
        case 100: l10y = 306; break;
        case 105: l10y = 292; break;
        case 110: l10y = 281; break;
        case 115: l10y = 266; break;
        case 120: l10y = 252; break;
        case 125: l10y = 241; break;
        case 130: l10y = 229; break;
        case 135: l10y = 218; break;
        case 140: l10y = 206; break;
        case 145: l10y = 197; break;
        case 150: l10y = 186; break;
        }
        scene->addEllipse(l10x, l10y, 4, 4, penYellow);
    }
    if (r10 > 0 && l10 > 0)
    {
        if (r10 == l10)
        {
            scene->addLine(r10x,r10y,l10x,l10y, penGreenLine);
            scene->addEllipse(l10x, l10y, 4, 4, penGreen);
            scene->addEllipse(r10x, r10y, 4, 4, penGreen);
        }
        if (r10 > l10)
        {
            scene->addLine(r10x,r10y,l10x,l10y, penRedLine);
            scene->addEllipse(l10x, l10y, 4, 4, penRed);
            scene->addEllipse(r10x, r10y, 4, 4, penRed);
        }
        if (r10 < l10)
        {
            scene->addLine(r10x,r10y,l10x,l10y, penBlueLine);
            scene->addEllipse(l10x, l10y, 4, 4, penBlue);
            scene->addEllipse(r10x, r10y, 4, 4, penBlue);
        }
    }
}

void MainWindow::r11l11() //VB
{
    if (r11 > 0)
    {
        switch (r11)
        {
        case 5:  r11y = 708; break;
        case 10: r11y = 673; break;
        case 15: r11y = 639; break;
        case 20: r11y = 607; break;
        case 25: r11y = 579; break;
        case 30: r11y = 553; break;
        case 35: r11y = 524; break;
        case 40: r11y = 496; break;
        case 45: r11y = 473; break;
        case 50: r11y = 447; break;
        case 55: r11y = 427; break;
        case 60: r11y = 407; break;
        case 65: r11y = 387; break;
        case 70: r11y = 367; break;
        case 75: r11y = 347; break;
        case 80: r11y = 326; break;
        case 85: r11y = 309; break;
        case 90: r11y = 295; break;
        case 95: r11y = 278; break;
        case 100: r11y = 263; break;
        case 105: r11y = 246; break;
        case 110: r11y = 232; break;
        case 115: r11y = 218; break;
        case 120: r11y = 206; break;
        case 125: r11y = 198; break;
        case 130: r11y = 189; break;
        }
        scene->addEllipse(r11x, r11y, 4, 4, penYellow);
    }// r11
    if (l11>0)
    {
        switch (l11)
        {
        case 5:  l11y = 708; break;
        case 10: l11y = 673; break;
        case 15: l11y = 639; break;
        case 20: l11y = 607; break;
        case 25: l11y = 579; break;
        case 30: l11y = 553; break;
        case 35: l11y = 524; break;
        case 40: l11y = 496; break;
        case 45: l11y = 473; break;
        case 50: l11y = 447; break;
        case 55: l11y = 427; break;
        case 60: l11y = 407; break;
        case 65: l11y = 387; break;
        case 70: l11y = 367; break;
        case 75: l11y = 347; break;
        case 80: l11y = 326; break;
        case 85: l11y = 309; break;
        case 90: l11y = 295; break;
        case 95: l11y = 278; break;
        case 100: l11y = 263; break;
        case 105: l11y = 246; break;
        case 110: l11y = 232; break;
        case 115: l11y = 218; break;
        case 120: l11y = 206; break;
        case 125: l11y = 198; break;
        case 130: l11y = 189; break;
        }
        scene->addEllipse(l11x, l11y, 4, 4, penYellow);
    }
    if (r11 > 0 && l11 > 0)
    {
        if (r11 == l11)
        {
            scene->addLine(r11x,r11y,l11x,l11y, penGreenLine);
            scene->addEllipse(l11x, l11y, 4, 4, penGreen);
            scene->addEllipse(r11x, r11y, 4, 4, penGreen);
        }
        if (r11 > l11)
        {
            scene->addLine(r11x,r11y,l11x,l11y, penRedLine);
            scene->addEllipse(l11x, l11y, 4, 4, penRed);
            scene->addEllipse(r11x, r11y, 4, 4, penRed);
        }
        if (r11 < l11)
        {
            scene->addLine(r11x,r11y,l11x,l11y, penBlueLine);
            scene->addEllipse(l11x, l11y, 4, 4, penBlue);
            scene->addEllipse(r11x, r11y, 4, 4, penBlue);
        }
    }
}

void MainWindow::r12l12()
{
    if (r12 > 0)
    {
        switch (r12)
        {
        case 5:  r12y = 708; break;
        case 10: r12y = 679; break;
        case 15: r12y = 651; break;
        case 20: r12y = 625; break;
        case 25: r12y = 599; break;
        case 30: r12y = 571; break;
        case 35: r12y = 548; break;
        case 40: r12y = 525; break;
        case 45: r12y = 499; break;
        case 50: r12y = 476; break;
        case 55: r12y = 456; break;
        case 60: r12y = 436; break;
        case 65: r12y = 419; break;
        case 70: r12y = 398; break;
        case 75: r12y = 379; break;
        case 80: r12y = 361; break;
        case 85: r12y = 347; break;
        case 90: r12y = 333; break;
        case 95: r12y = 316; break;
        case 100: r12y = 301; break;
        case 105: r12y = 287; break;
        case 110: r12y = 273; break;
        case 115: r12y = 258; break;
        case 120: r12y = 244; break;
        case 125: r12y = 232; break;
        case 130: r12y = 221; break;
        case 135: r12y = 210; break;
        case 140: r12y = 198; break;
        }
        scene->addEllipse(r12x, r12y, 4, 4, penYellow);
    }// r12
    if (l12>0)
    {
        switch (l12)
        {
        case 5:  l12y = 708; break;
        case 10: l12y = 679; break;
        case 15: l12y = 651; break;
        case 20: l12y = 625; break;
        case 25: l12y = 599; break;
        case 30: l12y = 571; break;
        case 35: l12y = 548; break;
        case 40: l12y = 525; break;
        case 45: l12y = 499; break;
        case 50: l12y = 476; break;
        case 55: l12y = 456; break;
        case 60: l12y = 436; break;
        case 65: l12y = 419; break;
        case 70: l12y = 398; break;
        case 75: l12y = 379; break;
        case 80: l12y = 361; break;
        case 85: l12y = 347; break;
        case 90: l12y = 333; break;
        case 95: l12y = 316; break;
        case 100: l12y = 301; break;
        case 105: l12y = 287; break;
        case 110: l12y = 273; break;
        case 115: l12y = 258; break;
        case 120: l12y = 244; break;
        case 125: l12y = 232; break;
        case 130: l12y = 221; break;
        case 135: l12y = 210; break;
        case 140: l12y = 198; break;
        }
        scene->addEllipse(l12x, l12y, 4, 4, penYellow);
    }
    if (r12 > 0 && l12 > 0)
    {
        if (r12 == l12)
        {
            scene->addLine(r12x,r12y,l12x,l12y, penGreenLine);
            scene->addEllipse(l12x, l12y, 4, 4, penGreen);
            scene->addEllipse(r12x, r12y, 4, 4, penGreen);
        }
        if (r12 > l12)
        {
            scene->addLine(r12x,r12y,l12x,l12y, penRedLine);
            scene->addEllipse(l12x, l12y, 4, 4, penRed);
            scene->addEllipse(r12x, r12y, 4, 4, penRed);
        }
        if (r12 < l12)
        {
            scene->addLine(r12x,r12y,l12x,l12y, penBlueLine);
            scene->addEllipse(l12x, l12y, 4, 4, penBlue);
            scene->addEllipse(r12x, r12y, 4, 4, penBlue);
        }
    }
}










