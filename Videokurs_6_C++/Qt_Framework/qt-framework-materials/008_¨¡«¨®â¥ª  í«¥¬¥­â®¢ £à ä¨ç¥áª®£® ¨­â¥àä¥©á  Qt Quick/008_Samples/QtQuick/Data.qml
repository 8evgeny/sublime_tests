import QtQuick 2.0

Item {
    ListModel {
        id: fruitModel
        property string language: "en"
        ListElement {
            name: "Apple"
            cost: 2.45
            fruitColor: "green"
        }
        ListElement {
            name: "Orange"
            cost: 3.25
            fruitColor: "orange"
        }
        ListElement {
            name: "Banana"
            cost: 1.95
            fruitColor: "yellow"
        }
    }

    Component {
        id: fruitDelegate
        Row {
                id: fruit
                Text { text: " Fruit: " + name; color: fruitColor }
                Text { text: " Cost: $" + cost }
                Text { text: " Language: " + fruit.ListView.view.model.language }
                Text { text: " Location: " + fruit.ListView.view.location }
        }
    }

    ListView {
        property string location: "Market"
        model: fruitModel
        delegate: fruitDelegate
        anchors.fill: parent
    }
}
