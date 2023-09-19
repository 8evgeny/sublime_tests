import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 500
    height: 450
    title: qsTr("QML  PatchView delegate Demo")

    Rectangle {
        width: 500
        height: 200

        PathView {
            id: view

            anchors.fill: parent
            model: 30

            path: Path {
                startX: 0
                startY: 0

                PathQuad {
                    x: view.width
                    y: 0
                    controlX: view.width / 2
                    controlY: view.height * 4
                }
            }
            delegate: Rectangle {
                width: 20
                height: 20
                color: "orchid"
                border {
                    color: "black"
                    width: 1
                }
            }
        }
    }
}
