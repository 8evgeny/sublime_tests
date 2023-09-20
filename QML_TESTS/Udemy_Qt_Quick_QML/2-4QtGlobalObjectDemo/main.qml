import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Qt Global Object Demo")

    property var fonts: Qt.fontFamilies()

    Rectangle{
        width: 300
        height: 100
        color: "red"
        anchors.centerIn: parent
        MouseArea{
            anchors.fill: parent
            onClicked: {

                //Quit the application
                console.log("Quitting the App")
                Qt.quit()

                //List the available fonts
                for( var i = 0; i < fonts.length ; i++){
                    console.log("["+ i + "] :" + fonts[i])
                }

                //Hash a string
                var mName = "Daniel Gakwaya"
                var mNameHash = Qt.md5(mName)
                console.log("The hash of the name is :"+ mNameHash)


                //Open url externally
                Qt.openUrlExternally("http://yandex.com")

                //Open local files with default program
//                Qt.openUrlExternally("file:///D:/artwork/LearnQt.png")
                Qt.openUrlExternally("file:///home/evg/SOFT/Github/sublime_tests/QML_TESTS/Udemy_Qt_Quick_QML/2-4QtGlobalObjectDemo/1.png")
                //Capture platform info
                console.log("The current platform is : "+Qt.platform.os)
            }
        }
    }
}
