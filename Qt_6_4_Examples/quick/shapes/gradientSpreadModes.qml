// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Shapes

Rectangle {
    color: "lightGray"
    width: 256
    height: 256
    Rectangle {
        border.color: "black"
        width: 200
        height: 200
        anchors.centerIn: parent

        Shape {
            anchors.fill: parent

            ShapePath {
                strokeColor: "transparent"

                fillGradient: LinearGradient {
                    id: grad
                    y1: 50; y2: 150
                    GradientStop { position: 0; color: "black" }
                    GradientStop { position: 1; color: "red" }
                }

                startX: 10; startY: 10
                PathLine { relativeX: 180; relativeY: 0 }
                PathLine { relativeX: 0; relativeY: 180 }
                PathLine { relativeX: -180; relativeY: 0 }
                PathLine { relativeX: 0; relativeY: -180 }
            }
        }

        Timer {
            id: spreadTimer
            interval: 3000
            running: true
            repeat: true
            property variant spreads: [ ShapeGradient.PadSpread, ShapeGradient.RepeatSpread, ShapeGradient.ReflectSpread ]
            property variant spreadTexts: [ "PadSpread", "RepeatSpread", "ReflectSpread" ]
            property int spreadIdx: 0
            onTriggered: { spreadIdx = (spreadIdx + 1) % spreads.length; grad.spread = spreads[spreadIdx] }
        }


        Shape {
            anchors.fill: parent
            ShapePath {
                strokeColor: "gray"
                strokeWidth: 2
                fillColor: "transparent"
                PathMove { x: 0; y: 50 }
                PathLine { relativeX: 200; relativeY: 0 }
                PathMove { x: 0; y: 150 }
                PathLine { relativeX: 200; relativeY: 0 }
            }
        }
    }

    Text {
        anchors.right: parent.right
        text: spreadTimer.spreadTexts[spreadTimer.spreadIdx]
    }
}
