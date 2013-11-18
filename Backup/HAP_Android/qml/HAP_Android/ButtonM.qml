import QtQuick 2.0

Rectangle {
    id:thisbutton
    property string buttentext: ""
    property string commandstring: ""
    width: 200
    height: 150
    radius: 20
    antialiasing: true
    Rectangle{
        id:background
        width: parent.width -10; height: parent.height -10
        color: "white"
        radius: 20
        anchors.centerIn: parent
        Text {
            anchors.centerIn: parent
            text: buttentext
            font.pointSize: 18; font.bold: true
        }
    }
    MouseArea {
        id: mouseArea;
        anchors.fill: parent
        onClicked: {
            broadencryptedmessage(commandstring)
            //thisbutton.state="clicked"
        }
    }

    states: State {
        name: "clicked"; when: mouseArea.pressed
        PropertyChanges { target: background; color: "red" }
    }

}
