import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.0

Window {
    visible: true
    width: 400
    height: 300
    title: qsTr("QML  TableView delegate Demo")

    Rectangle {
        width: 360
        height: 360

        ListModel {
            id: dataModel

            ListElement {
                color: "orange"
                text: "first"
            }
            ListElement {
                color: "lightgreen"
                text: "second"
            }
            ListElement {
                color: "orchid"
                text: "third"
            }
            ListElement {
                color: "tomato"
                text: "fourth"
            }
        }

        TableView {
            id: view

            anchors.margins: 10
            anchors.fill: parent
            model: dataModel
            clip: true

            TableViewColumn {
                width: 100
                title: "Color"
                role: "color"
            }
            TableViewColumn {
                width: 100
                title: "Text"
                role: "text"
            }

            itemDelegate: Item {
                Text {
                    anchors.centerIn: parent
                    renderType: Text.NativeRendering
                    text: styleData.value
                }
            }
        }
    }
}
