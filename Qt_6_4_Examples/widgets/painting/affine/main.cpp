// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "xform.h"

#include <QApplication>

int main(int argc, char **argv)
{
    Q_INIT_RESOURCE(affine);
#ifdef Q_OS_ANDROID
    qputenv("QT_SCALE_FACTOR", "2");
#endif
    QApplication app(argc, argv);

    XFormWidget xformWidget(nullptr);
    QStyle *arthurStyle = new ArthurStyle;
    xformWidget.setStyle(arthurStyle);

    const QList<QWidget *> widgets = xformWidget.findChildren<QWidget *>();
    for (QWidget *w : widgets) {
        w->setStyle(arthurStyle);
        w->setAttribute(Qt::WA_AcceptTouchEvents);
    }

    xformWidget.show();

    return app.exec();
}
