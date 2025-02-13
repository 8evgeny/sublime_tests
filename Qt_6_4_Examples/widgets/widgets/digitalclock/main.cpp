// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QApplication>

#include "digitalclock.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DigitalClock clock;
    clock.show();
    return app.exec();
}
