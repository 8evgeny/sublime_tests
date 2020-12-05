import QtQuick 2.9
import QtQuick.Controls 2.2
import com.ruslan.counter 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")

    Counter {
        id: counter
        onValueChanged: valueChangedLabel.text = value
    }

    Column {
        id: column
        spacing: 10
        anchors.fill: parent

        Row {
            id: row
            spacing: 20

            SpinBox {
                id: valueSpinBox
            }

            Button {
                objectName: "setValueButton"
                text: qsTr("Set value 2")
                onClicked: counter.value = valueSpinBox.value
            }

            Button {
                text: qsTr("Call setValue slot")
                onClicked: counter.setValue(valueSpinBox.value)
            }

        }

        Row {
            Label {
                text: qsTr("value: ")
            }

            Label {
                text: counter.value
            }
        }

        Row {
            Label {
                text: qsTr("valueChanged: ")
            }

            Label {
                id: valueChangedLabel
            }
        }
    }

}



























/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
