import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    id: element
    Column {
        id: column
        anchors.fill: parent

        Row {
            id: row
            width: 500
            height: 100
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                id: button
                text: qsTr("Button")
            }

            Button {
                id: button1
                text: qsTr("Button")
            }
        }

        Row {
            height: 100
            anchors.left: parent.left
            anchors.right: parent.right

            RadioButton {
                id: radioButton
                text: qsTr("Radio Button")
            }

            RadioButton {
                id: radioButton1
                text: qsTr("Radio Button")
            }

            RadioButton {
                id: radioButton2
                text: qsTr("Radio Button")
            }
        }

        Flow {
            height: 200
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: 0

            Button {
                id: button2
                text: qsTr("Button")
            }

            Label {
                id: label
                text: qsTr("Label")
            }

            RadioButton {
                id: radioButton3
                text: qsTr("Radio Button")
            }

            Slider {
                id: slider
                value: 0.5
            }

        }
    }

}
