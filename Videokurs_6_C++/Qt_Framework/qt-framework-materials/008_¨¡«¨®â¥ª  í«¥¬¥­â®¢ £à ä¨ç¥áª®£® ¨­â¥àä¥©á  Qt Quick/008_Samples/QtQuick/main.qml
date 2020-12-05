import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Tabs")

    StackLayout {
        id: stackLayout
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Visual {
        }

        Anchors {
        }

        Positioners {
        }

        LayoutManager {
        }

        Input {
        }

        States {
        }

        Data {
        }

        Logical{
        }

    }

    footer: TabBar {
        id: tabBar
        currentIndex: stackLayout.currentIndex

        TabButton {
            text: qsTr("Visual")
        }
        TabButton {
            text: qsTr("Anchors")
        }
        TabButton {
            text: qsTr("Positioners")
        }
        TabButton {
            text: qsTr("LayoutManager")
        }
        TabButton {
            text: qsTr("Input")
        }
        TabButton {
            text: qsTr("States")
        }
        TabButton {
            text: qsTr("Data")
        }
        TabButton {
            text: qsTr("Logical")
        }
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&New...") }
            Action { text: qsTr("&Open...") }
            Action { text: qsTr("&Save") }
            Action { text: qsTr("Save &As...") }
            MenuSeparator { }
            Action { text: qsTr("&Quit") }
        }
        Menu {
            title: qsTr("&Edit")
            Action { text: qsTr("Cu&t") }
            Action { text: qsTr("&Copy") }
            Action { text: qsTr("&Paste") }
        }
        Menu {
            title: qsTr("&Help")
            Action { text: qsTr("&About") }
        }
    }
}
