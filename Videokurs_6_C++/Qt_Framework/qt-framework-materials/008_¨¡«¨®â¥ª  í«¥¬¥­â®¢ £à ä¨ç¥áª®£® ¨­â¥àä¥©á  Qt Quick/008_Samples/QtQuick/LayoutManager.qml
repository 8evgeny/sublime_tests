import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Item {
    RowLayout {
        id: rowLayout
        anchors.fill: parent

        ColumnLayout {
            id: columnLayout
            Layout.columnSpan: 1
            Layout.rowSpan: 1
            Layout.fillHeight: true
            Layout.fillWidth: true

            RadioButton {
                id: radioButton
                text: qsTr("Radio Button")
                Layout.fillWidth: false
                Layout.fillHeight: true
            }

            RadioButton {
                id: radioButton1
                text: qsTr("Radio Button")
                Layout.preferredHeight: 100
            }

            RadioButton {
                id: radioButton2
                text: qsTr("Radio Button")
                Layout.fillHeight: true
            }
        }

        GridLayout {
            id: gridLayout
            width: 100
            height: 100

            ProgressBar {
                id: progressBar
                Layout.fillWidth: true
                Layout.fillHeight: true
                value: 0.5
            }

            Slider {
                id: slider
                Layout.fillHeight: true
                Layout.fillWidth: true
                value: 0.5
            }

            Button {
                id: button
                text: qsTr("Button")
                Layout.preferredWidth: 200
                Layout.rowSpan: 2
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Switch {
                id: element
                text: qsTr("Switch")
                Layout.row: 1
            }
        }
    }

}





















/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1;anchors_height:100;anchors_width:100;anchors_x:226;anchors_y:160}
}
 ##^##*/
