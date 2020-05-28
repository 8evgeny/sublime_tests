/********************************************************************************
** Form generated from reading UI file 'gamescreen.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMESCREEN_H
#define UI_GAMESCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "gamewidget.h"

QT_BEGIN_NAMESPACE

class Ui_GameScreen
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *helpButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *reload;
    GameWidget *gamewidget;

    void setupUi(QWidget *GameScreen)
    {
        if (GameScreen->objectName().isEmpty())
            GameScreen->setObjectName(QString::fromUtf8("GameScreen"));
        GameScreen->resize(461, 460);
        verticalLayout = new QVBoxLayout(GameScreen);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        helpButton = new QPushButton(GameScreen);
        helpButton->setObjectName(QString::fromUtf8("helpButton"));
        helpButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(helpButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        reload = new QPushButton(GameScreen);
        reload->setObjectName(QString::fromUtf8("reload"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(reload->sizePolicy().hasHeightForWidth());
        reload->setSizePolicy(sizePolicy);
        reload->setStyleSheet(QString::fromUtf8(""));
        reload->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(reload);


        verticalLayout->addLayout(horizontalLayout);

        gamewidget = new GameWidget(GameScreen);
        gamewidget->setObjectName(QString::fromUtf8("gamewidget"));

        verticalLayout->addWidget(gamewidget);


        retranslateUi(GameScreen);

        QMetaObject::connectSlotsByName(GameScreen);
    } // setupUi

    void retranslateUi(QWidget *GameScreen)
    {
        GameScreen->setWindowTitle(QCoreApplication::translate("GameScreen", "Form", nullptr));
        helpButton->setText(QCoreApplication::translate("GameScreen", "&help", nullptr));
        reload->setText(QCoreApplication::translate("GameScreen", "reload", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameScreen: public Ui_GameScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESCREEN_H
