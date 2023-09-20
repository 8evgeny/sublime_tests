import QtQuick 2.12

Item {
    id : rootId
    property alias buttonText: buttonTextId.text
    width: containerRectId.width
    height: containerRectId.height
    signal buttonClicked


    Rectangle {

        id : containerRectId
        width: buttonTextId.implicitWidth + 40
        height: buttonTextId.implicitHeight + 40
        color: "yellow"
        border { color: "black"; width : 2}

        Text {
            id : buttonTextId
            text : "Button"
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                //console.log("Clicked ON :"+ buttonTextId.text)
                rootId.buttonClicked()
            }
        }
    }

}


