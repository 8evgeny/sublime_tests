// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

// This example demonstrates placing items in a view using
// an ObjectModel

import QtQuick
import QtQml.Models

Rectangle {
    id: root
    color: "lightgray"
    width: 320
    height: 480
    property bool printDestruction: false

//! [0]
    ObjectModel {
        id: itemModel

        Rectangle {
            width: view.width; height: view.height
            color: "#FFFEF0"
            Text { text: "Page 1"; font.bold: true; anchors.centerIn: parent }

            Component.onDestruction: if (root.printDestruction) print("destroyed 1")
        }
        Rectangle {
            width: view.width; height: view.height
            color: "#F0FFF7"
            Text { text: "Page 2"; font.bold: true; anchors.centerIn: parent }

            Component.onDestruction: if (root.printDestruction) print("destroyed 2")
        }
        Rectangle {
            width: view.width; height: view.height
            color: "#F4F0FF"
            Text { text: "Page 3"; font.bold: true; anchors.centerIn: parent }

            Component.onDestruction: if (root.printDestruction) print("destroyed 3")
        }
    }

    ListView {
        id: view
        anchors { fill: parent; bottomMargin: 30 }
        model: itemModel
        preferredHighlightBegin: 0; preferredHighlightEnd: 0
        highlightRangeMode: ListView.StrictlyEnforceRange
        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem; flickDeceleration: 2000
        cacheBuffer: 200
    }
//! [0]
    Rectangle {
        width: root.width; height: 30
        anchors { top: view.bottom; bottom: parent.bottom }
        color: "gray"

        Row {
            anchors.centerIn: parent
            spacing: 20

            Repeater {
                model: itemModel.count

                Rectangle {
                    required property int index

                    width: 5; height: 5
                    radius: 3
                    color: view.currentIndex == index ? "blue" : "white"

                    MouseArea {
                        width: 20; height: 20
                        anchors.centerIn: parent
                        onClicked: view.currentIndex = parent.index
                    }
                }
            }
        }
    }
}
