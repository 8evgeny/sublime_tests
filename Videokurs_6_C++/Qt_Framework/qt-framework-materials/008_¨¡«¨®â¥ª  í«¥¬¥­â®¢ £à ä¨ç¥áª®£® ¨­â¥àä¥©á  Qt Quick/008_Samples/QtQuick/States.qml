import QtQuick 2.0

Item {
    Rectangle {
        id: rect
        width: 100; height: 100
        color: "black"

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
        }

        states: [
            State {
                name: "moved"; when: mouseArea.pressed
                PropertyChanges { target: rect; x: 50; y: 50 }
            },
            State {
                name: "colored"; when: mouseArea.containsMouse
                PropertyChanges { target: rect; color: "blue" }
            }
        ]
        transitions: [
            Transition {
                to: "moved"
                NumberAnimation { properties: "x,y"; easing.type: Easing.InOutQuad }
            },
            Transition {
                to: "colored"
                ColorAnimation { duration: 1000 }
            }
        ]
    }
}
