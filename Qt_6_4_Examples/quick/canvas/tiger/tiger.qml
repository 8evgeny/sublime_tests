// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls
import "../"
import "tiger.js" as Tiger

Item {
    id: container
    width: 320
    height: 480

    Column {
        spacing: 6
        anchors.fill: parent
        anchors.topMargin: 12

        Label {
            font.pointSize: 24
            font.bold: true
            text: "Tiger with SVG path"
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#777"
        }

        Canvas {
            id: canvas
            width: 320
            height: 280
            antialiasing: true

            property string strokeStyle: "steelblue"
            property string fillStyle: "yellow"
            property bool fill: true
            property bool stroke: true
            property real alpha: alphaCtrl.value
            property real scale: scaleCtrl.value
            property real rotate: rotateCtrl.value
            property int frame: 0

            onFillChanged: requestPaint();
            onStrokeChanged: requestPaint();
            onAlphaChanged: requestPaint();
            onScaleChanged: requestPaint();
            onRotateChanged: requestPaint();

            onPaint: {
                var ctx = canvas.getContext('2d');
                var originX = canvas.width/2 + 30
                var originY = canvas.height/2 + 60

                ctx.save();
                ctx.clearRect(0, 0, canvas.width, canvas.height);
                ctx.globalAlpha = canvas.alpha;
                ctx.globalCompositeOperation = "source-over";

                ctx.translate(originX, originY)
                ctx.scale(canvas.scale, canvas.scale);
                ctx.rotate(canvas.rotate);
                ctx.translate(-originX, -originY)

                ctx.strokeStyle = Qt.rgba(.3, .3, .3,1);
                ctx.lineWidth = 1;

                //! [0]
                for (var i = 0; i < Tiger.tiger.length; i++) {
                    if (Tiger.tiger[i].width != undefined)
                        ctx.lineWidth = Tiger.tiger[i].width;

                    if (Tiger.tiger[i].path != undefined)
                        ctx.path = Tiger.tiger[i].path;

                    if (Tiger.tiger[i].fill != undefined) {
                        ctx.fillStyle = Tiger.tiger[i].fill;
                        ctx.fill();
                    }

                    if (Tiger.tiger[i].stroke != undefined) {
                        ctx.strokeStyle = Tiger.tiger[i].stroke;
                        ctx.stroke();
                    }
                }
                //! [0]
                ctx.restore();
            }
        }
    }
    Column {
        id: controls
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 12

        LabeledSlider {id: scaleCtrl ; min: 0.1 ; max: 1 ; init: 0.3 ; name: "Scale"; width: container.width}
        LabeledSlider {id: rotateCtrl ; min: 0 ; max: Math.PI*2 ; init: 0 ; name: "Rotate"; width: container.width}
        LabeledSlider {id: alphaCtrl ; min: 0 ; max: 1 ; init: 1 ; name: "Alpha"; width: container.width}
    }
}
