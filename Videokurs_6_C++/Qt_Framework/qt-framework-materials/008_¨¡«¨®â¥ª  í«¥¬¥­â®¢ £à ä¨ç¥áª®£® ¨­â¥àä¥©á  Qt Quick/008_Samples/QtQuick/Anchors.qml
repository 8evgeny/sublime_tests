import QtQuick 2.12
import QtQuick.Controls 2.5

Item {
    id: element1
    Button {
        id: heightButton
        y: 421
        height: 59
        text: qsTr("Height++")
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.left: widthButton.right
        onClicked: height += 10
    }

    Button {
        id: widthButton
        y: 421
        width: 128
        height: 59
        text: qsTr("Width++")
        anchors.bottomMargin: 40
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        onClicked: width += 10
    }

    Dial {
        id: dial
        anchors.bottom: heightButton.top
        anchors.right: parent.right
        anchors.left: heightButton.left
        anchors.top: parent.top
    }


}





/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
