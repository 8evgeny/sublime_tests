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
    if (((Channel_P == "B/2")||(Channel_P == "B/-2")) &&
        ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")||(Channel_RP == "A/-2")||(Channel_RP == "B/-2")||(Channel_RP == "C/-2")))
        {
            diagnosic_message.append("Канал легких: (2мд: P/B/2,-2 + RP/ABC/2,-2) Острый ринит, евстахеит, отит.\n"
                                     "1 норма; 2 острое заболевание; -1 норма; -2 перед ремиссией.\n");
            return;
        }

    if (((Channel_P == "A/2")||(Channel_P == "A/1")||(Channel_P == "A/-1")||(Channel_P == "A/-2")) &&
        ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")||(Channel_RP == "A/-2")||(Channel_RP == "B/-2")||(Channel_RP == "C/-2")))
        {
            diagnosic_message.append("Канал легких: (2мд: P/A+RP/ABC/2,-2) Острая простуда или острое заболевание органов дыхания.\n "
                                     "1 предвестник обострения; 2 острое заболевание; -1 стихание симптомов; -2 перед ремиссией.\n");
            return;
        }

    if (((Channel_P == "C/2")||(Channel_P == "C/1")||(Channel_P == "C/-1")||(Channel_P == "C/-2")||(Channel_P == "C/0")) &&
        ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")||(Channel_RP == "A/-2")||(Channel_RP == "B/-2")||(Channel_RP == "C/-2")))
        {
            diagnosic_message.append("Канал легких: (2мд: P/C+RP/ABC/2,-2) Хронические заболевания органов дыхания.\n "
                                     "1 предвестник обострения; 2 обострение; -1 вялотекущая хроника; -2 перед ремиссией.\n");
            return;
        }

    //Канал легких A
    if (Channel_P == "A/2")
    {
        diagnosic_message.append("Канал лёгких: физиология, дискомфорт.\n");
    }
    if (Channel_P == "A/1")
    {
        diagnosic_message.append("Канал лёгких: физиология, дискомфорт.\n");
    }
   if (Channel_P == "A/0")
    {
        diagnosic_message.append("Канал лёгких: норма.\n");
    }
   if (Channel_P == "A/-1")
    {
        diagnosic_message.append("Канал лёгких: физиология, дискомфорт.\n");
    }
   if (Channel_P == "A/-2")
    {
        diagnosic_message.append("Канал лёгких: физиология, дискомфорт.\n");
    }
   if (Channel_P == "OK")
    {
        diagnosic_message.append("Канал лёгких: правосторонняя пневмония (острая).\n");
    }

//Канал легких В
    if (Channel_P == "B/2")
    {
        diagnosic_message.append("Канал лёгких: физиология, дискомфорт.\n");
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
        diagnosic_message.append("Канал лёгких: физиология, дискомфорт.\n");
    }

//Канал легких С
    if (Channel_P == "C/2")
    {
        diagnosic_message.append("Канал лёгких: физиология, дискомфорт.\n");
    }
    if (Channel_P == "C/1")
    {
        diagnosic_message.append("Канал лёгких: физиология, дискомфорт.\n");
    }
    if (Channel_P == "C/0")
    {
        diagnosic_message.append("Канал лёгких: склонность к заболеваниям органов дыхания.\n");
    }
    if (Channel_P == "C/-1")
    {
        diagnosic_message.append("Канал лёгких: физиология, дискомфорт.\n");
    }
    if (Channel_P == "C/-2")
    {
        diagnosic_message.append("Канал лёгких: физиология, дискомфорт.\n");
    }
    if (Channel_P == "OP")
    {
        diagnosic_message.append("Канал лёгких: левосторонняя пневмония (хрон.)\n");
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

    if (((Channel_MC == "A/2")||(Channel_MC == "A/1")) &&
            ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")))
        {
            diagnosic_message.append("Канал перикарда: (2мд: MC/A/1,2 + RP/ABC/2) Острые заболевания (воспаление) матки/предстательной железы.\n");
            return;
        }

    if (((Channel_MC == "A/-2")||(Channel_MC == "A/-1")) &&
            ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")))
        {
            diagnosic_message.append("Канал перикарда: (2мд: MC/A/-1,-2 + RP/ABC/2) Стихание симптомов при остром заболевании (воспаление)"
                                     "матки/предстательной железы, выздоровление.\n");
            return;
        }

    if (((Channel_MC == "OK")) &&
            ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")))
        {
            diagnosic_message.append("Канал перикарда: (2мд: MC/OK+RP/ABC/2) простатит или эндометриоз.\n");
            return;
        }

    if (((Channel_MC == "C/0")) &&
            ((Channel_TR == "C/2")||(Channel_TR == "C/1")||(Channel_TR == "C/0")||(Channel_TR == "C/-1")||(Channel_TR == "C/-2")))
        {
            diagnosic_message.append("Канал перикарда: (2мд: МС/С/0+TR/C) склонность к спазмам сосудов; И заболеваниям "
                                     "матки/предстательной железы.\n");
            return;
        }

    if (((Channel_MC == "C/1")||(Channel_MC == "C/2")) &&
            ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")))
        {
            diagnosic_message.append("Канал перикарда: (2мд: МС/С/1,2+RP/ABC/2) есть предвестник, "
                                     "или обострение хрон. заболевания - сосудов, или матки/предстательной железы.\n");
            return;
        }
    if (((Channel_MC == "C/-1")||(Channel_MC == "C/-2")) &&
            ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")))
        {
            diagnosic_message.append("Канал перикарда: (2мд: МС/С/-1,-2+RP/ABC/2) вялотекущая хроника или состояние перед ремиссией"
                                     " хрон. заболевания - сосудов, или матки/предстательной железы.\n");
            return;
        }

//Канал перикарда А
    if (Channel_MC == "A/2")
    {
        diagnosic_message.append("Канал перикарда: норма. Нервное перевозбуждение, повышенное АД, повышенное сексуальное желание.\n "
                                 "(конспект): гипертензия (сосудов), (я хочу);\n "
                                 "эмоция, легкая претензия к людям противоположного пола.\n");
    }
    if (Channel_MC == "A/1")
    {
        diagnosic_message.append("Канал перикарда: норма. Нервное перевозбуждение, повышенное АД, повышенное сексуальное желание.\n "
                                 "(конспект): гипотензия (сосудов), (я не хочу); не заболевание а физиология;\n "
                                 "эмоция, легкая претензия к людям противоположного пола.\n");
    }
    if (Channel_MC == "A/0")
    {
        diagnosic_message.append("Канал перикарда: норма.\n");
    }
    if (Channel_MC == "A/-1")
    {
        diagnosic_message.append("Канал перикарда: норма. Понижено АД.\n "
                                 "(конспект): эмоция, легкая претензия к людям противоположного пола.\n");
    }
    if (Channel_MC == "A/-2")
    {
        diagnosic_message.append("Канал перикарда: норма. Понижено АД, понижено сексуальное желание.\n "
                                 "(конспект): эмоция, легкая претензия к людям противоположного пола.\n");
    }
    if (Channel_MC == "OK")
    {
        diagnosic_message.append("Канал перикарда: может быть при эндометритах и простатитах (см.доп. другие каналы).\n");
    }

//Канал перикарда В
    if (Channel_MC == "B/2")
    {
        diagnosic_message.append("Канал перикарда: норма; повышено систолическое (верхнее) давление. Нервная система возбуждена (я хочу).\n "
                                 "(конспект): серъезная претензия к людям противоположного пола: привычка обвинять их во всех грехах.\n");
    }
    if (Channel_MC == "B/1")
    {
        diagnosic_message.append("Канал перикарда: норма.\n (конспект): серъезная претензия к людям противоположного пола: "
                                 "привычка обвинять их во всех грехах.\n");
    }
    if (Channel_MC == "B/0")
    {
        diagnosic_message.append("Канал перикарда: норма.\n");
    }
    if (Channel_MC == "B/-1")
    {
        diagnosic_message.append("Канал перикарда: норма.\n (конспект): серъезная претензия к людям противоположного пола: "
                                 "привычка обвинять их во всех грехах.\n");
    }
    if (Channel_MC == "B/-2")
    {
        diagnosic_message.append("Канал перикарда: норма; понижено систолическое (верхнее) давление, гипотония, перед сном (я не хочу).\n "
                                 "(конспект): серъезная претензия к людям противоположного пола: привычка обвинять их во всех грехах.\n");
    }

//Канал перикарда С
    if (Channel_MC == "C/2")
    {
        diagnosic_message.append("Канал перикарда: есть предвестник/легкие заболевания - сосудов, матки/предст.железы. "
                                 "Гипертония по сосудистому типу (повышены верхние цифры).\n");
    }
    if (Channel_MC == "C/1")
    {
        diagnosic_message.append("Канал перикарда: есть предвестник/легкие заболевания - сосудов; матки/предст.железы (см.еще TR).\n "
                                 "Гипертония по сосудистому типу (повышены верхние цифры).\n");
    }
    if (Channel_MC == "C/0")
    {
        diagnosic_message.append("Канал перикарда: склонность к спазмам сосудов; матки/предст.железы (см.еще TR).\n");
    }
    if (Channel_MC == "C/-1")
    {
        diagnosic_message.append("Канал перикарда: гипотония по сосудистому типу, тонус сосудов понижен.\n");
    }
    if (Channel_MC == "C/-2")
    {
        diagnosic_message.append("Канал перикарда: гипотония по сосудистому типу, тонус сосудов понижен.\n");
    }
    if (Channel_MC == "OP")
    {
        diagnosic_message.append("Канал перикарда: вероятность опухоли в органах половой системы, или их тяжелое воспаление. "
                                 "Но здесь нужно смотреть сочетания с другими меридианами!\n");
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
    if (((Channel_C == "OP")) &&
            ((Channel_TR == "C/2")||(Channel_TR == "C/1")||(Channel_TR == "C/0")||(Channel_TR == "C/-1")||(Channel_TR == "C/-2")))
        {
            diagnosic_message.append("Канал сердца: (2мд: C/OP+TR/C) возможен рак щитовидной железы.\n");
            //return;
        }
    if (((Channel_C == "C/2")||(Channel_C == "C/1")||(Channel_C == "C/0")||(Channel_C == "C/-1")||(Channel_C == "C/-2")) &&
            ((Channel_MC == "C/2")||(Channel_MC == "C/1")||(Channel_MC == "C/0")||(Channel_MC == "C/-1")||(Channel_MC == "C/-2")))
        {
            diagnosic_message.append("Канал сердца: (2мд: C/С+MC/C) ИБС.\n");
            return;
        }


//Канал сердца А
    if (Channel_C == "A/2")
    {
        diagnosic_message.append("Канал сердца: норма - физиология и дискомфорт. Тахикардия, гипертрофия левого желудочка сердца "
                                 "(спазм сосудов по БКК, возможны проблемы с внутр.органами), гипертония.\n "
                                 "Чем больше расстояние между точками - тем больше гипертрофия.\n");
    }
    if (Channel_C == "A/1")
    {
        diagnosic_message.append("Канал сердца: норма - физиология и дискомфорт. "
                                 "Склонность к тахикардии, гипертрофии левого желудочка сердца, повышению АД.\n "
                                 "Чем больше расстояние между точками - тем больше гипертрофия.\n");
    }
    if (Channel_C == "A/0")
    {
        diagnosic_message.append("Канал сердца: норма.\n");
    }
    if (Channel_C == "A/-1")
    {
        diagnosic_message.append("Канал сердца: норма - физиология и дискомфорт. "
                                 "Склонность к брадикардии, гипертрофии правого желудочка сердца (вариант нормы: спазм сосудов в МКК; "
                                 "признак проблемы в органах дыхания, а не в сердце; или раньше был спортсменом/танцором/грузчиком), "
                                 "понижению АД.\n Чем больше расстояние между точками - тем больше гипертрофия.\n");
    }
    if (Channel_C == "A/-2")
    {
        diagnosic_message.append("Канал сердца: норма - физиология и дискомфорт. "
                                 "Брадикардия, гипертрофия правого желудочка сердца (вариант нормы: спазм сосудов в МКК; "
                                 "признак проблемы в органах дыхания: а не в сердце; или раньше был спортсменом/танцором/грузчиком), "
                                 "понижено АД.\n Чем больше расстояние между точками - тем больше гипертрофия.\n");
    }
    if (Channel_C == "OK")
    {
        diagnosic_message.append("Канал сердца: недосып, диффузные изменения миокарда.\n");
    }

//Канал сердца В
    if (Channel_C == "B/2")
    {
        diagnosic_message.append("Канал сердца: норма - физиология и дискомфорт. Тахикардия, повышено диастолическое давление.\n");
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
   if (Channel_C == "B/-2")
    {
        diagnosic_message.append("Канал сердца: норма - физиология и дискомфорт. Брадикардия, понижено диастолическое давление.\n");
    }

//Канал сердца С
    if (Channel_C == "C/2")
    {
        diagnosic_message.append("Канал сердца: тахикардия, гипертрофия правого желудочка сердца (вариант нормы: спазм сосудов "
                                 "в МКК; признак проблемы в органах дыхания, а не в сердце; или раньше был "
                                 "спортсменом/танцором/грузчиком), повышено АД. Больше эмоции, чем болезнь.\n "
                                 "Чем больше расстояние между точками - тем больше гипертрофия.\n");
    }
    if (Channel_C == "C/1")
    {
        diagnosic_message.append("Канал сердца: тахикардия, гипертония, склонность к гипертрофии правого желудочка сердца "
                                 "(вариант нормы: спазм сосудов в МКК; признак проблемы в органах дыхания, а не в сердце; "
                                 "или раньше был спортсменом/танцором/грузчиком). Больше эмоции, чем болезнь.\n  "
                                 "Чем больше расстояние между точками - тем больше гипертрофия.\n");
    }
    if (Channel_C == "C/0")
    {
        diagnosic_message.append("Канал сердца: норма.\n");
    }
    if (Channel_C == "C/-1")
    {
        diagnosic_message.append("Канал сердца: брадикардия, гипотония, склонность к гипертрофии левого желудочка сердца "
                                 "(спазм сосудов по БКК, возможны проблемы с внутр.органами).Больше эмоции, чем болезнь.\n "
                                 "Чем больше расстояние между точками - тем больше гипертрофия.\n");
    }
    if (Channel_C == "C/-2")
    {
        diagnosic_message.append("Канал сердца: брадикардия, гипотония, гипертрофия левого желудочка сердца (спазм сосудов по"
                                 " БКК, возможны проблемы с внутр.органами); переходное состояние из гипотонии в гипертонию. "
                                 "Больше эмоции, чем болезнь.\n Чем больше расстояние между точками - тем больше гипертрофия.\n");
    }
    if (Channel_C == "OP")
    {
        diagnosic_message.append("Канал сердца: выход сильнейшего эмоционального стресса.\n");
    }
//Закрашиваем треугольники
    if (Channel_C.find_first_of('0') == string::npos ) //Обе точки не в коридоре
    {
        if (Channel_C.find("-2") != string::npos)//Обе точки ниже
        {
            scene->addEllipse(294, 772, 8, 8, penTriangle);
            scene->addEllipse(351, 772, 8, 8, penTriangle);
        }
        if (Channel_C.find("A/-1") != string::npos)//левая ниже
        {
            scene->addEllipse(294, 772, 8, 8, penTriangle);
        }
        if (Channel_C.find("C/-1") != string::npos)//правая ниже
        {
            scene->addEllipse(351, 772, 8, 8, penTriangle);
        }
        if (Channel_C.find("/2") != string::npos)//Обе точки выше
        {
            scene->addEllipse(294, 795, 8, 8, penTriangle);
            scene->addEllipse(351, 795, 8, 8, penTriangle);
        }
        if (Channel_C.find("A/1") != string::npos)//правая выше
        {
            scene->addEllipse(351, 795, 8, 8, penTriangle);
        }
        if (Channel_C.find("C/1") != string::npos)//левая выше
        {
            scene->addEllipse(294, 795, 8, 8, penTriangle);
        }
        if (Channel_C.find("OP") != string::npos)//левая выше  правая ниже
        {
            scene->addEllipse(294, 795, 8, 8, penTriangle);
            scene->addEllipse(351, 772, 8, 8, penTriangle);
        }
        if (Channel_C.find("OK") != string::npos)//левая ниже  правая выше
        {
            scene->addEllipse(294, 772, 8, 8, penTriangle);
            scene->addEllipse(351, 795, 8, 8, penTriangle);
        }
    }//triangles
}

void MainWindow::channel_IG()
{

//Или 1 или 2
    bool one_or_two = false;
    if (((Channel_IG == "C/2")||(Channel_IG == "C/1")||(Channel_IG == "C/-1")||(Channel_IG == "C/-2")) &&
            ((Channel_P == "C/2")||(Channel_P == "C/1")||(Channel_P == "C/0")||(Channel_P == "C/-1")||(Channel_P == "C/-2")))
        {
            one_or_two = true;
            diagnosic_message.append("Канал тонк.киш.: (2мд: IG/C+P/C) дуоденит - воспаление 12-ти перстной кишки.\n");
        }
    if (((Channel_IG == "C/2")||(Channel_IG == "C/1")||(Channel_IG == "C/0")||(Channel_IG == "C/-1")||(Channel_IG == "C/-2")) &&
            ((Channel_C == "C/2")||(Channel_C == "C/1")||(Channel_C == "C/0")||(Channel_C == "C/-1")||(Channel_C == "C/-2")))
        {
            one_or_two = true;
            diagnosic_message.append("Канал тонк.киш.: (2мд: IG/C+C/C) илио-кардиальный синдром.\n "
                                     "Редкое заболевание: проблемы с сердцем из-за отравленной пищи в тонком кишечнике - нужно убрать интоксикацию.\n "
                                     "Таким людям нужно кушать только проверенную качественную пищу.\n");
        }
    if (one_or_two)
        return;

//Канал тонкого кишечника А
    if (Channel_IG == "A/2")
    {
        diagnosic_message.append("Канал тонк.киш.: через 3 часа после приема пищи.\n");
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
    if (Channel_IG == "OK")
    {
        diagnosic_message.append("Канал тонк.киш.: переел 2 часа назад.\n");
    }

//Канал тонкого кишечника B
    if (Channel_IG == "B/2")
    {
        diagnosic_message.append("Канал тонк.киш.: через 3 часа после приема пищи.\n "
                                 "Здесь съел мало еды; часто мясоеды; когда голодаем.\n");
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
        diagnosic_message.append("Канал тонк.киш.: эмоция - неприятие человека или ситуации.\n");
    }
    if (Channel_IG == "C/1")
    {
        diagnosic_message.append("Канал тонк.киш.: эмоция - неприятие человека или ситуации.\n");
    }
    if (Channel_IG == "C/0")
    {
        diagnosic_message.append("Канал тонк.киш.: склонность к заболеваниям 12-ти перстной кишки; "
                                 "эмоция - неприятие человека или ситуации.\n");
    }
    if (Channel_IG == "C/-1")
    {
        diagnosic_message.append("Канал тонк.киш.: эмоция - неприятие человека или ситуации.\n");
    }
    if (Channel_IG == "C/-2")
    {
        diagnosic_message.append("Канал тонк.киш.: эмоция - неприятие человека или ситуации.\n");
    }
    if (Channel_IG == "OP")
    {
        diagnosic_message.append("Канал тонк.киш.: через 2-3 часа после переедания при дуодените;\n "
                                 "или вероятность рака 12-ти перстной кишки (нужно дополнительно смотреть состояние других меридианов!) .\n");
    }
//Закрашиваем треугольники
    if (Channel_IG.find_first_of('0') == string::npos ) //Обе точки не в коридоре
    {
        if (Channel_IG.find("-2") != string::npos)//Обе точки ниже
        {
            scene->addEllipse(380, 772, 8, 8, penTriangle);
            scene->addEllipse(435, 772, 8, 8, penTriangle);
        }
        if (Channel_IG.find("A/-1") != string::npos)//левая ниже
        {
            scene->addEllipse(380, 772, 8, 8, penTriangle);
        }
        if (Channel_IG.find("C/-1") != string::npos)//правая ниже
        {
            scene->addEllipse(435, 772, 8, 8, penTriangle);
        }
        if (Channel_IG.find("/2") != string::npos)//Обе точки выше
        {
            scene->addEllipse(380, 795, 8, 8, penTriangle);
            scene->addEllipse(435, 795, 8, 8, penTriangle);
        }
        if (Channel_IG.find("A/1") != string::npos)//правая выше
        {
            scene->addEllipse(435, 795, 8, 8, penTriangle);
        }
        if (Channel_IG.find("C/1") != string::npos)//левая выше
        {
            scene->addEllipse(380, 795, 8, 8, penTriangle);
        }
        if (Channel_IG.find("OP") != string::npos)//левая выше  правая ниже
        {
            scene->addEllipse(380, 795, 8, 8, penTriangle);
            scene->addEllipse(435, 772, 8, 8, penTriangle);
        }
        if (Channel_IG.find("OK") != string::npos)//левая ниже  правая выше
        {
            scene->addEllipse(380, 772, 8, 8, penTriangle);
            scene->addEllipse(435, 795, 8, 8, penTriangle);
        }
    }//triangles
}

void MainWindow::channel_TR()
{
//Канал тройного обогревателя А
    if (Channel_TR == "A/2")
    {
        diagnosic_message.append("Канал 3 обогревателя: физическое пернапряжение, избыток физической энергии\n");
    }
    if (Channel_TR == "A/1")
    {
        diagnosic_message.append("Канал 3 обогревателя: норма, возможен избыток физической энергии.\n");
    }
    if (Channel_TR == "A/0")
    {
        diagnosic_message.append("Канал 3 обогревателя: норма.\n");
    }
    if (Channel_TR == "A/-1")
    {
        diagnosic_message.append("Канал 3 обогревателя: усталость.\n");
    }
    if (Channel_TR == "A/-2")
    {
        diagnosic_message.append("Канал 3 обогревателя: физическое утомление.\n");
    }
    if (Channel_TR == "OK")
    {
        diagnosic_message.append("Канал 3 обогревателя: дисфункция гормональной системы (сглаз).\n "
                                 "Три тела человека находятся в раздрае.\n");
    }

//Канал тройного обогревателя В
    if (Channel_TR == "B/2")
    {
        diagnosic_message.append("Канал 3 обогревателя: ПЕРЕизбыток энергии.\n Человек сильный физически.\n");
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
        diagnosic_message.append("Канал 3 обогревателя: усталость, физическое переутомление.\n "
                                 "Но человек может быть сильным физически.\n");
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
//Закрашиваем треугольники
    if (Channel_TR.find_first_of('0') == string::npos ) //Обе точки не в коридоре
    {
        if (Channel_TR.find("-2") != string::npos)//Обе точки ниже
        {
            scene->addEllipse(466, 772, 8, 8, penTriangle);
            scene->addEllipse(520, 772, 8, 8, penTriangle);
        }
        if (Channel_TR.find("A/-1") != string::npos)//левая ниже
        {
            scene->addEllipse(466, 772, 8, 8, penTriangle);
        }
        if (Channel_TR.find("C/-1") != string::npos)//правая ниже
        {
            scene->addEllipse(520, 772, 8, 8, penTriangle);
        }
        if (Channel_TR.find("/2") != string::npos)//Обе точки выше
        {
            scene->addEllipse(466, 795, 8, 8, penTriangle);
            scene->addEllipse(520, 795, 8, 8, penTriangle);
        }
        if (Channel_TR.find("A/1") != string::npos)//правая выше
        {
            scene->addEllipse(520, 795, 8, 8, penTriangle);
        }
        if (Channel_TR.find("C/1") != string::npos)//левая выше
        {
            scene->addEllipse(466, 795, 8, 8, penTriangle);
        }
        if (Channel_TR.find("OP") != string::npos)//левая выше  правая ниже
        {
            scene->addEllipse(466, 795, 8, 8, penTriangle);
            scene->addEllipse(520, 772, 8, 8, penTriangle);
        }
        if (Channel_TR.find("OK") != string::npos)//левая ниже  правая выше
        {
            scene->addEllipse(466, 772, 8, 8, penTriangle);
            scene->addEllipse(520, 795, 8, 8, penTriangle);
        }
    }//triangles
}

void MainWindow::channel_GI()
{
    if (((Channel_GI == "C/1")||(Channel_GI == "C/-1")) &&
            ((Channel_P == "C/2")||(Channel_P == "C/1")||(Channel_P == "C/0")||(Channel_P == "C/-1")||(Channel_P == "C/-2")))
        {
            diagnosic_message.append("Канал толс.киш.: (2мд: GI/C+P/C) колит - воспаление толстой кишки.\n");
            return;
        }
    if (((Channel_GI == "C/2")) &&
            ((Channel_P == "C/2")||(Channel_P == "C/1")||(Channel_P == "C/0")||(Channel_P == "C/-1")||(Channel_P == "C/-2")))
        {
            diagnosic_message.append("Канал толс.киш.: (2мд: GI/C+P/C) колит - воспаление толстой кишки; с избыточной дефекацией.\n");
            return;
        }

    if (((Channel_GI == "C/-2")) &&
            ((Channel_P == "C/2")||(Channel_P == "C/1")||(Channel_P == "C/0")||(Channel_P == "C/-1")||(Channel_P == "C/-2")))
        {
            diagnosic_message.append("Канал толс.киш.: (2мд: GI/C+P/C) колит - воспаление толстой кишки; с запорами.\n");
            return;
        }
    if (((Channel_GI == "OP")) &&
            ((Channel_P == "C/2")||(Channel_P == "C/1")||(Channel_P == "C/0")||(Channel_P == "C/-1")||(Channel_P == "C/-2")))
        {
            diagnosic_message.append("Канал толс.киш.: (2мд: GI/C+P/C) колит - воспаление толстой кишки; "
                                     "с переизбытком каловых масс. Возможно рак.\n");
            return;
        }

//Канал толстого кишечника А
    if (Channel_GI == "A/2")
    {
        diagnosic_message.append("Канал толст.киш.: усиление перистальтики толстого кишечника.\n "
                                 "Метеоризм (см расстояние между точками).\n");
    }
    if (Channel_GI == "A/1")
    {
        diagnosic_message.append("Канал толст.киш.: небольшое усиление функции толстого кишечника.\n "
                                 "Метеоризм (см расстояние между точками).\n");
    }
    if (Channel_GI == "A/0")
    {
        diagnosic_message.append("Канал толст.киш.: норма.\n  Метеоризм (см расстояние между точками).\n");
    }
    if (Channel_GI == "A/-1")
    {
        diagnosic_message.append("Канал толст.киш.: склонность к неполному опорожнению кишечника.\n "
                                 "Метеоризм (см расстояние между точками).\n");
    }
    if (Channel_GI == "A/-2")
    {
        diagnosic_message.append("Канал толст.киш.: запор на нервной почве.\n Метеоризм (см расстояние между точками).\n");
    }
    if (Channel_GI == "OK")
    {
        diagnosic_message.append("Канал толст.киш.: сильный метеоризм.\n");
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
    if (Channel_GI == "B/0")
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
        diagnosic_message.append("Канал толст.киш.: усиление перистальтики толстого кишечника.\n");
    }
    if (Channel_GI == "C/1")
    {
        diagnosic_message.append("Канал толст.киш.: небольшое усиление перистальтики толстого кишечника.\n");
    }
    if (Channel_GI == "C/0")
    {
        diagnosic_message.append("Канал толст.киш.: эмоции; склонность к заболеваниям толстого кишечника.\n");
    }
    if (Channel_GI == "C/-1")
    {
        diagnosic_message.append("Канал толст.киш.: эмоции; склонность к заболеваниям толстого кишечника.\n");
    }
    if (Channel_GI == "C/-2")
    {
        diagnosic_message.append("Канал толст.киш.: эмоции; склонность к заболеваниям толстого кишечника.\n");
    }
    if (Channel_GI == "OP")
    {
        diagnosic_message.append("Канал толст.киш.: метеоризм; избыток содержимого; "
                                 "вероятность рака толстой кишки (нужно уточнять другие меридианы!).\n");
    }
//Закрашиваем треугольники
    if (Channel_GI.find_first_of('0') == string::npos ) //Обе точки не в коридоре
    {
        if (Channel_GI.find("-2") != string::npos)//Обе точки ниже
        {
            scene->addEllipse(551, 772, 8, 8, penTriangle);
            scene->addEllipse(606, 772, 8, 8, penTriangle);
        }
        if (Channel_GI.find("A/-1") != string::npos)//левая ниже
        {
            scene->addEllipse(551, 772, 8, 8, penTriangle);
        }
        if (Channel_GI.find("C/-1") != string::npos)//правая ниже
        {
            scene->addEllipse(606, 772, 8, 8, penTriangle);
        }
        if (Channel_GI.find("/2") != string::npos)//Обе точки выше
        {
            scene->addEllipse(551, 795, 8, 8, penTriangle);
            scene->addEllipse(606, 795, 8, 8, penTriangle);
        }
        if (Channel_GI.find("A/1") != string::npos)//правая выше
        {
            scene->addEllipse(606, 795, 8, 8, penTriangle);
        }
        if (Channel_GI.find("C/1") != string::npos)//левая выше
        {
            scene->addEllipse(551, 795, 8, 8, penTriangle);
        }
        if (Channel_GI.find("OP") != string::npos)//левая выше  правая ниже
        {
            scene->addEllipse(551, 795, 8, 8, penTriangle);
            scene->addEllipse(606, 772, 8, 8, penTriangle);
        }
        if (Channel_GI.find("OK") != string::npos)//левая ниже  правая выше
        {
            scene->addEllipse(551, 772, 8, 8, penTriangle);
            scene->addEllipse(606, 795, 8, 8, penTriangle);
        }
    }//triangles
}

void MainWindow::channel_RP()
{

    //Или 1 или 2
        bool one_or_two = false;
        if (((Channel_RP == "C/-2")) &&
                ((Channel_TR == "C/-2")))
            {
                one_or_two = true;
                diagnosic_message.append("Канал селезенки: (2мд: RP/C/-2 +TR/C/-2) иммунодефицит.\n");
            }
        if (((Channel_RP == "C/-2")||(Channel_RP == "B/-2")||(Channel_RP == "A/-2")) && //понижен сахар
                ((Channel_V == "A/-2")||(Channel_V == "B/-2")||(Channel_V == "C/-2")) && //мозг не соображает
                       ((Channel_E == "A/2")||(Channel_E == "B/2")||(Channel_E == "C/2")))  //повышена кислотность
            {
                one_or_two = true;
                diagnosic_message.append("Канал селезенки: (3мд: RP/ABC/-2 + V/ABC/-2 + E/ABC/2) сахар понижен, человек голодный.\n");
            }
        if (one_or_two)
            return;

//Канал селезенки и поджелудочной А
    if (Channel_RP == "A/2")
    {
        diagnosic_message.append("Канал селезенки: повышен сахар и иммунитет, лейкоцитоз, селезенка работает в напряженном режиме.\n");
    }
    if (Channel_RP == "A/1")
    {
        diagnosic_message.append("Канал селезенки: начинает повышаться сахар в крови, иммунитет повышен.\n");
    }
    if (Channel_RP == "A/0")
    {
        diagnosic_message.append("Канал селезенки: сахар и иммунитет - норма.\n");
    }
    if (Channel_RP == "A/-1")
    {
        diagnosic_message.append("Канал селезенки: понижен сахар в крови, иммунитет в норме.\n");
    }
    if (Channel_RP == "A/-2")
    {
        diagnosic_message.append("Канал селезенки: понижен сахар и иммунитет, или состояние голода.\n");
    }
    if (Channel_RP == "OK")
    {
        diagnosic_message.append("Канал селезенки: сахар низкий, иммунитет высокий; возможно переходное состояние в панкреатит.\n");
    }

//Канал селезенки и поджелудочной В
    if (Channel_RP == "B/2")
    {
        diagnosic_message.append("Канал селезенки: сахар повышен, иммунитет повышен.\n");
    }
    if (Channel_RP == "B/1")
    {
        diagnosic_message.append("Канал селезенки: сахар и иммунитет - норма.\n");
    }
    if (Channel_RP == "B/0")
    {
        diagnosic_message.append("Канал селезенки: сахар и иммунитет - норма.\n");
    }
    if (Channel_RP == "B/-1")
    {
        diagnosic_message.append("Канал селезенки: сахар и иммунитет - норма.\n");
    }
    if (Channel_RP == "B/-2")
    {
        diagnosic_message.append("Канал селезенки: сахар понижен, или состояние голода.\n");
    }

//Канал селезенки и поджелудочной С
    if (Channel_RP == "C/2")
    {
        diagnosic_message.append("Канал селезенки: проблемы в поджелудочной (обострение хронического панкреатита), "
                                 "лейкоцитоз, сдвиг лейкоцитарной формулы влево.\n");
    }
    if (Channel_RP == "C/1")
    {
        diagnosic_message.append("Канал селезенки: начальные проявления панкреатита.\n");
    }
    if (Channel_RP == "C/0")
    {
        diagnosic_message.append("Канал селезенки: склонность к заболеваниям поджелудочной железы.\n");
    }
    if (Channel_RP == "C/-1")
    {
        diagnosic_message.append("Канал селезенки: хроническое заболевание селезенки; (увеличение).\n");
    }
    if (Channel_RP == "C/-2")
    {
        diagnosic_message.append("Канал селезенки: заболевание селезенки; или гипогликемия, лейкопения; \n "
                                 "вероятность тяжелого поражения, рак (нужно смотреть другие меридианы!)\n");
    }
    if (Channel_RP == "OP")
    {
        diagnosic_message.append("Канал селезенки: предрак, или состояние рака поджелудочной железы или селезенки "
                                 "(нужно смотреть другие меридианы!) \n");
    }
//Закрашиваем треугольники
    if (Channel_RP.find_first_of('0') == string::npos ) //Обе точки не в коридоре
    {
        if (Channel_RP.find("-2") != string::npos)//Обе точки ниже
        {
            scene->addEllipse(638, 772, 8, 8, penTriangle);
            scene->addEllipse(692, 772, 8, 8, penTriangle);
        }
        if (Channel_RP.find("A/-1") != string::npos)//левая ниже
        {
            scene->addEllipse(638, 772, 8, 8, penTriangle);
        }
        if (Channel_RP.find("C/-1") != string::npos)//правая ниже
        {
            scene->addEllipse(692, 772, 8, 8, penTriangle);
        }
        if (Channel_RP.find("/2") != string::npos)//Обе точки выше
        {
            scene->addEllipse(638, 795, 8, 8, penTriangle);
            scene->addEllipse(692, 795, 8, 8, penTriangle);
        }
        if (Channel_RP.find("A/1") != string::npos)//правая выше
        {
            scene->addEllipse(692, 795, 8, 8, penTriangle);
        }
        if (Channel_RP.find("C/1") != string::npos)//левая выше
        {
            scene->addEllipse(638, 795, 8, 8, penTriangle);
        }
        if (Channel_RP.find("OP") != string::npos)//левая выше  правая ниже
        {
            scene->addEllipse(638, 795, 8, 8, penTriangle);
            scene->addEllipse(692, 772, 8, 8, penTriangle);
        }
        if (Channel_RP.find("OK") != string::npos)//левая ниже  правая выше
        {
            scene->addEllipse(638, 772, 8, 8, penTriangle);
            scene->addEllipse(692, 795, 8, 8, penTriangle);
        }
    }//triangles
}

void MainWindow::channel_F()
{

    if (((Channel_F == "A/2")||(Channel_F == "A/1")||(Channel_F == "A/-1")||(Channel_F == "A/-2")) &&
            ((Channel_RP == "C/2")||(Channel_RP == "B/2")||(Channel_RP == "A/2")))
        {
            diagnosic_message.append("Канал печени: (2мд: F/A+RP/ABC/2) острый гепатит ( особенно А/2,-2).\n");
            return;
        }

    if (((Channel_F == "C/2")) &&
            ((Channel_RP == "C/2")||(Channel_RP == "B/2")||(Channel_RP == "A/2")))
        {
            diagnosic_message.append("Канал печени: (2мд: F/C+RP/ABC/2) гепатит.\n");
            return;
        }


//Канал печени А
    if (Channel_F == "A/2")
    {
        diagnosic_message.append("Канал печени: избыток лекарственных препаратов или пищевых добавок.\n "
                                 "Печень в критическом состоянии, ее пора чистить - иначе перейдет в С.\n");
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
        diagnosic_message.append("Канал печени: вероятность недавнего приема кофе, крепкого чая, алкоголя, лекарств.\n");
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
        diagnosic_message.append("Канал печени: человек мало есть жирного, соленого, острого. Функция печени понижена.\n");
    }

//Канал печени С
    if (Channel_F == "C/2")
    {
        diagnosic_message.append("Канал печени: гепатоз.\n");
    }
    if (Channel_F == "C/1")
    {
        diagnosic_message.append("Канал печени: обострение хронического гепатита.\n");
    }
    if (Channel_F == "C/0")
    {
        diagnosic_message.append("Канал печени: склонность к заболеванию печени.\n");
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
//Закрашиваем треугольники
    if (Channel_F.find_first_of('0') == string::npos ) //Обе точки не в коридоре
    {
        if (Channel_F.find("-2") != string::npos)//Обе точки ниже
        {
            scene->addEllipse(724, 772, 8, 8, penTriangle);
            scene->addEllipse(779, 772, 8, 8, penTriangle);
        }
        if (Channel_F.find("A/-1") != string::npos)//левая ниже
        {
            scene->addEllipse(724, 772, 8, 8, penTriangle);
        }
        if (Channel_F.find("C/-1") != string::npos)//правая ниже
        {
            scene->addEllipse(779, 772, 8, 8, penTriangle);
        }
        if (Channel_F.find("/2") != string::npos)//Обе точки выше
        {
            scene->addEllipse(724, 795, 8, 8, penTriangle);
            scene->addEllipse(779, 795, 8, 8, penTriangle);
        }
        if (Channel_F.find("A/1") != string::npos)//правая выше
        {
            scene->addEllipse(779, 795, 8, 8, penTriangle);
        }
        if (Channel_F.find("C/1") != string::npos)//левая выше
        {
            scene->addEllipse(724, 795, 8, 8, penTriangle);
        }
        if (Channel_F.find("OP") != string::npos)//левая выше  правая ниже
        {
            scene->addEllipse(724, 795, 8, 8, penTriangle);
            scene->addEllipse(779, 772, 8, 8, penTriangle);
        }
        if (Channel_F.find("OK") != string::npos)//левая ниже  правая выше
        {
            scene->addEllipse(724, 772, 8, 8, penTriangle);
            scene->addEllipse(779, 795, 8, 8, penTriangle);
        }
    }//triangles
}

void MainWindow::channel_R()
{
    if (((Channel_R == "C/2")||(Channel_R == "C/1")||(Channel_R == "C/0")||(Channel_R == "C/-1")||(Channel_R == "C/-2")) &&
            ((Channel_VB == "A/2")||(Channel_VB == "A/1")||(Channel_VB == "A/0")||(Channel_VB == "A/-1")||(Channel_VB == "A/-2")))
        {
            diagnosic_message.append("Канал почек: (2мд: R/C +VB/A) опущение почки.\n");
            //return;
        }
    if (((Channel_R == "C/2")||(Channel_R == "C/1")||(Channel_R == "C/0")||(Channel_R == "C/-1")||(Channel_R == "C/-2")) &&
            ((Channel_VB == "C/2")||(Channel_VB == "C/1")||(Channel_VB == "C/0")||(Channel_VB == "C/-1")||(Channel_VB == "C/-2")))
        {
            diagnosic_message.append("Канал почек: (2мд: R/C +VB/С) песок/камни в почках.\n");
            //return;
        }

    if (((Channel_R == "C/2")||(Channel_R == "C/1")) &&
            ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")||(Channel_RP == "A/-2")||(Channel_RP == "B/-2")||(Channel_RP == "C/-2")))
        {
            diagnosic_message.append("Канал почек: (2мд: R/C/2,1 +RP/ABC/2,-2) хроническое воспаление правой почки.\n");
            return;
        }
    if (((Channel_R == "C/-2")||(Channel_R == "C/-1")) &&
            ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")||(Channel_RP == "A/-2")||(Channel_RP == "B/-2")||(Channel_RP == "C/-2")))
        {
            diagnosic_message.append("Канал почек: (2мд: R/C/-2,-1 +RP/ABC/2,-2) хроническое воспаление левой почки.\n");
            return;
        }

    if (((Channel_R == "B/2")) &&
            ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")))
        {
            diagnosic_message.append("Канал почек: (2мд: R/B/2+RP/ABC/2) усиленное мочеиспускание и 2х сторонний нефрит.\n");
            return;
        }
    if (((Channel_R == "B/-2")) &&
            ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")))
        {
            diagnosic_message.append("Канал почек: (2мд: R/B/-2 +RP/ABC/2) отеки и 2х сторонний нефрит.\n");
            return;
        }

    if (((Channel_R == "A/2")||(Channel_R == "A/1")) &&
            ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")))
        {
            diagnosic_message.append("Канал почек: (2мд: R/A/2,1 +RP/ABC/2) острый левосторонний нефрит.\n");
            return;
        }
    if (((Channel_R == "A/-2")||(Channel_R == "A/-1")) &&
            ((Channel_RP == "A/2")||(Channel_RP == "B/2")||(Channel_RP == "C/2")))
        {
            diagnosic_message.append("Канал почек: (2мд: R/A/-2,-1 +RP/ABC/2) острый правосторонний нефрит.\n");
            return;
        }

//Канал почек А
    if (Channel_R == "A/2")
    {
        diagnosic_message.append("Канал почек: усиленное мочеиспускание,за счет левой почки; "
                                 "вероятность приема мочегонных препаратов.\n");
    }
    if (Channel_R == "A/1")
    {
        diagnosic_message.append("Канал почек: небольшое усиление мочеиспускания, за счет левой почки.\n");
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
        diagnosic_message.append("Канал почек: отёки, вероятность камня в правой почке, опущение правой почки.\n");
    }
    if (Channel_R == "OK")
    {
        diagnosic_message.append("Канал почек: вероятность отказа правой почки (камни, сморщенная почка, рак, отсутствие почки).\n");
    }

//Канал почек В
    if (Channel_R == "B/2")
    {
        diagnosic_message.append("Канал почек: усиленное мочеиспускание, вероятность приема мочегонных препаратов.\n "
                                 "Человек много пил воды, или болел 3 дня назад и почки выводят инфекцию.\n");
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
        diagnosic_message.append("Канал почек: отёки (функциональные) - но почему сказать не можем;\n "
                                 "вероятность присутствия камней в обеих почках, опущение почек.\n");
    }

//Канал почек С
    if (Channel_R == "C/2")
    {
        diagnosic_message.append("Канал почек: начало мочекаменной болезни. Усиленное мочеиспускание,за счет левой почки.\n");
    }
    if (Channel_R == "C/1")
    {
        diagnosic_message.append("Канал почек: начало мочекаменной болезни. Усиленное мочеиспускание,за счет левой почки.\n");
    }
    if (Channel_R == "C/0")
    {
        diagnosic_message.append("Канал почек: норма.\n");
    }
    if (Channel_R == "C/-1")
    {
        diagnosic_message.append("Канал почек: пониженное мочеиспускание и отёки, за счет левой почки;\n "
                                 "вероятность камня в левой почке, или опущение левой почки.\n");
    }
    if (Channel_R == "C/-2")
    {
        diagnosic_message.append("Канал почек:  пониженное мочеиспускание и отёки, за счет левой почки;\n "
                                 "вероятность камня в левой почке, или опущение левой почки, воспаление.\n");
    }
    if (Channel_R == "OP")
    {
        diagnosic_message.append("Канал почек: вероятность отключения левой почки, почему то она не работает;\n "
                                 "она отсутствут, камни, рак (нужно еще смотреть другие меридианы!).\n");
    }
//Закрашиваем треугольники
    if (Channel_R.find_first_of('0') == string::npos ) //Обе точки не в коридоре
    {
        if (Channel_R.find("-2") != string::npos)//Обе точки ниже
        {
            scene->addEllipse(809, 772, 8, 8, penTriangle);
            scene->addEllipse(865, 772, 8, 8, penTriangle);
        }
        if (Channel_R.find("A/-1") != string::npos)//левая ниже
        {
            scene->addEllipse(809, 772, 8, 8, penTriangle);
        }
        if (Channel_R.find("C/-1") != string::npos)//правая ниже
        {
            scene->addEllipse(865, 772, 8, 8, penTriangle);
        }
        if (Channel_R.find("/2") != string::npos)//Обе точки выше
        {
            scene->addEllipse(809, 795, 8, 8, penTriangle);
            scene->addEllipse(865, 795, 8, 8, penTriangle);
        }
        if (Channel_R.find("A/1") != string::npos)//правая выше
        {
            scene->addEllipse(865, 795, 8, 8, penTriangle);
        }
        if (Channel_R.find("C/1") != string::npos)//левая выше
        {
            scene->addEllipse(809, 795, 8, 8, penTriangle);
        }
        if (Channel_R.find("OP") != string::npos)//левая выше  правая ниже
        {
            scene->addEllipse(809, 795, 8, 8, penTriangle);
            scene->addEllipse(865, 772, 8, 8, penTriangle);
        }
        if (Channel_R.find("OK") != string::npos)//левая ниже  правая выше
        {
            scene->addEllipse(809, 772, 8, 8, penTriangle);
            scene->addEllipse(865, 795, 8, 8, penTriangle);
        }
    }//triangles
}

void MainWindow::channel_V()
{
    if (((Channel_V == "OP")) &&
            ((Channel_IG == "C/2")||(Channel_IG == "C/1")||(Channel_IG == "C/0")||(Channel_IG == "C/-1")||(Channel_IG == "C/-2")))
        {
            diagnosic_message.append("Канал мочевого пузыря: (2мд: V/OP+IG/C) стресс; возможно рак мозга.\n");
            return;
        }
    if (((Channel_V == "OP")) &&
            ((Channel_R == "C/2")||(Channel_R == "C/1")||(Channel_R == "C/0")||(Channel_R == "C/-1")||(Channel_R == "C/-2")))
        {
            diagnosic_message.append("Канал мочевого пузыря: (2мд: V/OP+R/C) стресс; возможно рак мочевого пузыря.\n");
            return;
        }
    if (((Channel_V == "OP")) &&
            ((Channel_VB == "C/2")||(Channel_VB == "C/1")||(Channel_VB == "C/0")||(Channel_VB == "C/-1")||(Channel_VB == "C/-2")))
        {
            diagnosic_message.append("Канал мочевого пузыря: (2мд: V/OP+VB/C) стресс; возможно рак костей.\n");
            return;
        }

//Канал мочевого пузыря А
    if (Channel_V == "A/2")
    {
        diagnosic_message.append("Канал мочевого пузыря: умственное перевозбуждение.\n "
                                 "Больше напрягается левое полушарие мозга: технарь.\n");
    }
    if (Channel_V == "A/1")
    {
        diagnosic_message.append("Канал мочевого пузыря: норма.\n Больше напрягается левое полушарие мозга: технарь.\n");
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
        diagnosic_message.append("Канал мочевого пузыря: переутомление нервной системы,\n "
                                 "пониженная работоспособность мозга (например при переутомлении или голоде).\n");
    }
    if (Channel_V == "OK")
    {
        diagnosic_message.append("Канал мочевого пузыря: переполнение мочевого пузыря.\n");
    }

//Канал мочевого пузыря В
    if (Channel_V == "B/2")
    {
        diagnosic_message.append("Канал мочевого пузыря: напряжение нервной системы.\n "
                                 "Универсальное мышление: работают и левое и правое полушрия мозга.\n");
    }
    if (Channel_V == "B/1")
    {
        diagnosic_message.append("Канал мочевого пузыря: норма.\n "
                                 "Универсальное мышление: работают и левое и правое полушрия мозга.\n");
    }
    if (Channel_V == "B/0")
    {
        diagnosic_message.append("Канал мочевого пузыря: норма.\n "
                                 "Универсальное мышление: работают и левое и правое полушрия мозга.\n");
    }
    if (Channel_V == "B/-1")
    {
        diagnosic_message.append("Канал мочевого пузыря: норма.\n "
                                 "Универсальное мышление: работают и левое и правое полушрия мозга.\n");
    }
    if (Channel_V == "B/2")
    {
        diagnosic_message.append("Канал мочевого пузыря: утомление нервной системы, пониженная работоспособность мозга "
                                 "(например при усталости или голоде).\n "
                                 "Универсальное мышление: работают и левое и правое полушрия мозга.\n");
    }

//Канал мочевого пузыря С
    if (Channel_V == "C/2")
    {
        diagnosic_message.append("Канал мочевого пузыря: эмоциональное перевозбуждение.\n "
                                 "Больше напрягается правое полушарие мозга: гуманитарий.\n");
    }
    if (Channel_V == "C/1")
    {
        diagnosic_message.append("Канал мочевого пузыря: норма.\n "
                                 "Больше напрягается правое полушарие мозга: гуманитарий.\n");
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
        diagnosic_message.append("Канал мочевого пузыря: переутомление нервной системы, пониженная работоспособность мозга "
                                 "(например при усталости или голоде).\n");
    }
    if (Channel_V == "OP")
    {
        diagnosic_message.append("Канал мочевого пузыря: стресс, избыток мочи, возможно инфекция.\n");
    }
//Закрашиваем треугольники
    if (Channel_V.find_first_of('0') == string::npos ) //Обе точки не в коридоре
    {
        if (Channel_V.find("-2") != string::npos)//Обе точки ниже
        {
            scene->addEllipse(896, 772, 8, 8, penTriangle);
            scene->addEllipse(951, 772, 8, 8, penTriangle);
        }
        if (Channel_V.find("A/-1") != string::npos)//левая ниже
        {
            scene->addEllipse(896, 772, 8, 8, penTriangle);
        }
        if (Channel_V.find("C/-1") != string::npos)//правая ниже
        {
            scene->addEllipse(951, 772, 8, 8, penTriangle);
        }
        if (Channel_V.find("/2") != string::npos)//Обе точки выше
        {
            scene->addEllipse(896, 795, 8, 8, penTriangle);
            scene->addEllipse(951, 795, 8, 8, penTriangle);
        }
        if (Channel_V.find("A/1") != string::npos)//правая выше
        {
            scene->addEllipse(951, 795, 8, 8, penTriangle);
        }
        if (Channel_V.find("C/1") != string::npos)//левая выше
        {
            scene->addEllipse(896, 795, 8, 8, penTriangle);
        }
        if (Channel_V.find("OP") != string::npos)//левая выше  правая ниже
        {
            scene->addEllipse(896, 795, 8, 8, penTriangle);
            scene->addEllipse(951, 772, 8, 8, penTriangle);
        }
        if (Channel_V.find("OK") != string::npos)//левая ниже  правая выше
        {
            scene->addEllipse(896, 772, 8, 8, penTriangle);
            scene->addEllipse(951, 795, 8, 8, penTriangle);
        }
    }//triangles
}

void MainWindow::channel_VB()
{
    if (((Channel_VB == "C/-2")||(Channel_VB == "C/-1")) &&
            ((Channel_R == "C/2")||(Channel_R == "C/1")||(Channel_R == "C/0")||(Channel_R == "C/-1")||(Channel_R == "C/-2")))
        {
            diagnosic_message.append("Канал желчного пузыря: (2мд: VB/C/-1,-2 +R/C) желчекаменная болезнь; "
                                     "ЕСТЬ камни в желчном пузыре.\n");
            return;
        }
    if (((Channel_VB == "C/-2")||(Channel_VB == "C/-1")) &&
            ((Channel_R == "A/2")||(Channel_R == "A/1")||(Channel_R == "A/0")||(Channel_R == "A/-1")||(Channel_R == "A/-2")||(Channel_R == "B/2")||(Channel_R == "B/1")||(Channel_R == "B/0")||(Channel_R == "B/-1")||(Channel_R == "B/-2")))
        {
            diagnosic_message.append("Канал желчного пузыря: (2мд: VB/C/-1,-2 +R/AB) желчекаменная болезнь; "
                                     "ЕСТЬ песок в желчном пузыре.\n");
            return;
        }

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
        diagnosic_message.append("Канал желчного пузыря: хронический бескаменный холецистит, застой желчи.\n");
    }
    if (Channel_VB == "OK")
    {
        diagnosic_message.append("Канал желчного пузыря: избыток желчи при бескаменном холецистите.\n");
    }

//Канал желчного пузыря В
    if (Channel_VB == "B/2")
    {
        diagnosic_message.append("Канал желчного пузыря: дискинезия желчных путей с избытком (выбросом) желчи.\n");
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
        diagnosic_message.append("Канал желчного пузыря: дискинезия желчных путей с застоем желчи.\n");
    }

//Канал желчного пузыря С
    if (Channel_VB == "C/2")
    {
        diagnosic_message.append("Канал желчного пузыря: начальная стадия желчекаменной болезни.\n "
                                 "Активная стадия болезни, камней пока нет, а болезнь уже есть.\n");
    }
    if (Channel_VB == "C/1")
    {
        diagnosic_message.append("Канал желчного пузыря: начальная стадия желчекаменной болезни. Склонность к камнеобразованию.\n");
    }
    if (Channel_VB == "C/0")
    {
        diagnosic_message.append("Канал желчного пузыря: склонность к заболеванию ЖКБ. Склонность к камнеобразованию.\n");
    }
    if (Channel_VB == "C/-1")
    {
        diagnosic_message.append("Канал желчного пузыря: желчекаменная болезнь. Склонность к камнеобразованию.\n");
    }
    if (Channel_VB == "C/-2")
    {
        diagnosic_message.append("Канал желчного пузыря: желчекаменная болезнь. "
                                 "Возможны камни: тк вялотекущий хронический застой.\n");
    }
    if (Channel_VB == "OP")
    {
        diagnosic_message.append("Канал желчного пузыря: наличие камней или песка в желчном пузыре.\n "
                                 "Вероятность рака желчного пузыря (нужно еще смотреть другие меридианы!).\n");
    }
//Закрашиваем треугольники
    if (Channel_VB.find_first_of('0') == string::npos ) //Обе точки не в коридоре
    {
        if (Channel_VB.find("-2") != string::npos)//Обе точки ниже
        {
            scene->addEllipse(981, 772, 8, 8, penTriangle);
            scene->addEllipse(1037, 772, 8, 8, penTriangle);
        }
        if (Channel_VB.find("A/-1") != string::npos)//левая ниже
        {
            scene->addEllipse(981, 772, 8, 8, penTriangle);
        }
        if (Channel_VB.find("C/-1") != string::npos)//правая ниже
        {
            scene->addEllipse(1037, 772, 8, 8, penTriangle);
        }
        if (Channel_VB.find("/2") != string::npos)//Обе точки выше
        {
            scene->addEllipse(981, 795, 8, 8, penTriangle);
            scene->addEllipse(1037, 795, 8, 8, penTriangle);
        }
        if (Channel_VB.find("A/1") != string::npos)//правая выше
        {
            scene->addEllipse(1037, 795, 8, 8, penTriangle);
        }
        if (Channel_VB.find("C/1") != string::npos)//левая выше
        {
            scene->addEllipse(981, 795, 8, 8, penTriangle);
        }
        if (Channel_VB.find("OP") != string::npos)//левая выше  правая ниже
        {
            scene->addEllipse(981, 795, 8, 8, penTriangle);
            scene->addEllipse(1037, 772, 8, 8, penTriangle);
        }
        if (Channel_VB.find("OK") != string::npos)//левая ниже  правая выше
        {
            scene->addEllipse(981, 772, 8, 8, penTriangle);
            scene->addEllipse(1037, 795, 8, 8, penTriangle);
        }
    }//triangles
}

void MainWindow::channel_E()
{
    if (((Channel_E == "C/2")||(Channel_E == "C/1")) &&
            ((Channel_P == "C/2")||(Channel_P == "C/1")||(Channel_P == "C/0")||(Channel_P == "C/-1")||(Channel_P == "C/-2")))
        {
            diagnosic_message.append("Канал желудка: (2мд: E/C/2+P/C) гастрит с повышенной кислотностью.\n");
            return;
        }
    if (((Channel_E == "C/-2")||(Channel_E == "C/-1")) &&
            ((Channel_P == "C/2")||(Channel_P == "C/1")||(Channel_P == "C/0")||(Channel_P == "C/-1")||(Channel_P == "C/-2")))
        {
            diagnosic_message.append("Канал желудка: (2мд: E/C/-2 +P/C) гастрит с пониженной кислотностью.\n");
            return;
        }
    if (((Channel_E == "OP")) &&
            ((Channel_P == "C/2")||(Channel_P == "C/1")||(Channel_P == "C/0")||(Channel_P == "C/-1")||(Channel_P == "C/-2")))
        {
            diagnosic_message.append("Канал желудка: (2мд: E/OP +P/C) переедание при гастрите; или рак (нужно см.другие каналы!).\n");
            return;
        }

//Канал желудка А
    if (Channel_E == "A/2")
    {
        diagnosic_message.append("Канал желудка: повышенная кислотность желудочного сока. Человек наелся.\n");
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
    if (Channel_E == "OK")
    {
        diagnosic_message.append("Канал желудка: человек объелся.\n");
    }

//Канал желудка В
    if (Channel_E == "B/2")
    {
        diagnosic_message.append("Канал желудка: повышенная кислотность желудочного сока. Человек наелся.\n");
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
        diagnosic_message.append("Канал желудка: пониженная кислотность желудочного сока. Человек голодный, или мало поел.\n");
    }

//Канал желудка С
    if (Channel_E == "C/2")
    {
        diagnosic_message.append("Канал желудка: эмоции - экономность.\n");
    }
    if (Channel_E == "C/1")
    {
        diagnosic_message.append("Канал желудка: эмоции - экономость.\n");
    }
    if (Channel_E == "C/0")
    {
        diagnosic_message.append("Канал желудка: эмоции - бережливость.\n");
    }
    if (Channel_E == "C/-1")
    {
        diagnosic_message.append("Канал желудка: эмоции - жадность.\n");
    }
    if (Channel_E == "C/-2")
    {
        diagnosic_message.append("Канал желудка: эмоции - жадность.\n");
    }
    if (Channel_E == "OP")
    {
        diagnosic_message.append("Канал желудка: переедание.\n");
    }
//Закрашиваем треугольники
    if (Channel_E.find_first_of('0') == string::npos ) //Обе точки не в коридоре
    {
        if (Channel_E.find("-2") != string::npos)//Обе точки ниже
        {
            scene->addEllipse(1066, 772, 8, 8, penTriangle);
            scene->addEllipse(1122, 772, 8, 8, penTriangle);
        }
        if (Channel_E.find("A/-1") != string::npos)//левая ниже
        {
            scene->addEllipse(1066, 772, 8, 8, penTriangle);
        }
        if (Channel_E.find("C/-1") != string::npos)//правая ниже
        {
            scene->addEllipse(1122, 772, 8, 8, penTriangle);
        }
        if (Channel_E.find("/2") != string::npos)//Обе точки выше
        {
            scene->addEllipse(1066, 795, 8, 8, penTriangle);
            scene->addEllipse(1122, 795, 8, 8, penTriangle);
        }
        if (Channel_E.find("A/1") != string::npos)//правая выше
        {
            scene->addEllipse(1122, 795, 8, 8, penTriangle);
        }
        if (Channel_E.find("C/1") != string::npos)//левая выше
        {
            scene->addEllipse(1066, 795, 8, 8, penTriangle);
        }
        if (Channel_E.find("OP") != string::npos)//левая выше  правая ниже
        {
            scene->addEllipse(1066, 795, 8, 8, penTriangle);
            scene->addEllipse(1122, 772, 8, 8, penTriangle);
        }
        if (Channel_E.find("OK") != string::npos)//левая ниже  правая выше
        {
            scene->addEllipse(1066, 772, 8, 8, penTriangle);
            scene->addEllipse(1122, 795, 8, 8, penTriangle);
        }
    }//triangles
}
