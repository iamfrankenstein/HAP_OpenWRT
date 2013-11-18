import QtQuick 2.0

Rectangle {
    width: 200
    height: 150
    radius: 20
    color: "black"
    Rectangle{
        id:background
        width: parent.width -10; height: parent.height -10
        color: "white"
        radius: 20
        anchors.centerIn: parent
        Text {
            anchors.centerIn: parent
            text: "Exit"
            font.pointSize: 18; font.bold: true
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
        Qt.quit()
        }
    }

    states: State {
        name: "clicked"; when: mouseArea.pressed
        PropertyChanges { target: background; color: "red" }
    }
}
