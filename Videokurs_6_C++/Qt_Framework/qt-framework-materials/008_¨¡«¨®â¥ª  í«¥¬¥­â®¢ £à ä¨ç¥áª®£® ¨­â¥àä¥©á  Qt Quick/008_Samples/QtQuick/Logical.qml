import QtQuick 2.0

Item {
    TextInput {
        id: hexNumber
        anchors.fill: parent
        validator: RegExpValidator { regExp: /[0-9A-F]+/ }
    }

    Rectangle {
        x: 200
        y: 200
        width: 100;
        height: 100
        color: "red"
        transform: Rotation { origin.x: 20; origin.y: 20; angle: 45}
    }

    Rectangle {
        x: 200
        y: 200
        width: 100;
        height: 100
        color: "blue"
    }
}
