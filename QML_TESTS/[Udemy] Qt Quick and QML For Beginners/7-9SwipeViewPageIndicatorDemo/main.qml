import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("PageIndicator and SwipeView Demo")

    SwipeView{
        id : swipeViewId
        anchors.fill: parent
        currentIndex: pageIndicatorId.currentIndex

       Image {
           id : image1
           //source: "http://www.blikoontech.com/wp-content/uploads/2018/06/1.png"
           source:"images/1.png"
       }
       Image {
           id : image2
           //source: "http://www.blikoontech.com/wp-content/uploads/2018/06/2.png"
           source: "images/2.png"
       }
       Image {
           id : image3
           //source: "http://www.blikoontech.com/wp-content/uploads/2018/06/3.png"
           source: "images/3.png"
       }

    }

    PageIndicator{
        id : pageIndicatorId
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        //Page indicator specific properties
        currentIndex: swipeViewId.currentIndex
        interactive: true
        count : swipeViewId.count
    }


}
