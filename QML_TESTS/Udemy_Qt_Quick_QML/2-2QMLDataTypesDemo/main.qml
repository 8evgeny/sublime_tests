import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 800
    height: 600
    title: qsTr("QML Datatypes Demo")

    property string mString: "http://www.blikoontech.com"
    property int mInt: 45
    property bool isFemale: true
    property double mDouble: 77.5
    property url mUrl: "http://www.blikoontech.com"

    property int aNumber: 100
    property bool aBool: false
    property string aString: "Hello world!"
    property var anotherString: String("#FF008800")
    property color aColor: Qt.rgba(0.2, 0.3, 0.4, 0.5)
    property rect aRect: Qt.rect(17, 56, 46, 10)
    property point aPoint: Qt.point(10, 10)
    property size aSize: Qt.size(10, 10)
    property vector3d aVector3d: Qt.vector3d(100, 100, 100)
    property var anArray: [1, 2, 3, "four", "five", (function() { return "six"; })]
    property var anObject: { "foo": 10, "bar": 20 }
    property var aFunction: (function() { return "Seven"; })

    property var aFont  : Qt.font({family: "Consolas", pointSize: 30, bold: false})
    property date mDate: "2018-07-19"

    Rectangle {
        width: 200
        height: 100 + mInt
        anchors.centerIn: parent
        color: aColor

        Text {
            id: mTextId
            anchors.centerIn: parent
            text: mString
//            font.bold: isFemale?true:false
            font : aFont
        }
    }

    Component.onCompleted: {
        console.log("The value of mString is :" + mString)
        print("The value of mString is :"+mString)
        console.log("The value of mInt is :"+mInt)

        if ( isFemale){
            console.log("You may wear a dress")
        }else{
            console.log("You may wear a suit")
        }
        console.log("The value of mDouble is :" + mDouble)
        console.log("The value of mUrl is :"+ mUrl)

        if ( mString == mUrl)
        {
            console.log("They are the same")
        }else{
            console.log("They are NOT the same")
        }

        console.log("-----------------Playing with var datatype---------------")
        console.log("The value of aNumber is :"+ aNumber)
        console.log("The value of aBool is : " + aBool)
        console.log("The value of aString is : " + aString)
        console.log("The value of anotherString is : " + anotherString)

        console.log("The components of aRect are : x : "+ aRect.x
                    + " y :"+ aRect.y + " width :" + aRect.width + " height :"+ aRect.height)

        console.log("The length of the array is :"+anArray.length)


        anArray.forEach(function(value,index){
            if( index ===5){
              console.log(value())
            }else
            {
                console.log(value)
            }})


        for(var i = 0; i < anArray.length ; i++)
        {
            if ( i === 5)
            {
                console.log(anArray[i]())
            }else{
                console.log(anArray[i])
            }
        }

        console.log("The date is :"+ mDate)

        console.log("The function value is :"+aFunction())
    }
}
