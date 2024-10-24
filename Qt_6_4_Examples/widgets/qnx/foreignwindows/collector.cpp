// Copyright (C) 2018 QNX Software Systems. All rights reserved.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <QApplication>
#include <QDebug>
#include <QHBoxLayout>
#include <QWindow>

#include <algorithm>
#include <screen/screen.h>

#include "collector.h"

constexpr int MANAGER_EVENT_NAME_SUGGESTION = 9999;

Collector::Collector(QWidget *parent)
    : QWidget(parent)
{
    QApplication::instance()->installNativeEventFilter(this);

    QLayout *layout = new QHBoxLayout(this);
    setLayout(layout);
}

Collector::~Collector()
{
    QApplication::instance()->removeNativeEventFilter(this);
}

bool Collector::nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result)
{
    Q_UNUSED(result);

    if (eventType == QByteArrayLiteral("screen_event_t"))
        return filterQnxScreenEvent(static_cast<screen_event_t>(message));

    return false;
}

bool Collector::filterQnxScreenEvent(screen_event_t event)
{
    int objectType = SCREEN_OBJECT_TYPE_CONTEXT;
    screen_get_event_property_iv(event, SCREEN_PROPERTY_OBJECT_TYPE, &objectType);

    if (objectType == SCREEN_OBJECT_TYPE_WINDOW)
        return filterQnxScreenWindowEvent(event);

    return false;
}

bool Collector::filterQnxScreenWindowEvent(screen_event_t event)
{
    int eventType = SCREEN_EVENT_NONE;
    screen_get_event_property_iv(event, SCREEN_PROPERTY_TYPE, &eventType);
    screen_window_t window = nullptr;
    screen_get_event_property_pv(event,
                                 SCREEN_PROPERTY_WINDOW,
                                 reinterpret_cast<void **>(&window));

    if (eventType == SCREEN_EVENT_CREATE)
        return filterQnxScreenWindowCreateEvent(window, event);
    else if (eventType == SCREEN_EVENT_CLOSE)
        return filterQnxScreenWindowCloseEvent(window, event);
    else if (eventType == SCREEN_EVENT_MANAGER)
        return filterQnxScreenWindowManagerEvent(window, event);

    return false;
}

bool Collector::filterQnxScreenWindowCreateEvent(screen_window_t window, screen_event_t event)
{
    Q_UNUSED(event);
    WId winId = reinterpret_cast<WId>(window);

    QByteArray parentGroup(256, 0);
    screen_get_window_property_cv(window,
            SCREEN_PROPERTY_PARENT,
            parentGroup.length(),
            parentGroup.data());
    parentGroup.resize(strlen(parentGroup.constData()));

    QByteArray group(256, 0);
    screen_get_window_property_cv(reinterpret_cast<screen_window_t>(windowHandle()->winId()),
            SCREEN_PROPERTY_GROUP,
            group.length(),
            group.data());
    group.resize(strlen(group.constData()));

    if (parentGroup != group)
        return false;

    Collectible collectible;
    collectible.window = QWindow::fromWinId(winId);
    collectible.widget = QWidget::createWindowContainer(collectible.window, this);
    layout()->addWidget(collectible.widget);
    m_collectibles.append(collectible);

    return false;
}

bool Collector::filterQnxScreenWindowCloseEvent(screen_window_t window, screen_event_t event)
{
    Q_UNUSED(event);
    WId winId = reinterpret_cast<WId>(window);
    auto it = std::find_if(m_collectibles.begin(), m_collectibles.end(),
                           [winId] (const Collectible &collectible) {
                               return collectible.window->winId() == winId;
                           });
    if (it != m_collectibles.end()) {
        delete it->widget;
        // it->window is deleted by it->widget.
        m_collectibles.erase(it);
    }

    return false;
}

bool Collector::filterQnxScreenWindowManagerEvent(screen_window_t window, screen_event_t event)
{
    int managerEventType = 0;
    screen_get_event_property_iv(event, SCREEN_PROPERTY_SUBTYPE, &managerEventType);

    if (managerEventType == MANAGER_EVENT_NAME_SUGGESTION)
        return filterQnxScreenWindowManagerNameEvent(window, event);

    return false;
}

bool Collector::filterQnxScreenWindowManagerNameEvent(screen_window_t window, screen_event_t event)
{
    Q_UNUSED(window);
    int dataSize = 0;
    screen_get_event_property_iv(event, SCREEN_PROPERTY_SIZE, &dataSize);
    if (dataSize > 0) {
        QByteArray data(dataSize, 0);
        screen_get_event_property_cv(event, SCREEN_PROPERTY_USER_DATA, data.size(), data.data());
    }

    return false;
}
