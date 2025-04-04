// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef BINDABLEUSER_H
#define BINDABLEUSER_H

#include <QProperty>

//! [bindable-user-class]

class BindableUser
{
public:
    enum Country {
        None,
        Finland,
        Germany,
        Norway,
    };

    BindableUser() = default;
    BindableUser(const BindableUser &) = delete;

    Country country() const { return m_country; }
    void setCountry(Country country);
    QBindable<Country> bindableCountry() { return &m_country; }

    int age() const { return m_age; }
    void setAge(int age);
    QBindable<int> bindableAge() { return &m_age; }

private:
    QProperty<Country> m_country { None };
    QProperty<int> m_age { 0 };
};

//! [bindable-user-class]

#endif // BINDABLEUSER_H
