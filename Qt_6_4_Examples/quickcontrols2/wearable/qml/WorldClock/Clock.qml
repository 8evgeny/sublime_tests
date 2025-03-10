// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls as QQC2
import ".."
import "../Style"

SwipeViewPage {
    id: clock

    property int hours
    property int minutes
    property int seconds
    property real shift: timeShift
    property bool night: false
    property bool internationalTime: true //Unset for local time

    function getWatchFaceImage(imageName) {
        return "images/" + imageName
    }

    function timeChanged() {
        var date = new Date
        hours = internationalTime ? date.getUTCHours() + Math.floor(
                                        clock.shift) : date.getHours()
        night = (hours < 7 || hours > 19)
        minutes = internationalTime ?
         date.getUTCMinutes() + ((clock.shift % 1) * 60) : date.getMinutes()
        seconds = date.getUTCSeconds()
    }

    Timer {
        interval: 100
        running: true
        repeat: true
        onTriggered: clock.timeChanged()
    }

    Item {
        anchors.centerIn: parent

        width: 200
        height: 220

        Rectangle {
            color: clock.night ? UIStyle.colorQtGray1 : UIStyle.colorQtGray10
            radius: width / 2
            width: parent.width
            height: parent.width
        }

        Image {
            id: background
            source: getWatchFaceImage("swissdaydial.png")
            visible: clock.night == false
        }
        Image {
            source: getWatchFaceImage("swissnightdial.png")
            visible: clock.night == true
        }

        Image {
            x: 92.5
            y: 27
            source: getWatchFaceImage(clock.night ?
                                        "swissnighthour.png"
                                        : "swissdayhour.png")
            transform: Rotation {
                id: hourRotation
                origin.x: 7.5
                origin.y: 73
                angle: (clock.hours * 30) + (clock.minutes * 0.5)
                Behavior on angle {
                    SpringAnimation {
                        spring: 2
                        damping: 0.2
                        modulus: 360
                    }
                }
            }
        }

        Image {
            x: 93.5
            y: 17
            source: getWatchFaceImage(clock.night ?
                                        "swissnightminute.png"
                                        : "swissdayminute.png")
            transform: Rotation {
                id: minuteRotation
                origin.x: 6.5
                origin.y: 83
                angle: clock.minutes * 6
                Behavior on angle {
                    SpringAnimation {
                        spring: 2
                        damping: 0.2
                        modulus: 360
                    }
                }
            }
        }

        Image {
            x: 97.5
            y: 20
            source: getWatchFaceImage("second.png")
            transform: Rotation {
                id: secondRotation
                origin.x: 2.5
                origin.y: 80
                angle: clock.seconds * 6
                Behavior on angle {
                    SpringAnimation {
                        spring: 2
                        damping: 0.2
                        modulus: 360
                    }
                }
            }
        }

        Image {
            anchors.centerIn: background
            source: getWatchFaceImage("center.png")
        }

        Text {
            id: cityLabel
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            anchors.horizontalCenter: parent.horizontalCenter

            text: cityName
            color: UIStyle.themeColorQtGray1
            font.pixelSize: UIStyle.fontSizeXS
            font.letterSpacing: 2
        }
    }
}
