import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    Rectangle {
        id: feedback
        anchors.fill: parent
        color: "green"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                label.text = "Clicked:" + mouse.x + "," + mouse.y
                parent.forceActiveFocus()
            }
            onWheel: {
                label.text = "Wheel:" + wheel.angleDelta
            }
        }

        focus: true
        Keys.onUpPressed: label.text = "UpPressed"

//        MultiPointTouchArea {
//            id: multiPointTouchArea
//            anchors.fill: parent
//            touchPoints: [
//                TouchPoint { id: point1 },
//                TouchPoint { id: point2 }
//            ]
//        }

//        Rectangle {
//            width: 30; height: 30
//            color: "red"
//            x: point1.x + 10
//            y: point1.y + 10
//        }

        Label {
            id: label
            x: 398
            text: qsTr("Label")
            font.pointSize: 26
            font.family: "Times New Roman"
            anchors.top: parent.top
            anchors.right: parent.right
        }
    }
}
