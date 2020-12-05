import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

Item {
    Material.accent: Material.Purple
    Button {
        id: button
        x: 270
        y: 8
        text: qsTr("Button")
        onClicked: menu.open()
        Material.background: Material.Teal

        Menu {
            id: menu
            y: button.height

            MenuItem {
                text: "New..."
            }
            MenuItem {
                text: "Open..."
            }
            MenuItem {
                text: "Save"
            }
        }
    }

    CheckBox {
        id: checkBox
        x: 8
        y: 98
        text: qsTr("Check Box")
    }

    ComboBox {
        id: comboBox
        x: 489
        y: 8
        font.family: "Courier"
        spacing: -1
        model: ["First", "Second", "Third"]
    }

    Label {
        id: label
        x: 8
        y: 8
        text: qsTr("Label")
    }

    RadioButton {
        id: radioButton
        x: 8
        y: 52
        text: qsTr("Radio Button")
    }

    RangeSlider {
        id: rangeSlider
        x: 8
        y: 193
        first.value: 0.25
        second.value: 0.75
    }

    Tumbler {
        id: tumbler
        x: 280
        y: 278
        width: 60
        height: 113
        model: 10
    }

    Slider {
        id: slider
        x: 229
        y: 193
        value: 0.5
    }

    BusyIndicator {
        id: busyIndicator
        x: 523
        y: 100
    }

    RadioButton {
        id: radioButton1
        x: 248
        y: 52
        text: qsTr("Radio Button")
    }

    RadioButton {
        id: radioButton2
        x: 487
        y: 54
        text: qsTr("Radio Button")
    }

    Switch {
        id: element
        x: 248
        y: 98
        text: qsTr("Switch")
    }

    TextArea {
        id: textArea
        x: 32
        y: 266
        width: 212
        height: 125
        text: qsTr("Text Area Text Area Text Area Text Area Text Area Text Area Text Area Text Area
")
        wrapMode: Text.WordWrap
        selectByMouse: true
    }

    Dial {
        id: dial
        x: 467
        y: 200
        width: 153
        height: 139
        value: 0.5
    }
}



/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
