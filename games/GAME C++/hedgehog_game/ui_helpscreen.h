/********************************************************************************
** Form generated from reading UI file 'helpscreen.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPSCREEN_H
#define UI_HELPSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "help/gamehelpwidget.h"

QT_BEGIN_NAMESPACE

class Ui_HelpScreen
{
public:
    QGridLayout *gridLayout;
    GameHelpWidget *demo;
    QHBoxLayout *horizontalLayout;
    QPushButton *rulesButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *menuButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *demoButton;
    QTextEdit *rules;

    void setupUi(QWidget *HelpScreen)
    {
        if (HelpScreen->objectName().isEmpty())
            HelpScreen->setObjectName(QString::fromUtf8("HelpScreen"));
        HelpScreen->resize(400, 300);
        HelpScreen->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(HelpScreen);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        demo = new GameHelpWidget(HelpScreen);
        demo->setObjectName(QString::fromUtf8("demo"));

        gridLayout->addWidget(demo, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        rulesButton = new QPushButton(HelpScreen);
        rulesButton->setObjectName(QString::fromUtf8("rulesButton"));
        rulesButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(rulesButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        menuButton = new QPushButton(HelpScreen);
        menuButton->setObjectName(QString::fromUtf8("menuButton"));

        horizontalLayout->addWidget(menuButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        demoButton = new QPushButton(HelpScreen);
        demoButton->setObjectName(QString::fromUtf8("demoButton"));
        demoButton->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(demoButton);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        rules = new QTextEdit(HelpScreen);
        rules->setObjectName(QString::fromUtf8("rules"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(rules->sizePolicy().hasHeightForWidth());
        rules->setSizePolicy(sizePolicy);
        rules->setMinimumSize(QSize(0, 0));
        rules->setMaximumSize(QSize(16777215, 16777215));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(186, 189, 183, 0));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 0));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(220, 222, 219, 0));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(93, 94, 91, 0));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(124, 126, 122, 0));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(220, 222, 219, 127));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        rules->setPalette(palette);
        rules->setReadOnly(true);

        gridLayout->addWidget(rules, 2, 0, 1, 1);


        retranslateUi(HelpScreen);

        QMetaObject::connectSlotsByName(HelpScreen);
    } // setupUi

    void retranslateUi(QWidget *HelpScreen)
    {
        HelpScreen->setWindowTitle(QCoreApplication::translate("HelpScreen", "Form", nullptr));
        rulesButton->setText(QCoreApplication::translate("HelpScreen", "Rules", nullptr));
        menuButton->setText(QCoreApplication::translate("HelpScreen", "&Game", nullptr));
        demoButton->setText(QCoreApplication::translate("HelpScreen", "Demo", nullptr));
        rules->setHtml(QCoreApplication::translate("HelpScreen", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Monospace'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a name=\"result_box\"></a><span style=\" font-family:'Serif';\">T</span><span style=\" font-family:'Serif';\">he </span><span style=\" font-family:'Serif'; font-weight:600;\">goal</span><span style=\" font-family:'Serif';\"> - to hold all the hedgehog cloud. <br /><br />Hedgehog is able to walk only on the vertical and horizontal movement started, it goes all the way. <br /><br />You need to select the starting position for the hedgehog. Then, indicate the direction in which it should move. <br /><br />In the </span><span style=\" font-family:'Serif'; font-wei"
                        "ght:600;\">demo</span><span style=\" font-family:'Serif';\"> the game &quot;right&quot; cloud highlighted.</span></p></body></html>", nullptr));
        rules->setPlaceholderText(QCoreApplication::translate("HelpScreen", "\320\246\320\265\320\273\321\214 \320\270\320\263\321\200\321\213 \342\200\224 \320\277\321\200\320\276\320\262\320\265\321\201\321\202\320\270 \321\221\320\266\320\270\320\272\320\260 \320\277\320\276 \320\262\321\201\320\265\320\274 \321\202\321\203\321\207\320\272\320\260\320\274. \320\222 \320\275\320\260\321\207\320\260\320\273\320\265, \320\262\320\260\320\274 \320\275\320\260\320\264\320\276 \320\262\321\213\320\261\321\200\320\260\321\202\321\214 \320\275\320\260\321\207\320\260\320\273\321\214\320\275\321\203\321\216 \320\277\320\276\320\267\320\270\321\206\320\270\321\216 \320\264\320\273\321\217 \320\265\320\266\320\260. \320\227\320\260\321\202\320\265\320\274, \321\203\320\272\320\260\320\267\321\213\320\262\320\260\321\202\321\214 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265, \320\262 \320\272\320\276\321\202\320\276\321\200\320\276\320\274 \320\276\320\275 \320\264\320\276\320\273\320\266\320\265\320\275 \320\264\320\262\320\270\320\263\320\260\321\202"
                        "\321\214\321\201\321\217. \320\201\320\266 \321\203\320\274\320\265\320\265\321\202 \321\205\320\276\320\264\320\270\321\202\321\214 \321\202\320\276\320\273\321\214\320\272\320\276 \320\277\320\276 \320\262\320\265\321\200\321\202\320\270\320\272\320\260\320\273\320\270 \320\270 \320\263\320\276\321\200\320\270\320\267\320\276\320\275\321\202\320\260\320\273\320\270, \320\275\320\260\321\207\320\260\320\262 \320\264\320\262\320\270\320\266\320\265\320\275\320\270\320\265, \320\276\320\275 \320\270\320\264\320\265\321\202 \320\264\320\276 \321\203\320\277\320\276\321\200\320\260. \320\222 \320\264\320\265\320\274\320\276-\320\270\320\263\321\200\320\265 \302\253\320\277\321\200\320\260\320\262\320\270\320\273\321\214\320\275\321\213\320\265\302\273 \321\202\321\203\321\207\320\272\320\270 \320\262\321\213\320\264\320\265\320\273\320\265\320\275\321\213 \321\206\320\262\320\265\321\202\320\276\320\274.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HelpScreen: public Ui_HelpScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPSCREEN_H
