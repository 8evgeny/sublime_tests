// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQml
import QtQml.Models
import QtQuick

Rectangle {
    id: window
    width: 320; height: 480; color: "#232323"

    property var easingCurve: [ 0.2, 0.2, 0.13, 0.65, 0.2, 0.8,
                                0.624, 0.98, 0.93, 0.95, 1, 1 ]

    ListModel {
        id: easingTypes
        ListElement { name: "Easing.Linear"; type: Easing.Linear; ballColor: "DarkRed" }
        ListElement { name: "Easing.InQuad"; type: Easing.InQuad; ballColor: "IndianRed" }
        ListElement { name: "Easing.OutQuad"; type: Easing.OutQuad; ballColor: "Salmon" }
        ListElement { name: "Easing.InOutQuad"; type: Easing.InOutQuad; ballColor: "Tomato" }
        ListElement { name: "Easing.OutInQuad"; type: Easing.OutInQuad; ballColor: "DarkOrange" }
        ListElement { name: "Easing.InCubic"; type: Easing.InCubic; ballColor: "Gold" }
        ListElement { name: "Easing.OutCubic"; type: Easing.OutCubic; ballColor: "Yellow" }
        ListElement { name: "Easing.InOutCubic"; type: Easing.InOutCubic; ballColor: "PeachPuff" }
        ListElement { name: "Easing.OutInCubic"; type: Easing.OutInCubic; ballColor: "Thistle" }
        ListElement { name: "Easing.InQuart"; type: Easing.InQuart; ballColor: "Orchid" }
        ListElement { name: "Easing.OutQuart"; type: Easing.OutQuart; ballColor: "Purple" }
        ListElement { name: "Easing.InOutQuart"; type: Easing.InOutQuart; ballColor: "SlateBlue" }
        ListElement { name: "Easing.OutInQuart"; type: Easing.OutInQuart; ballColor: "Chartreuse" }
        ListElement { name: "Easing.InQuint"; type: Easing.InQuint; ballColor: "LimeGreen" }
        ListElement { name: "Easing.OutQuint"; type: Easing.OutQuint; ballColor: "SeaGreen" }
        ListElement { name: "Easing.InOutQuint"; type: Easing.InOutQuint; ballColor: "DarkGreen" }
        ListElement { name: "Easing.OutInQuint"; type: Easing.OutInQuint; ballColor: "Olive" }
        ListElement { name: "Easing.InSine"; type: Easing.InSine; ballColor: "DarkSeaGreen" }
        ListElement { name: "Easing.OutSine"; type: Easing.OutSine; ballColor: "Teal" }
        ListElement { name: "Easing.InOutSine"; type: Easing.InOutSine; ballColor: "Turquoise" }
        ListElement { name: "Easing.OutInSine"; type: Easing.OutInSine; ballColor: "SteelBlue" }
        ListElement { name: "Easing.InExpo"; type: Easing.InExpo; ballColor: "SkyBlue" }
        ListElement { name: "Easing.OutExpo"; type: Easing.OutExpo; ballColor: "RoyalBlue" }
        ListElement { name: "Easing.InOutExpo"; type: Easing.InOutExpo; ballColor: "MediumBlue" }
        ListElement { name: "Easing.OutInExpo"; type: Easing.OutInExpo; ballColor: "MidnightBlue" }
        ListElement { name: "Easing.InCirc"; type: Easing.InCirc; ballColor: "CornSilk" }
        ListElement { name: "Easing.OutCirc"; type: Easing.OutCirc; ballColor: "Bisque" }
        ListElement { name: "Easing.InOutCirc"; type: Easing.InOutCirc; ballColor: "RosyBrown" }
        ListElement { name: "Easing.OutInCirc"; type: Easing.OutInCirc; ballColor: "SandyBrown" }
        ListElement { name: "Easing.InElastic"; type: Easing.InElastic; ballColor: "DarkGoldenRod" }
        ListElement { name: "Easing.OutElastic"; type: Easing.OutElastic; ballColor: "Chocolate" }
        ListElement { name: "Easing.InOutElastic"; type: Easing.InOutElastic; ballColor: "SaddleBrown" }
        ListElement { name: "Easing.OutInElastic"; type: Easing.OutInElastic; ballColor: "Brown" }
        ListElement { name: "Easing.InBack"; type: Easing.InBack; ballColor: "Maroon" }
        ListElement { name: "Easing.OutBack"; type: Easing.OutBack; ballColor: "LavenderBlush" }
        ListElement { name: "Easing.InOutBack"; type: Easing.InOutBack; ballColor: "MistyRose" }
        ListElement { name: "Easing.OutInBack"; type: Easing.OutInBack; ballColor: "Gainsboro" }
        ListElement { name: "Easing.OutBounce"; type: Easing.OutBounce; ballColor: "Silver" }
        ListElement { name: "Easing.InBounce"; type: Easing.InBounce; ballColor: "DimGray" }
        ListElement { name: "Easing.InOutBounce"; type: Easing.InOutBounce; ballColor: "SlateGray" }
        ListElement { name: "Easing.OutInBounce"; type: Easing.OutInBounce; ballColor: "DarkSlateGray" }
        ListElement { name: "Easing.BezierSpline"; type: Easing.BezierSpline; ballColor: "Chartreuse"; }
    }

    Component {
        id: delegate

        Item {
            id: delegateInstance
            required property string name;
            required property int type;
            required property color ballColor;

            height: 56; width: window.width

            Text { text: parent.name; anchors.centerIn: parent; color: "White" }

            Rectangle {
                id: slot1; color: "#121212"; x: 30; height: 46; width: 46
                border.color: "#343434"; border.width: 1; radius: 12; antialiasing: true
                anchors.verticalCenter: parent.verticalCenter
            }

            Rectangle {
                id: slot2; color: "#121212"; x: window.width - 76; height: 46; width: 46
                border.color: "#343434"; border.width: 1; radius: 12; antialiasing: true
                anchors.verticalCenter: parent.verticalCenter
            }

            Rectangle {
                id: rect; x: 30; color: "#454545"
                border.color: "White"; border.width: 2
                height: 46; width: 46; radius: 12; antialiasing: true
                anchors.verticalCenter: parent.verticalCenter

                MouseArea {
                    onClicked: if (rect.state == '') rect.state = "right"; else rect.state = ''
                    anchors.fill: parent
                    anchors.margins: -5 // Make MouseArea bigger than the rectangle, itself
                }

                states : State {
                    name: "right"
                    PropertyChanges {
                        rect {
                            x: window.width - 76;
                            color: delegateInstance.ballColor
                        }
                    }
                }

                transitions: Transition {
                    NumberAnimation {
                        properties: "x"
                        easing.type: delegateInstance.type
                        easing.bezierCurve: window.getBezierCurve(delegateInstance.name)
                        duration: 1000
                    }
                    ColorAnimation {
                        properties: "color"
                        easing.type: delegateInstance.type
                        easing.bezierCurve: window.getBezierCurve(delegateInstance.name)
                        duration: 1000
                    }
                }
            }
        }
    }

    Flickable {
        anchors.fill: parent
        contentHeight: layout.height
        Column {
            id: layout
            Repeater { model: easingTypes; delegate: delegate }
        }
    }

    function getBezierCurve(name)
    {
        if (name === "Easing.BezierSpline")
            return easingCurve;
        return [];
    }
}
