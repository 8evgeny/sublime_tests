// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "widgetgallery.h"
#include "norwegianwoodstyle.h"

#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QDial>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollBar>
#include <QSpinBox>
#include <QStyle>
#include <QStyleFactory>
#include <QTableWidget>
#include <QTextEdit>
#include <QTimer>

//! [0]
WidgetGallery::WidgetGallery(QWidget *parent)
    : QDialog(parent)
{
    styleComboBox = new QComboBox;
    const QString defaultStyleName = QApplication::style()->objectName();
    QStringList styleNames = QStyleFactory::keys();
    styleNames.append("NorwegianWood");
    for (int i = 1, size = styleNames.size(); i < size; ++i) {
        if (defaultStyleName.compare(styleNames.at(i), Qt::CaseInsensitive) == 0) {
            styleNames.swapItemsAt(0, i);
            break;
        }
    }
    styleComboBox->addItems(styleNames);

    styleLabel = new QLabel(tr("&Style:"));
    styleLabel->setBuddy(styleComboBox);

    useStylePaletteCheckBox = new QCheckBox(tr("&Use style's standard palette"));
    useStylePaletteCheckBox->setChecked(true);

    disableWidgetsCheckBox = new QCheckBox(tr("&Disable widgets"));

    createTopLeftGroupBox();
    createTopRightGroupBox();
    createBottomLeftTabWidget();
    createBottomRightGroupBox();
    createProgressBar();
//! [0]

//! [1]
    connect(styleComboBox, &QComboBox::textActivated,
//! [1] //! [2]
            this, &WidgetGallery::changeStyle);
    connect(useStylePaletteCheckBox, &QCheckBox::toggled,
            this, &WidgetGallery::changePalette);
    connect(disableWidgetsCheckBox, &QCheckBox::toggled,
            topLeftGroupBox, &QGroupBox::setDisabled);
    connect(disableWidgetsCheckBox, &QCheckBox::toggled,
            topRightGroupBox, &QGroupBox::setDisabled);
    connect(disableWidgetsCheckBox, &QCheckBox::toggled,
            bottomLeftTabWidget, &QGroupBox::setDisabled);
    connect(disableWidgetsCheckBox, &QCheckBox::toggled,
            bottomRightGroupBox, &QGroupBox::setDisabled);
//! [2]

//! [3]
    QHBoxLayout *topLayout = new QHBoxLayout;
//! [3] //! [4]
    topLayout->addWidget(styleLabel);
    topLayout->addWidget(styleComboBox);
    topLayout->addStretch(1);
    topLayout->addWidget(useStylePaletteCheckBox);
    topLayout->addWidget(disableWidgetsCheckBox);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addLayout(topLayout, 0, 0, 1, 2);
    mainLayout->addWidget(topLeftGroupBox, 1, 0);
    mainLayout->addWidget(topRightGroupBox, 1, 1);
    mainLayout->addWidget(bottomLeftTabWidget, 2, 0);
    mainLayout->addWidget(bottomRightGroupBox, 2, 1);
    mainLayout->addWidget(progressBar, 3, 0, 1, 2);
    mainLayout->setRowStretch(1, 1);
    mainLayout->setRowStretch(2, 1);
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 1);
    setLayout(mainLayout);

    setWindowTitle(tr("Styles"));
    styleChanged();
}
//! [4]

//! [5]
void WidgetGallery::changeStyle(const QString &styleName)
//! [5] //! [6]
{
    if (styleName == "NorwegianWood")
        QApplication::setStyle(new NorwegianWoodStyle);
    else
        QApplication::setStyle(QStyleFactory::create(styleName));
}
//! [6]

//! [7]
void WidgetGallery::changePalette()
//! [7] //! [8]
{
    QApplication::setPalette(useStylePaletteCheckBox->isChecked() ?
        QApplication::style()->standardPalette() : QPalette());
}
//! [8]

void WidgetGallery::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::StyleChange)
        styleChanged();
}

void WidgetGallery::styleChanged()
{
    auto styleName = QApplication::style()->objectName();
    for (int i = 0; i < styleComboBox->count(); ++i) {
        if (QString::compare(styleComboBox->itemText(i), styleName, Qt::CaseInsensitive) == 0) {
            styleComboBox->setCurrentIndex(i);
            break;
        }
    }

    changePalette();
}

//! [9]
void WidgetGallery::advanceProgressBar()
//! [9] //! [10]
{
    int curVal = progressBar->value();
    int maxVal = progressBar->maximum();
    progressBar->setValue(curVal + (maxVal - curVal) / 100);
}
//! [10]

//! [11]
void WidgetGallery::createTopLeftGroupBox()
//! [11] //! [12]
{
    topLeftGroupBox = new QGroupBox(tr("Group 1"));

    radioButton1 = new QRadioButton(tr("Radio button 1"));
    radioButton2 = new QRadioButton(tr("Radio button 2"));
    radioButton3 = new QRadioButton(tr("Radio button 3"));
    radioButton1->setChecked(true);

    checkBox = new QCheckBox(tr("Tri-state check box"));
    checkBox->setTristate(true);
    checkBox->setCheckState(Qt::PartiallyChecked);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(radioButton1);
    layout->addWidget(radioButton2);
    layout->addWidget(radioButton3);
    layout->addWidget(checkBox);
    layout->addStretch(1);
    topLeftGroupBox->setLayout(layout);
}
//! [12]

void WidgetGallery::createTopRightGroupBox()
{
    topRightGroupBox = new QGroupBox(tr("Group 2"));

    defaultPushButton = new QPushButton(tr("Default Push Button"));
    defaultPushButton->setDefault(true);

    togglePushButton = new QPushButton(tr("Toggle Push Button"));
    togglePushButton->setCheckable(true);
    togglePushButton->setChecked(true);

    flatPushButton = new QPushButton(tr("Flat Push Button"));
    flatPushButton->setFlat(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(defaultPushButton);
    layout->addWidget(togglePushButton);
    layout->addWidget(flatPushButton);
    layout->addStretch(1);
    topRightGroupBox->setLayout(layout);
}

void WidgetGallery::createBottomLeftTabWidget()
{
    bottomLeftTabWidget = new QTabWidget;
    bottomLeftTabWidget->setSizePolicy(QSizePolicy::Preferred,
                                       QSizePolicy::Ignored);

    QWidget *tab1 = new QWidget;
    tableWidget = new QTableWidget(10, 10);

    QHBoxLayout *tab1hbox = new QHBoxLayout;
    tab1hbox->setContentsMargins(5,5, 5, 5);
    tab1hbox->addWidget(tableWidget);
    tab1->setLayout(tab1hbox);

    QWidget *tab2 = new QWidget;
    textEdit = new QTextEdit;

    textEdit->setPlainText(tr("Twinkle, twinkle, little star,\n"
                              "How I wonder what you are.\n"
                              "Up above the world so high,\n"
                              "Like a diamond in the sky.\n"
                              "Twinkle, twinkle, little star,\n"
                              "How I wonder what you are!\n"));

    QHBoxLayout *tab2hbox = new QHBoxLayout;
    tab2hbox->setContentsMargins(5, 5, 5, 5);
    tab2hbox->addWidget(textEdit);
    tab2->setLayout(tab2hbox);

    bottomLeftTabWidget->addTab(tab1, tr("&Table"));
    bottomLeftTabWidget->addTab(tab2, tr("Text &Edit"));
}

void WidgetGallery::createBottomRightGroupBox()
{
    bottomRightGroupBox = new QGroupBox(tr("Group 3"));
    bottomRightGroupBox->setCheckable(true);
    bottomRightGroupBox->setChecked(true);

    lineEdit = new QLineEdit("s3cRe7");
    lineEdit->setEchoMode(QLineEdit::Password);

    spinBox = new QSpinBox(bottomRightGroupBox);
    spinBox->setValue(50);

    dateTimeEdit = new QDateTimeEdit(bottomRightGroupBox);
    dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    slider = new QSlider(Qt::Horizontal, bottomRightGroupBox);
    slider->setValue(40);

    scrollBar = new QScrollBar(Qt::Horizontal, bottomRightGroupBox);
    scrollBar->setValue(60);

    dial = new QDial(bottomRightGroupBox);
    dial->setValue(30);
    dial->setNotchesVisible(true);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(lineEdit, 0, 0, 1, 2);
    layout->addWidget(spinBox, 1, 0, 1, 2);
    layout->addWidget(dateTimeEdit, 2, 0, 1, 2);
    layout->addWidget(slider, 3, 0);
    layout->addWidget(scrollBar, 4, 0);
    layout->addWidget(dial, 3, 1, 2, 1);
    layout->setRowStretch(5, 1);
    bottomRightGroupBox->setLayout(layout);
}

//! [13]
void WidgetGallery::createProgressBar()
{
    progressBar = new QProgressBar;
    progressBar->setRange(0, 10000);
    progressBar->setValue(0);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WidgetGallery::advanceProgressBar);
    timer->start(1000);
}
//! [13]
