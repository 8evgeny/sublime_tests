#include "mainwindow.h"

void MainWindow::channel_P()
{
//Канал легких
    if (((Channel_P == "B/2")||(Channel_P == "B/1")||(Channel_P == "B/0")||(Channel_P == "B/-1")||(Channel_P == "B/-2")) &&
        ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")||(Channel_RP == "A/-2")||(Channel_RP == "B/-2")||(Channel_RP == "C/-2")))
        {
            diagnosic_message.append("Канал легких: Острый ринит, евстахеит, отит.\n");
            return;
        }

    if (((Channel_P == "A/2")||(Channel_P == "A/1")||(Channel_P == "A/-1")||(Channel_P == "A/-2")) &&
        ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")||(Channel_RP == "A/-2")||(Channel_RP == "B/-2")||(Channel_RP == "C/-2")))
        {
            diagnosic_message.append("Канал легких: Острая простуда или острое заболевание органов дыхания.\n");
            return;
        }

    if (((Channel_P == "C/2")||(Channel_P == "C/1")||(Channel_P == "C/-1")||(Channel_P == "C/-2")||(Channel_P == "C/0")) &&
        ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")||(Channel_RP == "A/-2")||(Channel_RP == "B/-2")||(Channel_RP == "C/-2")))
        {
            diagnosic_message.append("Канал легких: Хронические заболевания органов дыхания.\n");
            return;
        }

    if (Channel_P == "A/2")
    {
        diagnosic_message.append("Канал лёгких: острое заболевание органов дыхательной системы.\n");
    }
    if (Channel_P == "A/1")
    {
        diagnosic_message.append("Канал лёгких: дискомфорт, предвестник заболевания.\n");
    }
   if (Channel_P == "A/0")
    {
        diagnosic_message.append("Канал лёгких: норма.\n");
    }
   if (Channel_P == "A/-1")
    {
        diagnosic_message.append("Канал лёгких: состояние перед выздоровлением.\n");
    }
   if (Channel_P == "A/-2")
    {
        diagnosic_message.append("Канал лёгких: затухание клинических симптомов заболевания органов дыхания.\n");
    }
   if (Channel_P == "OK")
    {
        diagnosic_message.append("Канал лёгких: правосторонняя пневмония.\n");
    }

//Канал легких В
    if (Channel_P == "B/2")
    {
        diagnosic_message.append("Канал лёгких: острая легкая простуда, насморк или кашель.\n");
    }
    if (Channel_P == "B/1")
    {
        diagnosic_message.append("Канал лёгких: норма.\n");
    }
    if (Channel_P == "B/0")
    {
        diagnosic_message.append("Канал лёгких: норма.\n");
    }
    if (Channel_P == "B/-1")
    {
        diagnosic_message.append("Канал лёгких: норма.\n");
    }
    if (Channel_P == "B/-2")
    {
        diagnosic_message.append("Канал лёгких: состояние перед выздоровлением.\n");
    }

//Канал легких С
    if (Channel_P == "C/2")
    {
        diagnosic_message.append("Канал лёгких: обострение хронического заболевания органов дыхания.\n");
    }
    if (Channel_P == "C/1")
    {
        diagnosic_message.append("Канал лёгких: начало обострения хронического заболевания органов дыхания.\n");
    }
    if (Channel_P == "C/0")
    {
        diagnosic_message.append("Канал лёгких: непроявленное заболевание, ремиссия или предрасположенность.\n");
    }
    if (Channel_P == "C/-1")
    {
        diagnosic_message.append("Канал лёгких: состояние перед ремиссией.\n");
    }
    if (Channel_P == "C/-2")
    {
        diagnosic_message.append("Канал лёгких: вялотекущий хронический процесс в дыхательной системе.\n");
    }
    if (Channel_P == "OP")
    {
        diagnosic_message.append("Канал лёгких: левосторонняя пневмония.\n");
    }

}

void MainWindow::channel_MC()
{


}

void MainWindow::channel_C()
{


}

void MainWindow::channel_IG()
{


}

void MainWindow::channel_TR()
{


}

void MainWindow::channel_GI()
{


}

void MainWindow::channel_RP()
{


}

void MainWindow::channel_F()
{


}

void MainWindow::channel_R()
{


}

void MainWindow::channel_V()
{


}

void MainWindow::channel_VB()
{


}

void MainWindow::channel_E()
{


}

#if 0

#endif
