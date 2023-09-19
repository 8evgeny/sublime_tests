import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.XmlListModel 2.15
Window {
    visible: true
    width: 1000
    height: 800
    title: qsTr("QML  PatchView delegate Demo")

    Rectangle {
        width: 1000
        height: 860
        color: "lightsteelblue"

        XmlListModel {
            id: dataModel

            source: "http://habrahabr.ru/rss"
            query: "/rss/channel/item"

            XmlRole {
                name: "title"
                query: "title/string()"
            }
        }

        ListView {
            id: view

            anchors.margins: 10
            anchors.fill: parent
            spacing: 10
            model: dataModel

            delegate: Rectangle {
                width: view.width
                height: 40
                radius: 10

                Text {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                    wrapMode: Text.Wrap
                    renderType: Text.NativeRendering
                    text: model.title
                }
            }
        }
    }
}
