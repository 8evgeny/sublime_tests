import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        ListView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: animalModel
            delegate: Text {
                text: size + " " + type
                width: parent.width
                font.pointSize: 30
            }
        }

        ListView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: animalModel
            delegate: Row {
                spacing: 5
                width: parent.width
                TextEdit {
                    text: size
                    font.pointSize: 30
                    onEditingFinished: {
                        size = text
                    }
                }
                TextEdit {
                    text: type
                    font.pointSize: 30
                    onEditingFinished: {
                        type = text
                    }
                }
            }
        }
    }
}
