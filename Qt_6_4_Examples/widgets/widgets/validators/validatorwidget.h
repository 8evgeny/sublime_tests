// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QWidget>

#include "ui_validators.h"

class ValidatorWidget : public QWidget, public Ui::ValidatorsForm
{
    Q_OBJECT
public:
    ValidatorWidget(QWidget *parent = nullptr);

private slots:
    void updateValidator();
    void updateDoubleValidator();
};
