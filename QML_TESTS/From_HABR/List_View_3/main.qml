import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 370
    height: 350
    title: qsTr("QML  ListView delegate Demo")

    Rectangle {
        width: 360
        height: 360

        ListModel {
            id: dataModel

            ListElement {
                type: "bird"
                text: "penguin"
            }
            ListElement {
                type: "bird"
                text: "raven"
            }
            ListElement {
                type: "reptile"
                text: "lizard"
            }
            ListElement {
                type: "reptile"
                text: "turtle"
            }
            ListElement {
                type: "reptile"
                text: "crocodile"
            }
        }

        ListView {
            id: view

            anchors.margins: 10
            anchors.fill: parent
            spacing: 10
            model: dataModel
            clip: true

            section.property: "type"
            section.delegate: Rectangle {
                width: view.width
                height: 40
                color: "lightgreen"
                Text {
                    anchors.centerIn: parent
                    renderType: Text.NativeRendering
                    font.bold: true
                    text: section
                }
            }

            delegate: Rectangle {
                width: view.width
                height: 40
                border {
                    color: "black"
                    width: 1
                }

                Text {
                    anchors.centerIn: parent
                    renderType: Text.NativeRendering
                    text: model.text
                }
            }
        }
    }
  }
