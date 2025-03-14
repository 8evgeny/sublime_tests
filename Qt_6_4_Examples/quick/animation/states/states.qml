// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQml
import QtQuick

Rectangle {
    id: page
    width: 640; height: 480
    color: "#343434"

    Image {
        id: userIcon
        x: topLeftRect.x; y: topLeftRect.y
        source: "qt-logo.png"
    }

    Rectangle {
        id: topLeftRect

        anchors { left: parent.left; top: parent.top; leftMargin: 10; topMargin: 20 }
        width: 46; height: 54
        color: "Transparent"; border.color: "Gray"; radius: 6

        // Clicking in here sets the state to the default state, returning the image to
        // its initial position
        MouseArea { anchors.fill: parent; onClicked: page.state = '' }
    }

    Rectangle {
        id: middleRightRect

        anchors { right: parent.right; verticalCenter: parent.verticalCenter; rightMargin: 20 }
        width: 46; height: 54
        color: "Transparent"; border.color: "Gray"; radius: 6

        // Clicking in here sets the state to 'middleRight'
        MouseArea { anchors.fill: parent; onClicked: page.state = 'middleRight' }
    }

    Rectangle {
        id: bottomLeftRect

        anchors { left: parent.left; bottom: parent.bottom; leftMargin: 10; bottomMargin: 20 }
        width: 46; height: 54
        color: "Transparent"; border.color: "Gray"; radius: 6

        // Clicking in here sets the state to 'bottomLeft'
        MouseArea { anchors.fill: parent; onClicked: page.state = 'bottomLeft' }
    }

    states: [
        // ![0]
        // In state 'middleRight', move the image to middleRightRect
        State {
            name: "middleRight"
            PropertyChanges {
                userIcon {
                    x: middleRightRect.x
                    y: middleRightRect.y
                }
            }
        },

        // In state 'bottomLeft', move the image to bottomLeftRect
        State {
            name: "bottomLeft"
            PropertyChanges {
                userIcon {
                    x: bottomLeftRect.x
                    y: bottomLeftRect.y
                }
            }
        }
        // ![0]
    ]
}
