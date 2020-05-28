/********************************************************************************
** Form generated from reading UI file 'winscreen.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINSCREEN_H
#define UI_WINSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinScreen
{
public:
    QGridLayout *gridLayout;
    QPushButton *replay;
    QTextBrowser *winText;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *WinScreen)
    {
        if (WinScreen->objectName().isEmpty())
            WinScreen->setObjectName(QString::fromUtf8("WinScreen"));
        WinScreen->resize(400, 300);
        gridLayout = new QGridLayout(WinScreen);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        replay = new QPushButton(WinScreen);
        replay->setObjectName(QString::fromUtf8("replay"));

        gridLayout->addWidget(replay, 2, 0, 1, 1);

        winText = new QTextBrowser(WinScreen);
        winText->setObjectName(QString::fromUtf8("winText"));
        winText->setMaximumSize(QSize(16777215, 100));

        gridLayout->addWidget(winText, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 0, 1, 1);


        retranslateUi(WinScreen);

        QMetaObject::connectSlotsByName(WinScreen);
    } // setupUi

    void retranslateUi(QWidget *WinScreen)
    {
        WinScreen->setWindowTitle(QCoreApplication::translate("WinScreen", "Form", nullptr));
        replay->setText(QCoreApplication::translate("WinScreen", "Replay", nullptr));
        winText->setHtml(QCoreApplication::translate("WinScreen", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Serif'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a name=\"result_box\"></a><span style=\" font-size:20pt;\">y</span><span style=\" font-size:20pt;\">ou won !</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">you can replay</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinScreen: public Ui_WinScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINSCREEN_H
