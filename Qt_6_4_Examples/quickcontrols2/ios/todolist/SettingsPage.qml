// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

import QtQuick
import QtQuick.Controls
import QtQuick.Controls.iOS

Page {
    title: "settingsPage"

    property bool showDoneTasks: true

    header: Label {
        text: qsTr("Settings")
        font.pointSize: AppSettings.fontSize + 20
        font.styleName: "Semibold"
        leftPadding: 20
        topPadding: 20
    }

    ListView {
        anchors.fill: parent
        topMargin: 20
        model: listModel
        clip: true

        ListModel {
            id: listModel
            ListElement {
                setting: qsTr("Font size")
                page: "FontSize"
            }

            ListElement {
                setting: qsTr("Maximum number of tasks per project")
                page: "MaxTasks"
            }

            ListElement {
                setting: qsTr("Show completed tasks")
                page: "ToggleCompletedTasks"
            }
        }

        delegate: ItemDelegate {
            width: parent.width
            text: setting
            font.pointSize: AppSettings.fontSize

            onClicked: stackView.push(page + "Page.qml")

            required property string setting
            required property string page

            Image {
                source: IOS.theme === IOS.Dark ? "images/back-white.png"
                                               : "images/back.png"
                width: 20
                height: 20
                anchors.right: parent.right
                anchors.rightMargin: 10
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenter: parent.verticalCenter
                mirror: true
            }
        }
    }
}
