import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 400
    height: 300
    title: qsTr("QML  ListView delegate Demo")

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

        GridView {
            id: view

            anchors.margins: 10
            anchors.fill: parent
            cellHeight: 100
            cellWidth: cellHeight
            model: dataModel
            clip: true

            highlight: Rectangle {
                color: "skyblue"
            }

            delegate: Item {
                property var view: GridView.view
                property var isCurrent: GridView.isCurrentItem

                height: view.cellHeight
                width: view.cellWidth

                Rectangle {
                    anchors.margins: 5
                    anchors.fill: parent
                    color: model.color
                    border {
                        color: "black"
                        width: 1
                    }

                    Text {
                        anchors.centerIn: parent
                        renderType: Text.NativeRendering
                        text: "%1%2".arg(model.text).arg(isCurrent ? " *" : "")
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: view.currentIndex = model.index
                    }
                }
            }
        }
    }
}
