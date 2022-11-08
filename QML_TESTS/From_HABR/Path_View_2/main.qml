import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 400
    height: 600
    title: qsTr("QML  PatchView delegate Demo")

    Rectangle {
        width: 400
        height: 400

        PathView {
            id: view

            anchors.fill: parent
            model: 50

            path: Path {
                startX: view.width / 2
                startY: view.height / 2

                PathQuad {
                    relativeX: 0
                    y: view.height
                    controlX: view.width
                    controlY: 0
                }
                PathQuad {
                    relativeX: 0
                    y: view.height / 2
                    controlX: 0
                    controlY: 0
                }
            }
            delegate: Rectangle {
                width: 20
                height: 20
                color: "hotpink"
                border {
                    color: "black"
                    width: 1
                }
            }
        }
    }
}
