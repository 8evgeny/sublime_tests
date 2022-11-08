import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 400
    height: 400
    title: qsTr("QML  PatchView delegate Demo")

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

        Flickable {
            anchors.fill: parent
            contentWidth: row.width

            Row {
                id: row

                height: parent.height

                Repeater {
                    model: dataModel
                    delegate: Item {
                        height: parent.height
                        width: 100

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
                                text: model.text
                            }
                        }
                    }
                }
            }
        }
    }
}
