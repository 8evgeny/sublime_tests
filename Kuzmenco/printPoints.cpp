#include "mainwindow.h"
#include <QGraphicsScene>
#include <QPainter>

extern QPen penRed;
extern QPen penGreen;
extern QPen penBlue;
extern QPen penYellow;
extern QPen penRedLine;
extern QPen penGreenLine;
extern QPen penBlueLine;
extern QGraphicsScene * scene;

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
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    if (r1 > 0 && l1 > 0)
    {
        QPainter p(this);
        p.setPen(Qt::red);
        QFont font = p.font();
        font.setPixelSize(25);
        p.setFont(font);
        p.drawText(r1x,20,"A0");
    }





}

void MainWindow::r1l1()
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
    QWidget::repaint();
}

void MainWindow::r2l2()
{
scene->addEllipse(r2x, r2, 4, 4, penRed);
scene->addEllipse(l2x, l2, 4, 4, penRed);
    if (r2 > 0)
    {
        switch (r2)
        {
            case 5:  r2y = 000; break;
            case 10: r2y = 000; break;
            case 15: r2y = 000; break;
            case 20: r2y = 000; break;
            case 25: r2y = 000; break;
            case 30: r2y = 000; break;
            case 35: r2y = 000; break;
            case 40: r2y = 000; break;
            case 45: r2y = 000; break;
            case 50: r2y = 000; break;
            case 55: r2y = 000; break;
            case 60: r2y = 000; break;
            case 65: r2y = 000; break;
            case 70: r2y = 000; break;
            case 75: r2y = 000; break;
            case 80: r2y = 000; break;
            case 85: r2y = 000; break;
            case 90: r2y = 000; break;
            case 95: r2y = 000; break;
            case 100: r2y = 000; break;
            case 105: r2y = 000; break;
            case 110: r2y = 000; break;
            case 115: r2y = 000; break;
            case 120: r2y = 000; break;
            case 125: r2y = 000; break;
            case 130: r2y = 000; break;
            case 135: r2y = 000; break;
            case 140: r2y = 000; break;
            case 145: r2y = 000; break;
            case 150: r2y = 000; break;
            case 155: r2y = 000; break;
            case 160: r2y = 000; break;
            case 165: r2y = 000; break;
            case 170: r2y = 000; break;
            case 175: r2y = 000; break;
            case 180: r2y = 000; break;
            case 185: r2y = 000; break;
            case 190: r2y = 000; break;
        }
        scene->addEllipse(r2x, r2y, 4, 4, penYellow);
    }// r2
    if (l2>0)
    {
        switch (l2)
        {
            case 5:  l2y = 000; break;
            case 10: l2y = 000; break;
            case 15: l2y = 000; break;
            case 20: l2y = 000; break;
            case 25: l2y = 000; break;
            case 30: l2y = 000; break;
            case 35: l2y = 000; break;
            case 40: l2y = 000; break;
            case 45: l2y = 000; break;
            case 50: l2y = 000; break;
            case 55: l2y = 000; break;
            case 60: l2y = 000; break;
            case 65: l2y = 000; break;
            case 70: l2y = 000; break;
            case 75: l2y = 000; break;
            case 80: l2y = 000; break;
            case 85: l2y = 000; break;
            case 90: l2y = 000; break;
            case 95: l2y = 000; break;
            case 100: l2y = 000; break;
            case 105: l2y = 000; break;
            case 110: l2y = 000; break;
            case 115: l2y = 000; break;
            case 120: l2y = 000; break;
            case 125: l2y = 000; break;
            case 130: l2y = 000; break;
            case 135: l2y = 000; break;
            case 140: l2y = 000; break;
            case 145: l2y = 000; break;
            case 150: l2y = 000; break;
            case 155: l2y = 000; break;
            case 160: l2y = 000; break;
            case 165: l2y = 000; break;
            case 170: l2y = 000; break;
            case 175: l2y = 000; break;
            case 180: l2y = 000; break;
            case 185: l2y = 000; break;
            case 190: l2y = 000; break;
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

void MainWindow::r3l3()
{
scene->addEllipse(r3x, r3, 4, 4, penRed);
scene->addEllipse(l3x, l3, 4, 4, penRed);
    if (r3 > 0)
    {
        switch (r3)
        {
            case 5:  r3y = 000; break;
            case 10: r3y = 000; break;
            case 15: r3y = 000; break;
            case 20: r3y = 000; break;
            case 25: r3y = 000; break;
            case 30: r3y = 000; break;
            case 35: r3y = 000; break;
            case 40: r3y = 000; break;
            case 45: r3y = 000; break;
            case 50: r3y = 000; break;
            case 55: r3y = 000; break;
            case 60: r3y = 000; break;
            case 65: r3y = 000; break;
            case 70: r3y = 000; break;
            case 75: r3y = 000; break;
            case 80: r3y = 000; break;
            case 85: r3y = 000; break;
            case 90: r3y = 000; break;
            case 95: r3y = 000; break;
            case 100: r3y = 000; break;
            case 105: r3y = 000; break;
            case 110: r3y = 000; break;
            case 115: r3y = 000; break;
            case 120: r3y = 000; break;
            case 125: r3y = 000; break;
            case 130: r3y = 000; break;
            case 135: r3y = 000; break;
            case 140: r3y = 000; break;
            case 145: r3y = 000; break;
            case 150: r3y = 000; break;
            case 155: r3y = 000; break;
            case 160: r3y = 000; break;
            case 165: r3y = 000; break;
            case 170: r3y = 000; break;
            case 175: r3y = 000; break;
            case 180: r3y = 000; break;
            case 185: r3y = 000; break;
            case 190: r3y = 000; break;
        }
        scene->addEllipse(r3x, r3y, 4, 4, penYellow);
    }// r3
    if (l3>0)
    {
        switch (l3)
        {
            case 5:  l3y = 000; break;
            case 10: l3y = 000; break;
            case 15: l3y = 000; break;
            case 20: l3y = 000; break;
            case 25: l3y = 000; break;
            case 30: l3y = 000; break;
            case 35: l3y = 000; break;
            case 40: l3y = 000; break;
            case 45: l3y = 000; break;
            case 50: l3y = 000; break;
            case 55: l3y = 000; break;
            case 60: l3y = 000; break;
            case 65: l3y = 000; break;
            case 70: l3y = 000; break;
            case 75: l3y = 000; break;
            case 80: l3y = 000; break;
            case 85: l3y = 000; break;
            case 90: l3y = 000; break;
            case 95: l3y = 000; break;
            case 100: l3y = 000; break;
            case 105: l3y = 000; break;
            case 110: l3y = 000; break;
            case 115: l3y = 000; break;
            case 120: l3y = 000; break;
            case 125: l3y = 000; break;
            case 130: l3y = 000; break;
            case 135: l3y = 000; break;
            case 140: l3y = 000; break;
            case 145: l3y = 000; break;
            case 150: l3y = 000; break;
            case 155: l3y = 000; break;
            case 160: l3y = 000; break;
            case 165: l3y = 000; break;
            case 170: l3y = 000; break;
            case 175: l3y = 000; break;
            case 180: l3y = 000; break;
            case 185: l3y = 000; break;
            case 190: l3y = 000; break;
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

void MainWindow::r4l4()
{
scene->addEllipse(r4x, r4, 4, 4, penRed);
scene->addEllipse(l4x, l4, 4, 4, penRed);
    if (r4 > 0)
    {
        switch (r4)
        {
            case 5:  r4y = 000; break;
            case 10: r4y = 000; break;
            case 15: r4y = 000; break;
            case 20: r4y = 000; break;
            case 25: r4y = 000; break;
            case 30: r4y = 000; break;
            case 35: r4y = 000; break;
            case 40: r4y = 000; break;
            case 45: r4y = 000; break;
            case 50: r4y = 000; break;
            case 55: r4y = 000; break;
            case 60: r4y = 000; break;
            case 65: r4y = 000; break;
            case 70: r4y = 000; break;
            case 75: r4y = 000; break;
            case 80: r4y = 000; break;
            case 85: r4y = 000; break;
            case 90: r4y = 000; break;
            case 95: r4y = 000; break;
            case 100: r4y = 000; break;
            case 105: r4y = 000; break;
            case 110: r4y = 000; break;
            case 115: r4y = 000; break;
            case 120: r4y = 000; break;
            case 125: r4y = 000; break;
            case 130: r4y = 000; break;
            case 135: r4y = 000; break;
            case 140: r4y = 000; break;
            case 145: r4y = 000; break;
            case 150: r4y = 000; break;
            case 155: r4y = 000; break;
            case 160: r4y = 000; break;
            case 165: r4y = 000; break;
            case 170: r4y = 000; break;
            case 175: r4y = 000; break;
            case 180: r4y = 000; break;
            case 185: r4y = 000; break;
            case 190: r4y = 000; break;
        }
        scene->addEllipse(r4x, r4y, 4, 4, penYellow);
    }// r4
    if (l4>0)
    {
        switch (l4)
        {
            case 5:  l4y = 000; break;
            case 10: l4y = 000; break;
            case 15: l4y = 000; break;
            case 20: l4y = 000; break;
            case 25: l4y = 000; break;
            case 30: l4y = 000; break;
            case 35: l4y = 000; break;
            case 40: l4y = 000; break;
            case 45: l4y = 000; break;
            case 50: l4y = 000; break;
            case 55: l4y = 000; break;
            case 60: l4y = 000; break;
            case 65: l4y = 000; break;
            case 70: l4y = 000; break;
            case 75: l4y = 000; break;
            case 80: l4y = 000; break;
            case 85: l4y = 000; break;
            case 90: l4y = 000; break;
            case 95: l4y = 000; break;
            case 100: l4y = 000; break;
            case 105: l4y = 000; break;
            case 110: l4y = 000; break;
            case 115: l4y = 000; break;
            case 120: l4y = 000; break;
            case 125: l4y = 000; break;
            case 130: l4y = 000; break;
            case 135: l4y = 000; break;
            case 140: l4y = 000; break;
            case 145: l4y = 000; break;
            case 150: l4y = 000; break;
            case 155: l4y = 000; break;
            case 160: l4y = 000; break;
            case 165: l4y = 000; break;
            case 170: l4y = 000; break;
            case 175: l4y = 000; break;
            case 180: l4y = 000; break;
            case 185: l4y = 000; break;
            case 190: l4y = 000; break;
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

void MainWindow::r5l5()
{
scene->addEllipse(r5x, r5, 4, 4, penRed);
scene->addEllipse(l5x, l5, 4, 4, penRed);
    if (r5 > 0)
    {
        switch (r5)
        {
            case 5:  r5y = 000; break;
            case 10: r5y = 000; break;
            case 15: r5y = 000; break;
            case 20: r5y = 000; break;
            case 25: r5y = 000; break;
            case 30: r5y = 000; break;
            case 35: r5y = 000; break;
            case 40: r5y = 000; break;
            case 45: r5y = 000; break;
            case 50: r5y = 000; break;
            case 55: r5y = 000; break;
            case 60: r5y = 000; break;
            case 65: r5y = 000; break;
            case 70: r5y = 000; break;
            case 75: r5y = 000; break;
            case 80: r5y = 000; break;
            case 85: r5y = 000; break;
            case 90: r5y = 000; break;
            case 95: r5y = 000; break;
            case 100: r5y = 000; break;
            case 105: r5y = 000; break;
            case 110: r5y = 000; break;
            case 115: r5y = 000; break;
            case 120: r5y = 000; break;
            case 125: r5y = 000; break;
            case 130: r5y = 000; break;
            case 135: r5y = 000; break;
            case 140: r5y = 000; break;
            case 145: r5y = 000; break;
            case 150: r5y = 000; break;
            case 155: r5y = 000; break;
            case 160: r5y = 000; break;
            case 165: r5y = 000; break;
            case 170: r5y = 000; break;
            case 175: r5y = 000; break;
            case 180: r5y = 000; break;
            case 185: r5y = 000; break;
            case 190: r5y = 000; break;
        }
        scene->addEllipse(r5x, r5y, 4, 4, penYellow);
    }// r5
    if (l5>0)
    {
        switch (l5)
        {
            case 5:  l5y = 000; break;
            case 10: l5y = 000; break;
            case 15: l5y = 000; break;
            case 20: l5y = 000; break;
            case 25: l5y = 000; break;
            case 30: l5y = 000; break;
            case 35: l5y = 000; break;
            case 40: l5y = 000; break;
            case 45: l5y = 000; break;
            case 50: l5y = 000; break;
            case 55: l5y = 000; break;
            case 60: l5y = 000; break;
            case 65: l5y = 000; break;
            case 70: l5y = 000; break;
            case 75: l5y = 000; break;
            case 80: l5y = 000; break;
            case 85: l5y = 000; break;
            case 90: l5y = 000; break;
            case 95: l5y = 000; break;
            case 100: l5y = 000; break;
            case 105: l5y = 000; break;
            case 110: l5y = 000; break;
            case 115: l5y = 000; break;
            case 120: l5y = 000; break;
            case 125: l5y = 000; break;
            case 130: l5y = 000; break;
            case 135: l5y = 000; break;
            case 140: l5y = 000; break;
            case 145: l5y = 000; break;
            case 150: l5y = 000; break;
            case 155: l5y = 000; break;
            case 160: l5y = 000; break;
            case 165: l5y = 000; break;
            case 170: l5y = 000; break;
            case 175: l5y = 000; break;
            case 180: l5y = 000; break;
            case 185: l5y = 000; break;
            case 190: l5y = 000; break;
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

void MainWindow::r6l6()
{
scene->addEllipse(r6x, r6, 4, 4, penRed);
scene->addEllipse(l6x, l6, 4, 4, penRed);
    if (r6 > 0)
    {
        switch (r6)
        {
            case 5:  r6y = 000; break;
            case 10: r6y = 000; break;
            case 15: r6y = 000; break;
            case 20: r6y = 000; break;
            case 25: r6y = 000; break;
            case 30: r6y = 000; break;
            case 35: r6y = 000; break;
            case 40: r6y = 000; break;
            case 45: r6y = 000; break;
            case 50: r6y = 000; break;
            case 55: r6y = 000; break;
            case 60: r6y = 000; break;
            case 65: r6y = 000; break;
            case 70: r6y = 000; break;
            case 75: r6y = 000; break;
            case 80: r6y = 000; break;
            case 85: r6y = 000; break;
            case 90: r6y = 000; break;
            case 95: r6y = 000; break;
            case 100: r6y = 000; break;
            case 105: r6y = 000; break;
            case 110: r6y = 000; break;
            case 115: r6y = 000; break;
            case 120: r6y = 000; break;
            case 125: r6y = 000; break;
            case 130: r6y = 000; break;
            case 135: r6y = 000; break;
            case 140: r6y = 000; break;
            case 145: r6y = 000; break;
            case 150: r6y = 000; break;
            case 155: r6y = 000; break;
            case 160: r6y = 000; break;
            case 165: r6y = 000; break;
            case 170: r6y = 000; break;
            case 175: r6y = 000; break;
            case 180: r6y = 000; break;
            case 185: r6y = 000; break;
            case 190: r6y = 000; break;
        }
        scene->addEllipse(r6x, r6y, 4, 4, penYellow);
    }// r6
    if (l6>0)
    {
        switch (l6)
        {
            case 5:  l6y = 000; break;
            case 10: l6y = 000; break;
            case 15: l6y = 000; break;
            case 20: l6y = 000; break;
            case 25: l6y = 000; break;
            case 30: l6y = 000; break;
            case 35: l6y = 000; break;
            case 40: l6y = 000; break;
            case 45: l6y = 000; break;
            case 50: l6y = 000; break;
            case 55: l6y = 000; break;
            case 60: l6y = 000; break;
            case 65: l6y = 000; break;
            case 70: l6y = 000; break;
            case 75: l6y = 000; break;
            case 80: l6y = 000; break;
            case 85: l6y = 000; break;
            case 90: l6y = 000; break;
            case 95: l6y = 000; break;
            case 100: l6y = 000; break;
            case 105: l6y = 000; break;
            case 110: l6y = 000; break;
            case 115: l6y = 000; break;
            case 120: l6y = 000; break;
            case 125: l6y = 000; break;
            case 130: l6y = 000; break;
            case 135: l6y = 000; break;
            case 140: l6y = 000; break;
            case 145: l6y = 000; break;
            case 150: l6y = 000; break;
            case 155: l6y = 000; break;
            case 160: l6y = 000; break;
            case 165: l6y = 000; break;
            case 170: l6y = 000; break;
            case 175: l6y = 000; break;
            case 180: l6y = 000; break;
            case 185: l6y = 000; break;
            case 190: l6y = 000; break;
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

void MainWindow::r7l7()
{
scene->addEllipse(r7x, r7, 4, 4, penRed);
scene->addEllipse(l7x, l7, 4, 4, penRed);
    if (r7 > 0)
    {
        switch (r7)
        {
            case 5:  r7y = 000; break;
            case 10: r7y = 000; break;
            case 15: r7y = 000; break;
            case 20: r7y = 000; break;
            case 25: r7y = 000; break;
            case 30: r7y = 000; break;
            case 35: r7y = 000; break;
            case 40: r7y = 000; break;
            case 45: r7y = 000; break;
            case 50: r7y = 000; break;
            case 55: r7y = 000; break;
            case 60: r7y = 000; break;
            case 65: r7y = 000; break;
            case 70: r7y = 000; break;
            case 75: r7y = 000; break;
            case 80: r7y = 000; break;
            case 85: r7y = 000; break;
            case 90: r7y = 000; break;
            case 95: r7y = 000; break;
            case 100: r7y = 000; break;
            case 105: r7y = 000; break;
            case 110: r7y = 000; break;
            case 115: r7y = 000; break;
            case 120: r7y = 000; break;
            case 125: r7y = 000; break;
            case 130: r7y = 000; break;
            case 135: r7y = 000; break;
            case 140: r7y = 000; break;
            case 145: r7y = 000; break;
            case 150: r7y = 000; break;
            case 155: r7y = 000; break;
            case 160: r7y = 000; break;
            case 165: r7y = 000; break;
            case 170: r7y = 000; break;
            case 175: r7y = 000; break;
            case 180: r7y = 000; break;
            case 185: r7y = 000; break;
            case 190: r7y = 000; break;
        }
        scene->addEllipse(r7x, r7y, 4, 4, penYellow);
    }// r7
    if (l7>0)
    {
        switch (l7)
        {
            case 5:  l7y = 000; break;
            case 10: l7y = 000; break;
            case 15: l7y = 000; break;
            case 20: l7y = 000; break;
            case 25: l7y = 000; break;
            case 30: l7y = 000; break;
            case 35: l7y = 000; break;
            case 40: l7y = 000; break;
            case 45: l7y = 000; break;
            case 50: l7y = 000; break;
            case 55: l7y = 000; break;
            case 60: l7y = 000; break;
            case 65: l7y = 000; break;
            case 70: l7y = 000; break;
            case 75: l7y = 000; break;
            case 80: l7y = 000; break;
            case 85: l7y = 000; break;
            case 90: l7y = 000; break;
            case 95: l7y = 000; break;
            case 100: l7y = 000; break;
            case 105: l7y = 000; break;
            case 110: l7y = 000; break;
            case 115: l7y = 000; break;
            case 120: l7y = 000; break;
            case 125: l7y = 000; break;
            case 130: l7y = 000; break;
            case 135: l7y = 000; break;
            case 140: l7y = 000; break;
            case 145: l7y = 000; break;
            case 150: l7y = 000; break;
            case 155: l7y = 000; break;
            case 160: l7y = 000; break;
            case 165: l7y = 000; break;
            case 170: l7y = 000; break;
            case 175: l7y = 000; break;
            case 180: l7y = 000; break;
            case 185: l7y = 000; break;
            case 190: l7y = 000; break;
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

void MainWindow::r8l8()
{
scene->addEllipse(r8x, r8, 4, 4, penRed);
scene->addEllipse(l8x, l8, 4, 4, penRed);
    if (r8 > 0)
    {
        switch (r8)
        {
            case 5:  r8y = 000; break;
            case 10: r8y = 000; break;
            case 15: r8y = 000; break;
            case 20: r8y = 000; break;
            case 25: r8y = 000; break;
            case 30: r8y = 000; break;
            case 35: r8y = 000; break;
            case 40: r8y = 000; break;
            case 45: r8y = 000; break;
            case 50: r8y = 000; break;
            case 55: r8y = 000; break;
            case 60: r8y = 000; break;
            case 65: r8y = 000; break;
            case 70: r8y = 000; break;
            case 75: r8y = 000; break;
            case 80: r8y = 000; break;
            case 85: r8y = 000; break;
            case 90: r8y = 000; break;
            case 95: r8y = 000; break;
            case 100: r8y = 000; break;
            case 105: r8y = 000; break;
            case 110: r8y = 000; break;
            case 115: r8y = 000; break;
            case 120: r8y = 000; break;
            case 125: r8y = 000; break;
            case 130: r8y = 000; break;
            case 135: r8y = 000; break;
            case 140: r8y = 000; break;
            case 145: r8y = 000; break;
            case 150: r8y = 000; break;
            case 155: r8y = 000; break;
            case 160: r8y = 000; break;
            case 165: r8y = 000; break;
            case 170: r8y = 000; break;
            case 175: r8y = 000; break;
            case 180: r8y = 000; break;
            case 185: r8y = 000; break;
            case 190: r8y = 000; break;
        }
        scene->addEllipse(r8x, r8y, 4, 4, penYellow);
    }// r8
    if (l8>0)
    {
        switch (l8)
        {
            case 5:  l8y = 000; break;
            case 10: l8y = 000; break;
            case 15: l8y = 000; break;
            case 20: l8y = 000; break;
            case 25: l8y = 000; break;
            case 30: l8y = 000; break;
            case 35: l8y = 000; break;
            case 40: l8y = 000; break;
            case 45: l8y = 000; break;
            case 50: l8y = 000; break;
            case 55: l8y = 000; break;
            case 60: l8y = 000; break;
            case 65: l8y = 000; break;
            case 70: l8y = 000; break;
            case 75: l8y = 000; break;
            case 80: l8y = 000; break;
            case 85: l8y = 000; break;
            case 90: l8y = 000; break;
            case 95: l8y = 000; break;
            case 100: l8y = 000; break;
            case 105: l8y = 000; break;
            case 110: l8y = 000; break;
            case 115: l8y = 000; break;
            case 120: l8y = 000; break;
            case 125: l8y = 000; break;
            case 130: l8y = 000; break;
            case 135: l8y = 000; break;
            case 140: l8y = 000; break;
            case 145: l8y = 000; break;
            case 150: l8y = 000; break;
            case 155: l8y = 000; break;
            case 160: l8y = 000; break;
            case 165: l8y = 000; break;
            case 170: l8y = 000; break;
            case 175: l8y = 000; break;
            case 180: l8y = 000; break;
            case 185: l8y = 000; break;
            case 190: l8y = 000; break;
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

void MainWindow::r9l9()
{
scene->addEllipse(r9x, r9, 4, 4, penRed);
scene->addEllipse(l9x, l9, 4, 4, penRed);
    if (r9 > 0)
    {
        switch (r9)
        {
            case 5:  r9y = 000; break;
            case 10: r9y = 000; break;
            case 15: r9y = 000; break;
            case 20: r9y = 000; break;
            case 25: r9y = 000; break;
            case 30: r9y = 000; break;
            case 35: r9y = 000; break;
            case 40: r9y = 000; break;
            case 45: r9y = 000; break;
            case 50: r9y = 000; break;
            case 55: r9y = 000; break;
            case 60: r9y = 000; break;
            case 65: r9y = 000; break;
            case 70: r9y = 000; break;
            case 75: r9y = 000; break;
            case 80: r9y = 000; break;
            case 85: r9y = 000; break;
            case 90: r9y = 000; break;
            case 95: r9y = 000; break;
            case 100: r9y = 000; break;
            case 105: r9y = 000; break;
            case 110: r9y = 000; break;
            case 115: r9y = 000; break;
            case 120: r9y = 000; break;
            case 125: r9y = 000; break;
            case 130: r9y = 000; break;
            case 135: r9y = 000; break;
            case 140: r9y = 000; break;
            case 145: r9y = 000; break;
            case 150: r9y = 000; break;
            case 155: r9y = 000; break;
            case 160: r9y = 000; break;
            case 165: r9y = 000; break;
            case 170: r9y = 000; break;
            case 175: r9y = 000; break;
            case 180: r9y = 000; break;
            case 185: r9y = 000; break;
            case 190: r9y = 000; break;
        }
        scene->addEllipse(r9x, r9y, 4, 4, penYellow);
    }// r9
    if (l9>0)
    {
        switch (l9)
        {
            case 5:  l9y = 000; break;
            case 10: l9y = 000; break;
            case 15: l9y = 000; break;
            case 20: l9y = 000; break;
            case 25: l9y = 000; break;
            case 30: l9y = 000; break;
            case 35: l9y = 000; break;
            case 40: l9y = 000; break;
            case 45: l9y = 000; break;
            case 50: l9y = 000; break;
            case 55: l9y = 000; break;
            case 60: l9y = 000; break;
            case 65: l9y = 000; break;
            case 70: l9y = 000; break;
            case 75: l9y = 000; break;
            case 80: l9y = 000; break;
            case 85: l9y = 000; break;
            case 90: l9y = 000; break;
            case 95: l9y = 000; break;
            case 100: l9y = 000; break;
            case 105: l9y = 000; break;
            case 110: l9y = 000; break;
            case 115: l9y = 000; break;
            case 120: l9y = 000; break;
            case 125: l9y = 000; break;
            case 130: l9y = 000; break;
            case 135: l9y = 000; break;
            case 140: l9y = 000; break;
            case 145: l9y = 000; break;
            case 150: l9y = 000; break;
            case 155: l9y = 000; break;
            case 160: l9y = 000; break;
            case 165: l9y = 000; break;
            case 170: l9y = 000; break;
            case 175: l9y = 000; break;
            case 180: l9y = 000; break;
            case 185: l9y = 000; break;
            case 190: l9y = 000; break;
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

void MainWindow::r10l10()
{
scene->addEllipse(r10x, r10, 4, 4, penRed);
scene->addEllipse(l10x, l10, 4, 4, penRed);
    if (r10 > 0)
    {
        switch (r10)
        {
            case 5:  r10y = 000; break;
            case 10: r10y = 000; break;
            case 15: r10y = 000; break;
            case 20: r10y = 000; break;
            case 25: r10y = 000; break;
            case 30: r10y = 000; break;
            case 35: r10y = 000; break;
            case 40: r10y = 000; break;
            case 45: r10y = 000; break;
            case 50: r10y = 000; break;
            case 55: r10y = 000; break;
            case 60: r10y = 000; break;
            case 65: r10y = 000; break;
            case 70: r10y = 000; break;
            case 75: r10y = 000; break;
            case 80: r10y = 000; break;
            case 85: r10y = 000; break;
            case 90: r10y = 000; break;
            case 95: r10y = 000; break;
            case 100: r10y = 000; break;
            case 105: r10y = 000; break;
            case 110: r10y = 000; break;
            case 115: r10y = 000; break;
            case 120: r10y = 000; break;
            case 125: r10y = 000; break;
            case 130: r10y = 000; break;
            case 135: r10y = 000; break;
            case 140: r10y = 000; break;
            case 145: r10y = 000; break;
            case 150: r10y = 000; break;
            case 155: r10y = 000; break;
            case 160: r10y = 000; break;
            case 165: r10y = 000; break;
            case 170: r10y = 000; break;
            case 175: r10y = 000; break;
            case 180: r10y = 000; break;
            case 185: r10y = 000; break;
            case 190: r10y = 000; break;
        }
        scene->addEllipse(r10x, r10y, 4, 4, penYellow);
    }// r10
    if (l10>0)
    {
        switch (l10)
        {
            case 5:  l10y = 000; break;
            case 10: l10y = 000; break;
            case 15: l10y = 000; break;
            case 20: l10y = 000; break;
            case 25: l10y = 000; break;
            case 30: l10y = 000; break;
            case 35: l10y = 000; break;
            case 40: l10y = 000; break;
            case 45: l10y = 000; break;
            case 50: l10y = 000; break;
            case 55: l10y = 000; break;
            case 60: l10y = 000; break;
            case 65: l10y = 000; break;
            case 70: l10y = 000; break;
            case 75: l10y = 000; break;
            case 80: l10y = 000; break;
            case 85: l10y = 000; break;
            case 90: l10y = 000; break;
            case 95: l10y = 000; break;
            case 100: l10y = 000; break;
            case 105: l10y = 000; break;
            case 110: l10y = 000; break;
            case 115: l10y = 000; break;
            case 120: l10y = 000; break;
            case 125: l10y = 000; break;
            case 130: l10y = 000; break;
            case 135: l10y = 000; break;
            case 140: l10y = 000; break;
            case 145: l10y = 000; break;
            case 150: l10y = 000; break;
            case 155: l10y = 000; break;
            case 160: l10y = 000; break;
            case 165: l10y = 000; break;
            case 170: l10y = 000; break;
            case 175: l10y = 000; break;
            case 180: l10y = 000; break;
            case 185: l10y = 000; break;
            case 190: l10y = 000; break;
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

void MainWindow::r11l11()
{
scene->addEllipse(r11x, r11, 4, 4, penRed);
scene->addEllipse(l11x, l11, 4, 4, penRed);
    if (r11 > 0)
    {
        switch (r11)
        {
            case 5:  r11y = 000; break;
            case 10: r11y = 000; break;
            case 15: r11y = 000; break;
            case 20: r11y = 000; break;
            case 25: r11y = 000; break;
            case 30: r11y = 000; break;
            case 35: r11y = 000; break;
            case 40: r11y = 000; break;
            case 45: r11y = 000; break;
            case 50: r11y = 000; break;
            case 55: r11y = 000; break;
            case 60: r11y = 000; break;
            case 65: r11y = 000; break;
            case 70: r11y = 000; break;
            case 75: r11y = 000; break;
            case 80: r11y = 000; break;
            case 85: r11y = 000; break;
            case 90: r11y = 000; break;
            case 95: r11y = 000; break;
            case 100: r11y = 000; break;
            case 105: r11y = 000; break;
            case 110: r11y = 000; break;
            case 115: r11y = 000; break;
            case 120: r11y = 000; break;
            case 125: r11y = 000; break;
            case 130: r11y = 000; break;
            case 135: r11y = 000; break;
            case 140: r11y = 000; break;
            case 145: r11y = 000; break;
            case 150: r11y = 000; break;
            case 155: r11y = 000; break;
            case 160: r11y = 000; break;
            case 165: r11y = 000; break;
            case 170: r11y = 000; break;
            case 175: r11y = 000; break;
            case 180: r11y = 000; break;
            case 185: r11y = 000; break;
            case 190: r11y = 000; break;
        }
        scene->addEllipse(r11x, r11y, 4, 4, penYellow);
    }// r11
    if (l11>0)
    {
        switch (l11)
        {
            case 5:  l11y = 000; break;
            case 10: l11y = 000; break;
            case 15: l11y = 000; break;
            case 20: l11y = 000; break;
            case 25: l11y = 000; break;
            case 30: l11y = 000; break;
            case 35: l11y = 000; break;
            case 40: l11y = 000; break;
            case 45: l11y = 000; break;
            case 50: l11y = 000; break;
            case 55: l11y = 000; break;
            case 60: l11y = 000; break;
            case 65: l11y = 000; break;
            case 70: l11y = 000; break;
            case 75: l11y = 000; break;
            case 80: l11y = 000; break;
            case 85: l11y = 000; break;
            case 90: l11y = 000; break;
            case 95: l11y = 000; break;
            case 100: l11y = 000; break;
            case 105: l11y = 000; break;
            case 110: l11y = 000; break;
            case 115: l11y = 000; break;
            case 120: l11y = 000; break;
            case 125: l11y = 000; break;
            case 130: l11y = 000; break;
            case 135: l11y = 000; break;
            case 140: l11y = 000; break;
            case 145: l11y = 000; break;
            case 150: l11y = 000; break;
            case 155: l11y = 000; break;
            case 160: l11y = 000; break;
            case 165: l11y = 000; break;
            case 170: l11y = 000; break;
            case 175: l11y = 000; break;
            case 180: l11y = 000; break;
            case 185: l11y = 000; break;
            case 190: l11y = 000; break;
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
    scene->addEllipse(r12x, r12, 4, 4, penRed);
    scene->addEllipse(l12x, l12, 4, 4, penRed);
    if (r12 > 0)
    {
        switch (r12)
        {
            case 5:  r12y = 000; break;
            case 10: r12y = 000; break;
            case 15: r12y = 000; break;
            case 20: r12y = 000; break;
            case 25: r12y = 000; break;
            case 30: r12y = 000; break;
            case 35: r12y = 000; break;
            case 40: r12y = 000; break;
            case 45: r12y = 000; break;
            case 50: r12y = 000; break;
            case 55: r12y = 000; break;
            case 60: r12y = 000; break;
            case 65: r12y = 000; break;
            case 70: r12y = 000; break;
            case 75: r12y = 000; break;
            case 80: r12y = 000; break;
            case 85: r12y = 000; break;
            case 90: r12y = 000; break;
            case 95: r12y = 000; break;
            case 100: r12y = 000; break;
            case 105: r12y = 000; break;
            case 110: r12y = 000; break;
            case 115: r12y = 000; break;
            case 120: r12y = 000; break;
            case 125: r12y = 000; break;
            case 130: r12y = 000; break;
            case 135: r12y = 000; break;
            case 140: r12y = 000; break;
            case 145: r12y = 000; break;
            case 150: r12y = 000; break;
            case 155: r12y = 000; break;
            case 160: r12y = 000; break;
            case 165: r12y = 000; break;
            case 170: r12y = 000; break;
            case 175: r12y = 000; break;
            case 180: r12y = 000; break;
            case 185: r12y = 000; break;
            case 190: r12y = 000; break;
        }
        scene->addEllipse(r12x, r12y, 4, 4, penYellow);
    }// r12
    if (l12>0)
    {
        switch (l12)
        {
            case 5:  l12y = 000; break;
            case 10: l12y = 000; break;
            case 15: l12y = 000; break;
            case 20: l12y = 000; break;
            case 25: l12y = 000; break;
            case 30: l12y = 000; break;
            case 35: l12y = 000; break;
            case 40: l12y = 000; break;
            case 45: l12y = 000; break;
            case 50: l12y = 000; break;
            case 55: l12y = 000; break;
            case 60: l12y = 000; break;
            case 65: l12y = 000; break;
            case 70: l12y = 000; break;
            case 75: l12y = 000; break;
            case 80: l12y = 000; break;
            case 85: l12y = 000; break;
            case 90: l12y = 000; break;
            case 95: l12y = 000; break;
            case 100: l12y = 000; break;
            case 105: l12y = 000; break;
            case 110: l12y = 000; break;
            case 115: l12y = 000; break;
            case 120: l12y = 000; break;
            case 125: l12y = 000; break;
            case 130: l12y = 000; break;
            case 135: l12y = 000; break;
            case 140: l12y = 000; break;
            case 145: l12y = 000; break;
            case 150: l12y = 000; break;
            case 155: l12y = 000; break;
            case 160: l12y = 000; break;
            case 165: l12y = 000; break;
            case 170: l12y = 000; break;
            case 175: l12y = 000; break;
            case 180: l12y = 000; break;
            case 185: l12y = 000; break;
            case 190: l12y = 000; break;
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






