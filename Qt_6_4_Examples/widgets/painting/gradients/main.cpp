// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "gradients.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(gradients);
#ifdef Q_OS_ANDROID
    qputenv("QT_SCALE_FACTOR", "2");
#endif

    QApplication app(argc, argv);

    GradientWidget gradientWidget;
    QStyle *arthurStyle = new ArthurStyle;
    gradientWidget.setStyle(arthurStyle);
    const QList<QWidget *> widgets = gradientWidget.findChildren<QWidget *>();
    for (QWidget *w : widgets) {
        w->setStyle(arthurStyle);
        w->setAttribute(Qt::WA_AcceptTouchEvents);
    }
    gradientWidget.show();

    return app.exec();
}
