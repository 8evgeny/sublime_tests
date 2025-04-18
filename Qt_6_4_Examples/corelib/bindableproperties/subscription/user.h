// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef USER_H
#define USER_H

#include <QObject>

//! [user-class]

class User : public QObject
{
    Q_OBJECT

public:
    enum Country {
        None,
        Finland,
        Germany,
        Norway,
    };

    Country country() const { return m_country; }
    void setCountry(Country country);

    int age() const { return m_age; }
    void setAge(int age);

signals:
    void countryChanged();
    void ageChanged();

private:
    Country m_country = Country::None;
    int m_age = 0;
};

//! [user-class]
#endif // USER_H
