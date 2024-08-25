#include "mainwindow.h"
#include <QGraphicsScene>

using namespace std;
extern QPen penTriangle;
extern QGraphicsScene * scene;

// OK OP ABC/-2 -1 0 1 2
void MainWindow::diagnostic()
{
    channel_P();
    channel_MC();
    channel_C();
    channel_IG();
    channel_TR();
    channel_GI();
    channel_RP();
    channel_F();
    channel_R();
    channel_V();
    channel_VB();
    channel_E();
}

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

//Закрашиваем треугольники
    if (Channel_P.find_first_of('0') == string::npos ) //Обе точки не в коридоре
    {
        if (Channel_P.find("-2") != string::npos)//Обе точки ниже
        {
            scene->addEllipse(122, 772, 8, 8, penTriangle);
            scene->addEllipse(178, 772, 8, 8, penTriangle);
        }
        if (Channel_P.find("A/-1") != string::npos)//левая ниже
        {
            scene->addEllipse(122, 772, 8, 8, penTriangle);
        }
        if (Channel_P.find("C/-1") != string::npos)//правая ниже
        {
            scene->addEllipse(178, 772, 8, 8, penTriangle);
        }
        if (Channel_P.find("/2") != string::npos)//Обе точки выше
        {
            scene->addEllipse(121, 795, 8, 8, penTriangle);
            scene->addEllipse(177, 795, 8, 8, penTriangle);
        }
        if (Channel_P.find("A/1") != string::npos)//правая выше
        {
            scene->addEllipse(177, 795, 8, 8, penTriangle);
        }
        if (Channel_P.find("C/1") != string::npos)//левая выше
        {
            scene->addEllipse(121, 795, 8, 8, penTriangle);
        }
        if (Channel_P.find("OP") != string::npos)//левая выше  правая ниже
        {
            scene->addEllipse(121, 795, 8, 8, penTriangle);
            scene->addEllipse(178, 772, 8, 8, penTriangle);
        }
        if (Channel_P.find("OK") != string::npos)//левая ниже  правая выше
        {
            scene->addEllipse(122, 772, 8, 8, penTriangle);
            scene->addEllipse(177, 795, 8, 8, penTriangle);
        }
    }//triangles
}

void MainWindow::channel_MC()
{
//Канал перикарда А
    if (Channel_MC == "A/2")
    {
        diagnosic_message.append("Канал перикарда: нервное перевозбуждение, повышенное АД, повышенное сексуальное желание.\n");
    }
    if (Channel_MC == "A/1")
    {
        diagnosic_message.append("Канал перикарда: нервное перевозбуждение, повышенное АД, повышенное сексуальное желание.\n");
    }
    if (Channel_MC == "A/0")
    {
        diagnosic_message.append("Канал перикарда: норма.\n");
    }
    if (Channel_MC == "A/-1")
    {
        diagnosic_message.append("Канал перикарда: понижено АД.\n");
    }
    if (Channel_MC == "A/-2")
    {
        diagnosic_message.append("Канал перикарда: понижено АД, понижено сексуальное желание.\n");
    }
    if (Channel_MC == "OK")
    {
        diagnosic_message.append("Канал перикарда: бывает при эндометритах и простатитах.\n");
    }

//Канал перикарда В
    if (Channel_MC == "B/2")
    {
        diagnosic_message.append("Канал перикарда: повышено систолическое давление.\n");
    }
    if (Channel_MC == "B/1")
    {
        diagnosic_message.append("Канал перикарда: норма.\n");
    }
    if (Channel_MC == "B/0")
    {
        diagnosic_message.append("Канал перикарда: норма.\n");
    }
    if (Channel_MC == "B/-1")
    {
        diagnosic_message.append("Канал перикарда: норма.\n");
    }
    if (Channel_MC == "B/-2")
    {
        diagnosic_message.append("Канал перикарда: понижено систолическое давление.\n");
    }

//Канал перикарда С
    if (Channel_MC == "C/2")
    {
        diagnosic_message.append("Канал перикарда: обострение хронических заболеваний половой системы, гипертония.\n");
    }
    if (Channel_MC == "C/1")
    {
        diagnosic_message.append("Канал перикарда: начало клинических проявлений заболеваний половой системы, гипертония.\n");
    }
    if (Channel_MC == "C/0")
    {
        diagnosic_message.append("Канал перикарда: непроявленные заболевания половой системы, ремиссия или предрасположенность.\n");
    }
    if (Channel_MC == "C/-1")
    {
        diagnosic_message.append("Канал перикарда: состояние перед ремиссией заболеваний половой системы.\n");
    }
    if (Channel_MC == "C/-2")
    {
        diagnosic_message.append("Канал перикарда: вялотекущее хроническое заболевание половой системы.\n");
    }
    if (Channel_MC == "OP")
    {
        diagnosic_message.append("Канал перикарда: вероятность опухоли в органах половой системы, или их тяжелое воспаление. Но здесь нужно смотреть сочетания с другими меридианами!.\n");
    }
//Закрашиваем треугольники
    if (Channel_MC.find_first_of('0') == string::npos ) //Обе точки не в коридоре
    {
        if (Channel_MC.find("-2") != string::npos)//Обе точки ниже
        {
            scene->addEllipse(208, 772, 8, 8, penTriangle);
            scene->addEllipse(264, 772, 8, 8, penTriangle);
        }
        if (Channel_MC.find("A/-1") != string::npos)//левая ниже
        {
            scene->addEllipse(208, 772, 8, 8, penTriangle);
        }
        if (Channel_MC.find("C/-1") != string::npos)//правая ниже
        {
            scene->addEllipse(264, 772, 8, 8, penTriangle);
        }
        if (Channel_MC.find("/2") != string::npos)//Обе точки выше
        {
            scene->addEllipse(208, 795, 8, 8, penTriangle);
            scene->addEllipse(264, 795, 8, 8, penTriangle);
        }
        if (Channel_MC.find("A/1") != string::npos)//правая выше
        {
            scene->addEllipse(264, 795, 8, 8, penTriangle);
        }
        if (Channel_MC.find("C/1") != string::npos)//левая выше
        {
            scene->addEllipse(208, 795, 8, 8, penTriangle);
        }
        if (Channel_MC.find("OP") != string::npos)//левая выше  правая ниже
        {
            scene->addEllipse(208, 795, 8, 8, penTriangle);
            scene->addEllipse(264, 772, 8, 8, penTriangle);
        }
        if (Channel_MC.find("OK") != string::npos)//левая ниже  правая выше
        {
            scene->addEllipse(208, 772, 8, 8, penTriangle);
            scene->addEllipse(264, 795, 8, 8, penTriangle);
        }
    }//triangles
}

void MainWindow::channel_C()
{
//Канал сердца А
    if (Channel_C == "A/2")
    {
        diagnosic_message.append("Канал сердца: тахикардия, гипертрофия левого желудочка сердца, повышено АД.\n");
    }
    if (Channel_C == "A/1")
    {
        diagnosic_message.append("Канал сердца: тахикардия, гипертрофия левого желудочка сердца, повышено АД.\n");
    }
    if (Channel_C == "A/0")
    {
        diagnosic_message.append("Канал сердца: норма.\n");
    }
    if (Channel_C == "A/-1")
    {
        diagnosic_message.append("Канал сердца: брадикардия, гипертрофия правого желудочка сердца, понижено АД.\n");
    }
    if (Channel_C == "A/-2")
    {
        diagnosic_message.append("Канал сердца: брадикардия, гипертрофия правого желудочка сердца, понижено АД.\n");
    }
    if (Channel_C == "OK")
    {
        diagnosic_message.append("Канал сердца: миокардиодистрофия.\n");
    }

//Канал сердца В
    if (Channel_C == "B/2")
    {
        diagnosic_message.append("Канал сердца: тахикардия, повышено диастолическое давление.\n");
    }
    if (Channel_C == "B/1")
    {
        diagnosic_message.append("Канал сердца: норма.\n");
    }
    if (Channel_C == "B/0")
    {
        diagnosic_message.append("Канал сердца: норма.\n");
    }
    if (Channel_C == "B/-1")
    {
        diagnosic_message.append("Канал сердца: норма.\n");
    }
   if (Channel_C == "B/2")
    {
        diagnosic_message.append("Канал сердца: брадикардия, понижено диастолическое давление.\n");
    }

//Канал сердца С
    if (Channel_C == "C/2")
    {
        diagnosic_message.append("Канал сердца: тахикардия, гипертрофия правого желудочка сердца.\n");
    }
    if (Channel_C == "C/1")
    {
        diagnosic_message.append("Канал сердца: тахикардия, гипертония, гипертрофия правого желудочка сердца.\n");
    }
    if (Channel_C == "C/0")
    {
        diagnosic_message.append("Канал сердца: норма.\n");
    }
    if (Channel_C == "C/-1")
    {
        diagnosic_message.append("Канал сердца: брадикардия, гипотония, гипертрофия левого желудочка сердца.\n");
    }
    if (Channel_C == "C/-2")
    {
        diagnosic_message.append("Канал сердца: брадикардия, гипотония, гипертрофия левого желудочка сердца; переходное состояние из гипотонии в гипертонию.\n");
    }
    if (Channel_C == "OP")
    {
        diagnosic_message.append("Канал сердца: миокардит, или \"панцирное сердце\" бывает при раке щитовидной железы.\n");
    }
//Закрашиваем треугольники
    if (Channel_C.find_first_of('0') == string::npos ) //Обе точки не в коридоре
    {
        if (Channel_C.find("-2") != string::npos)//Обе точки ниже
        {
            scene->addEllipse(294, 772, 8, 8, penTriangle);
            scene->addEllipse(353, 772, 8, 8, penTriangle);
        }
        if (Channel_C.find("A/-1") != string::npos)//левая ниже
        {
            scene->addEllipse(294, 772, 8, 8, penTriangle);
        }
        if (Channel_C.find("C/-1") != string::npos)//правая ниже
        {
            scene->addEllipse(353, 772, 8, 8, penTriangle);
        }
        if (Channel_C.find("/2") != string::npos)//Обе точки выше
        {
            scene->addEllipse(294, 795, 8, 8, penTriangle);
            scene->addEllipse(353, 795, 8, 8, penTriangle);
        }
        if (Channel_C.find("A/1") != string::npos)//правая выше
        {
            scene->addEllipse(353, 795, 8, 8, penTriangle);
        }
        if (Channel_C.find("C/1") != string::npos)//левая выше
        {
            scene->addEllipse(294, 795, 8, 8, penTriangle);
        }
        if (Channel_C.find("OP") != string::npos)//левая выше  правая ниже
        {
            scene->addEllipse(294, 795, 8, 8, penTriangle);
            scene->addEllipse(353, 772, 8, 8, penTriangle);
        }
        if (Channel_C.find("OK") != string::npos)//левая ниже  правая выше
        {
            scene->addEllipse(294, 772, 8, 8, penTriangle);
            scene->addEllipse(353, 795, 8, 8, penTriangle);
        }
    }//triangles
}

void MainWindow::channel_IG()
{
    //Канал тонкого кишечника А
        if (Channel_IG == "A/2")
        {
            diagnosic_message.append("Канал тонк.киш.: через 1,5-2 часа после приема пищи.\n");
        }
        if (Channel_IG == "A/1")
        {
            diagnosic_message.append("Канал тонк.киш.: норма.\n");
        }
        if (Channel_IG == "A/0")
        {
            diagnosic_message.append("Канал тонк.киш.: норма.\n");
        }
        if (Channel_IG == "A/-1")
        {
            diagnosic_message.append("Канал тонк.киш.: норма.\n");
        }
        if (Channel_IG == "A/-2")
        {
            diagnosic_message.append("Канал тонк.киш.: через 2 часа после приема пищи.\n");
        }

    //Канал тонкого кишечника B
        if (Channel_IG == "B/2")
        {
            diagnosic_message.append("Канал тонк.киш.: через 1,5-2 часа после приема пищи.\n");
        }
        if (Channel_IG == "B/1")
        {
            diagnosic_message.append("Канал тонк.киш.: норма.\n");
        }
        if (Channel_IG == "B/0")
        {
            diagnosic_message.append("Канал тонк.киш.: норма.\n");
        }
        if (Channel_IG == "B/-1")
        {
            diagnosic_message.append("Канал тонк.киш.: норма.\n");
        }
        if (Channel_IG == "B/-2")
        {
            diagnosic_message.append("Канал тонк.киш.: через 2 часа после приема пищи.\n");
        }

    //Канал тонкого кишечника C
        if (Channel_IG == "C/2")
        {
            diagnosic_message.append("Канал тонк.киш.: обострение хронического дуоденита.\n");
        }
        if (Channel_IG == "C/1")
        {
            diagnosic_message.append("Канал тонк.киш.: начало обострения хронического дуоденита.\n");
        }
        if (Channel_IG == "C/0")
        {
            diagnosic_message.append("Канал тонк.киш.: непроявленное заболевание, ремиссия, или есть предрасположенность.\n");
        }
        if (Channel_IG == "C/-1")
        {
            diagnosic_message.append("Канал тонк.киш.: состояние перед ремиссией дуоденита.\n");
        }
        if (Channel_IG == "C/-2")
        {
            diagnosic_message.append("Канал тонк.киш.: старый вялотекущий дуоденит.\n");
        }
        if (Channel_IG == "OP")
        {
            diagnosic_message.append("Канал тонк.киш.: через 2 часа после обильного застолья при дуодените; или вероятность рака 12-ти перстной кишки (нужно дополнительно смотреть состояние других меридианов!) .\n");
        }

}

void MainWindow::channel_TR()
{
    //Канал тройного обогревателя А
        if (Channel_TR == "A/2")
        {
            diagnosic_message.append("Канал 3 обогревателя: физическое пернапряжение.\n");
        }
        if (Channel_TR == "A/1")
        {
            diagnosic_message.append("Канал 3 обогревателя: норма.\n");
        }
        if (Channel_TR == "A/0")
        {
            diagnosic_message.append("Канал 3 обогревателя: норма.\n");
        }
        if (Channel_TR == "A/-1")
        {
            diagnosic_message.append("Канал 3 обогревателя: норма.\n");
        }
        if (Channel_TR == "A/-2")
        {
            diagnosic_message.append("Канал 3 обогревателя: физическое утомление.\n");
        }
        if (Channel_TR == "OK")
        {
            diagnosic_message.append("Канал 3 обогревателя: дисфункция гормональной системы (сглаз).\n");
        }

    //Канал тройного обогревателя В
        if (Channel_TR == "B/2")
        {
            diagnosic_message.append("Канал 3 обогревателя: избыток энергии.\n");
        }
        if (Channel_TR == "B/1")
        {
            diagnosic_message.append("Канал 3 обогревателя: норма.\n");
        }
        if (Channel_TR == "B/0")
        {
            diagnosic_message.append("Канал 3 обогревателя: норма.\n");
        }
        if (Channel_TR == "B/-1")
        {
            diagnosic_message.append("Канал 3 обогревателя: норма.\n");
        }
        if (Channel_TR == "B/-2")
        {
            diagnosic_message.append("Канал 3 обогревателя: усталость, физическое переутомление.\n");
        }

    //Канал тройного обогревателя С
        if (Channel_TR == "C/2")
        {
            diagnosic_message.append("Канал 3 обогревателя: гиперфункция гормональной системы.\n");
        }
        if (Channel_TR == "C/1")
        {
            diagnosic_message.append("Канал 3 обогревателя: гиперфункция гормональной системы.\n");
        }
        if (Channel_TR == "C/0")
        {
            diagnosic_message.append("Канал 3 обогревателя: дисфункция гормональной системы.\n");
        }
        if (Channel_TR == "C/-1")
        {
            diagnosic_message.append("Канал 3 обогревателя: гипофункция гормональной системы.\n");
        }
        if (Channel_TR == "C/-2")
        {
            diagnosic_message.append("Канал 3 обогревателя: гипофункция гормональной системы.\n");
        }
        if (Channel_TR == "OP")
        {
            diagnosic_message.append("Канал 3 обогревателя: тяжелая дисфункция гормональной системы (порча).\n");
        }

}

void MainWindow::channel_GI()
{
    //Канал толстого кишечника А
        if (Channel_GI == "A/2")
        {
            diagnosic_message.append("Канал толст.киш.: усиление перистальтики толстого кишечника.\n");
        }
        if (Channel_GI == "A/1")
        {
            diagnosic_message.append("Канал толст.киш.: небольшое усиление функции толстого кишечника.\n");
        }
        if (Channel_GI == "A/0")
        {
            diagnosic_message.append("Канал толст.киш.: норма.\n");
        }
        if (Channel_GI == "A/-1")
        {
            diagnosic_message.append("Канал толст.киш.: склонность к неполному опорожнению кишечника.\n");
        }
        if (Channel_GI == "A/-2")
        {
            diagnosic_message.append("Канал толст.киш.: запор на нервной почве.\n");
        }
        if (Channel_GI == "OK")
        {
            diagnosic_message.append("Канал толст.киш.: метеоризм.\n");
        }

    //Канал толстого кишечника В
        if (Channel_GI == "B/2")
        {
            diagnosic_message.append("Канал толст.киш.: усиление перистальтики толстого кишечника, употребление слабительного.\n");
        }
        if (Channel_GI == "B/1")
        {
            diagnosic_message.append("Канал толст.киш.: норма.\n");
        }
        if (Channel_GI == "B/01")
        {
            diagnosic_message.append("Канал толст.киш.: норма.\n");
        }
        if (Channel_GI == "B/-1")
        {
            diagnosic_message.append("Канал толст.киш.: норма.\n");
        }
        if (Channel_GI == "B/-2")
        {
            diagnosic_message.append("Канал толст.киш.: запор на нервной почве.\n");
        }

    //Канал толстого кишечника С
        if (Channel_GI == "C/2")
        {
            diagnosic_message.append("Канал толст.киш.: усиление перистальтики толстого кишечника, колит.\n");
        }
        if (Channel_GI == "C/1")
        {
            diagnosic_message.append("Канал толст.киш.: небольшое усиление перистальтики толстого кишечника.\n");
        }
        if (Channel_GI == "C/0")
        {
            diagnosic_message.append("Канал толст.киш.: непроявленное заболевание, ремиссия или предрасположенность.\n");
        }
        if (Channel_GI == "C/-1")
        {
            diagnosic_message.append("Канал толст.киш.: начальная стадия колита.\n");
        }
        if (Channel_GI == "C/-2")
        {
            diagnosic_message.append("Канал толст.киш.: хронический колит.\n");
        }
        if (Channel_GI == "OP")
        {
            diagnosic_message.append("Канал толст.киш.: метеоризм при колите; вероятность рака толстой кишки (нужно уточнять другие меридианы!).\n");
        }

}

void MainWindow::channel_RP()
{
    //Канал селезенки и поджелудочной А
        if (Channel_RP == "A/2")
        {
            diagnosic_message.append("Канал селезенки: повышен сахар и иммунитет, лейкоцитоз, селезенка работает в напряженном режиме.\n");
        }
        if (Channel_RP == "A/1")
        {
            diagnosic_message.append("Канал селезенки: начинает повышаться сахар в крови и иммунитет.\n");
        }
        if (Channel_RP == "A/0")
        {
            diagnosic_message.append("Канал селезенки: норма.\n");
        }
        if (Channel_RP == "A/-1")
        {
            diagnosic_message.append("Канал селезенки: снижается сахар в крови, снижается иммунитет.\n");
        }
        if (Channel_RP == "A/-2")
        {
            diagnosic_message.append("Канал селезенки: понижен сахар и иммунитет, или состояние голода.\n");
        }
        if (Channel_RP == "OK")
        {
            diagnosic_message.append("Канал селезенки: переходное состояние в панкреатит.\n");
        }

    //Канал селезенки и поджелудочной В
        if (Channel_RP == "B/2")
        {
            diagnosic_message.append("Канал селезенки: сахар повышен, иммунитет повышен.\n");
        }
        if (Channel_RP == "B/1")
        {
            diagnosic_message.append("Канал селезенки: норма.\n");
        }
        if (Channel_RP == "B/0")
        {
            diagnosic_message.append("Канал селезенки: норма.\n");
        }
        if (Channel_RP == "B/-1")
        {
            diagnosic_message.append("Канал селезенки: норма.\n");
        }
        if (Channel_RP == "B/-2")
        {
            diagnosic_message.append("Канал селезенки: сахар понижен, или состояние голода.\n");
        }

    //Канал селезенки и поджелудочной С
        if (Channel_RP == "C/2")
        {
            diagnosic_message.append("Канал селезенки: обострение хронического панкреатита, лейкоцитоз, сдвиг лейкоцитарной формулы влево.\n");
        }
        if (Channel_RP == "C/1")
        {
            diagnosic_message.append("Канал селезенки: начальные проявления панкреатита.\n");
        }
        if (Channel_RP == "C/0")
        {
            diagnosic_message.append("Канал селезенки: непроявленное заболвавние, ремиссия или предрасположенность.\n");
        }
        if (Channel_RP == "C/-1")
        {
            diagnosic_message.append("Канал селезенки: увеличение селезенки.\n");
        }
        if (Channel_RP == "C/-2")
        {
            diagnosic_message.append("Канал селезенки: состояние голода у больного панкреатитом; или гипогликемия, лейкопения; \n вероятность тяжелого поражения, рак, иммунодефицит (нужно смотреть другие меридианы!) \n");
        }
        if (Channel_RP == "OP")
        {
            diagnosic_message.append("Канал селезенки: предрак, или состояние рака поджелудочной железы или селезенки (нужно смотреть другие меридианы!) \n");
        }

}

void MainWindow::channel_F()
{
    //Канал печени А
        if (Channel_F == "A/2")
        {
            diagnosic_message.append("Канал печени: вероятность приема кофе, крепкого чая, алкоголя, лекарств.\n");
        }
        if (Channel_F == "A/1")
        {
            diagnosic_message.append("Канал печени: вероятность приема кофе, крепкого чая, алкоголя, лекарств.\n");
        }
        if (Channel_F == "A/0")
        {
            diagnosic_message.append("Канал печени: норма.\n");
        }
       if (Channel_F == "A/-1")
        {
            diagnosic_message.append("Канал печени: понижена функция печени.\n");
        }
       if (Channel_F == "A/-2")
        {
            diagnosic_message.append("Канал печени: понижена функция печени.\n");
        }
       if (Channel_F == "OK")
        {
            diagnosic_message.append("Канал печени: шлаки в печени.\n");
        }

    //Канал печени В
        if (Channel_F == "B/2")
        {
            diagnosic_message.append("Канал печени: вероятность приема кофе, крепкого чая, алкоголя, лекарств.\n");
        }
        if (Channel_F == "B/1")
        {
            diagnosic_message.append("Канал печени: норма.\n");
        }
        if (Channel_F == "B/0")
        {
            diagnosic_message.append("Канал печени: норма.\n");
        }
        if (Channel_F == "B/-1")
        {
            diagnosic_message.append("Канал печени: норма.\n");
        }
        if (Channel_F == "B/-2")
        {
            diagnosic_message.append("Канал печени: функция печени понижена.\n");
        }

    //Канал печени С
        if (Channel_F == "C/2")
        {
            diagnosic_message.append("Канал печени: обострение хронического гепатита.\n");
        }
        if (Channel_F == "C/1")
        {
            diagnosic_message.append("Канал печени: обострение хронического гепатита.\n");
        }
        if (Channel_F == "C/0")
        {
            diagnosic_message.append("Канал печени: непроявленное заболевание, ремиссия или предрасположенность.\n");
        }
        if (Channel_F == "C/-1")
        {
            diagnosic_message.append("Канал печени: увеличение печени (гепатит).\n");
        }
        if (Channel_F == "C/-2")
        {
            diagnosic_message.append("Канал печени: старый гепатит, вероятен переход в цирроз.\n");
        }
        if (Channel_F == "OP")
        {
            diagnosic_message.append("Канал печени: вероятность рака печени, или цирроза печени (нужно еще смотреть другие каналы!).\n");
        }

}

void MainWindow::channel_R()
{
    //Канал почек А
        if (Channel_R == "A/2")
        {
            diagnosic_message.append("Канал почек: усиленное мочеиспускание, вероятность приема мочегонных препаратов.\n");
        }
        if (Channel_R == "A/1")
        {
            diagnosic_message.append("Канал почек: небольшое усиление мочеиспускания.\n");
        }
        if (Channel_R == "A/0")
        {
            diagnosic_message.append("Канал почек: норма.\n");
        }
        if (Channel_R == "A/-1")
        {
            diagnosic_message.append("Канал почек: отёки, вероятность наличия заболевания в правой почке, или опущение правой почки.\n");
        }
        if (Channel_R == "A/-2")
        {
            diagnosic_message.append("Канал почек: отёки, вероятность камня в правой почке, опущение правой почки, или её воспаление.\n");
        }
        if (Channel_R == "OK")
        {
            diagnosic_message.append("Канал почек: вероятность отказа правой почки (камни, сморщенная почка, рак, отсутствие почки).\n");
        }

    //Канал почек В
        if (Channel_R == "B/2")
        {
            diagnosic_message.append("Канал почек: усиленное мочеиспускание, вероятность приема мочегонных препаратов.\n");
        }
        if (Channel_R == "B/1")
        {
            diagnosic_message.append("Канал почек: норма.\n");
        }
        if (Channel_R == "B/0")
        {
            diagnosic_message.append("Канал почек: норма.\n");
        }
        if (Channel_R == "B/-1")
        {
            diagnosic_message.append("Канал почек: норма.\n");
        }
        if (Channel_R == "B/-2")
        {
            diagnosic_message.append("Канал почек: отёки (функциональные); вероятность присутствия камней в обеих почках, опущение почек.\n");
        }

    //Канал почек С
        if (Channel_R == "C/2")
        {
            diagnosic_message.append("Канал почек: начало мочекаменной болезни.\n");
        }
        if (Channel_R == "C/1")
        {
            diagnosic_message.append("Канал почек: начало мочекаменной болезни.\n");
        }
        if (Channel_R == "C/0")
        {
            diagnosic_message.append("Канал почек: норма.\n");
        }
        if (Channel_R == "C/-1")
        {
            diagnosic_message.append("Канал почек: отёки, вероятность камня в левой почке, или опущение левой почки.\n");
        }
        if (Channel_R == "C/-2")
        {
            diagnosic_message.append("Канал почек: отёки, вероятность камня в левой почке, или опущение левой почки, воспаление.\n");
        }
        if (Channel_R == "OP")
        {
            diagnosic_message.append("Канал почек: вероятность отключения левой почки, её отсутствие, камни, рак (нужно еще смотреть другие меридианы!).\n");
        }

}

void MainWindow::channel_V()
{
    //Канал мочевого пузыря А
        if (Channel_V == "A/2")
        {
            diagnosic_message.append("Канал мочевого пузыря: умственное перевозбуждение.\n");
        }
        if (Channel_V == "A/1")
        {
            diagnosic_message.append("Канал мочевого пузыря: норма.\n");
        }
        if (Channel_V == "A/0")
        {
            diagnosic_message.append("Канал мочевого пузыря: норма.\n");
        }
        if (Channel_V == "A/-1")
        {
            diagnosic_message.append("Канал мочевого пузыря: норма.\n");
        }
        if (Channel_V == "A/-2")
        {
            diagnosic_message.append("Канал мочевого пузыря: переутомление нервной системы, пониженная работоспособность мозга (например при переутомлении или голоде).\n");
        }
        if (Channel_V == "OK")
        {
            diagnosic_message.append("Канал мочевого пузыря: переполнение мочевого пузыря.\n");
        }

    //Канал мочевого пузыря В
        if (Channel_V == "B/2")
        {
            diagnosic_message.append("Канал мочевого пузыря: напряжение нервной системы.\n");
        }
        if (Channel_V == "B/1")
        {
            diagnosic_message.append("Канал мочевого пузыря: норма.\n");
        }
        if (Channel_V == "B/0")
        {
            diagnosic_message.append("Канал мочевого пузыря: норма.\n");
        }
        if (Channel_V == "B/-1")
        {
            diagnosic_message.append("Канал мочевого пузыря: норма.\n");
        }
        if (Channel_V == "B/2")
        {
            diagnosic_message.append("Канал мочевого пузыря: утомление нервной системы, пониженная работоспособность мозга (например при усталости или голоде).\n");
        }

    //Канал мочевого пузыря С
        if (Channel_V == "C/2")
        {
            diagnosic_message.append("Канал мочевого пузыря: эмоциональное перевозбуждение.\n");
        }
        if (Channel_V == "C/1")
        {
            diagnosic_message.append("Канал мочевого пузыря: норма.\n");
        }
        if (Channel_V == "C/0")
        {
            diagnosic_message.append("Канал мочевого пузыря: норма.\n");
        }
        if (Channel_V == "C/-1")
        {
            diagnosic_message.append("Канал мочевого пузыря: норма.\n");
        }
        if (Channel_V == "C/-2")
        {
            diagnosic_message.append("Канал мочевого пузыря: переутомление нервной системы, пониженная работоспособность мозга (например при усталости или голоде).\n");
        }
        if (Channel_V == "OP")
        {
            diagnosic_message.append("Канал мочевого пузыря: вероятность рака мочевого пузыря или костей (нужно еще смотреть другие меридианы!).\n");
        }

}

void MainWindow::channel_VB()
{
    //Канал желчного пузыря А
        if (Channel_VB == "A/2")
        {
            diagnosic_message.append("Канал желчного пузыря: начальная стадия бескаменного холецистита.\n");
        }
        if (Channel_VB == "A/1")
        {
            diagnosic_message.append("Канал желчного пузыря: норма.\n");
        }
        if (Channel_VB == "A/0")
        {
            diagnosic_message.append("Канал желчного пузыря: норма.\n");
        }
        if (Channel_VB == "A/-1")
        {
            diagnosic_message.append("Канал желчного пузыря: норма.\n");
        }
        if (Channel_VB == "A/-2")
        {
            diagnosic_message.append("Канал желчного пузыря: хронический бескаменный холецистит.\n");
        }
        if (Channel_VB == "OK")
        {
            diagnosic_message.append("Канал желчного пузыря: избыток желчи при бескаменном холецистите.\n");
        }

    //Канал желчного пузыря В
        if (Channel_VB == "B/2")
        {
            diagnosic_message.append("Канал желчного пузыря: дискинезия желчных путей.\n");
        }
        if (Channel_VB == "B/1")
        {
            diagnosic_message.append("Канал желчного пузыря: норма.\n");
        }
        if (Channel_VB == "B/0")
        {
            diagnosic_message.append("Канал желчного пузыря: норма.\n");
        }
        if (Channel_VB == "B/-1")
        {
            diagnosic_message.append("Канал желчного пузыря: норма.\n");
        }
        if (Channel_VB == "B/-2")
        {
            diagnosic_message.append("Канал желчного пузыря: дискинезия желчных путей.\n");
        }

    //Канал желчного пузыря С
        if (Channel_VB == "C/2")
        {
            diagnosic_message.append("Канал желчного пузыря: начальная стадия желчекаменной болезни.\n");
        }
        if (Channel_VB == "C/1")
        {
            diagnosic_message.append("Канал желчного пузыря: начальная стадия желчекаменной болезни.\n");
        }
        if (Channel_VB == "C/0")
        {
            diagnosic_message.append("Канал желчного пузыря: непроявленное заболевание, ремиссия или предрасположенность.\n");
        }
        if (Channel_VB == "C/-1")
        {
            diagnosic_message.append("Канал желчного пузыря: желчекаменная болезнь.\n");
        }
        if (Channel_VB == "C/-2")
        {
            diagnosic_message.append("Канал желчного пузыря: желчекаменная болезнь. Вероятность наличия камней или песка в желчном пузыре (нужно еще смотреть другие меридианы!).\n");
        }
        if (Channel_VB == "OP")
        {
            diagnosic_message.append("Канал желчного пузыря: наличие камней или песка в желчном пузыре. Вероятность рака желчного пузыря (нужно еще смотреть другие меридианы!).\n");
        }

}

void MainWindow::channel_E()
{
    //Канал желудка А
        if (Channel_E == "A/2")
        {
            diagnosic_message.append("Канал желудка: повышенная кислотность желудочного сока.\n");
        }
        if (Channel_E == "A/1")
        {
            diagnosic_message.append("Канал желудка: норма.\n");
        }
        if (Channel_E == "A/0")
        {
            diagnosic_message.append("Канал желудка: норма.\n");
        }
        if (Channel_E == "A/-1")
        {
            diagnosic_message.append("Канал желудка: норма.\n");
        }
        if (Channel_E == "A/-2")
        {
            diagnosic_message.append("Канал желудка: пониженная кислотность желудочного сока.\n");
        }

    //Канал желудка В
        if (Channel_E == "B/2")
        {
            diagnosic_message.append("Канал желудка: повышенная кислотность желудочного сока.\n");
        }
        if (Channel_E == "B/1")
        {
            diagnosic_message.append("Канал желудка: норма.\n");
        }
        if (Channel_E == "B/0")
        {
            diagnosic_message.append("Канал желудка: норма.\n");
        }
        if (Channel_E == "B/-1")
        {
            diagnosic_message.append("Канал желудка: норма.\n");
        }
        if (Channel_E == "B/-2")
        {
            diagnosic_message.append("Канал желудка: пониженная кислотность желудочного сока.\n");
        }


    //Канал желудка С
        if (Channel_E == "C/2")
        {
            diagnosic_message.append("Канал желудка: гастрит с повышенной кислотностью желудочного сока.\n");
        }
        if (Channel_E == "C/1")
        {
            diagnosic_message.append("Канал желудка: гастрит с повышенной кислотностью желудочного сока.\n");
        }
        if (Channel_E == "C/0")
        {
            diagnosic_message.append("Канал желудка: непроявленное заболевание, ремиссия или предрасположенность.\n");
        }
        if (Channel_E == "C/-1")
        {
            diagnosic_message.append("Канал желудка: гастрит с пониженной кислотностью желудочного сока.\n");
        }
        if (Channel_E == "C/-2")
        {
            diagnosic_message.append("Канал желудка: гастрит с пониженной кислотностью желудочного сока.\n");
        }
        if (Channel_E == "OP")
        {
            diagnosic_message.append("Канал желудка: переедание при гастрите. Вероятность рака желудка (нужно еще смотреть другие меридианы!).\n");
        }

}

#if 0

#endif
