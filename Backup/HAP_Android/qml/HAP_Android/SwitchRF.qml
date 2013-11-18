import QtQuick 2.0

Rectangle {
    id:thisbutton
    property string buttentext: ""
    property string commandstring: ""

    width: 500
    height: 150
    radius: 20
    antialiasing: true
    color: "black"
    Rectangle{
        id:background
        width: parent.width -10; height: parent.height -10
        color: "white"
        radius: 20
        anchors.centerIn: parent
        Rectangle{
            id: button_on
            x: 8
            y: 62
             width: (parent.width/2)-25; height: (parent.height/2);
             radius: 21
             border.width: 6
             border.color: "#000000"
             Text {
                 id: press_on
                 x: 8
                 y: 8
                 width: 212
                 height: 55
                 text: "On"
                 style: Text.Normal
                 font.italic: false
                 font.bold: true
                 font.pointSize: 21
                 horizontalAlignment: Text.AlignHCenter
                 verticalAlignment: Text.AlignVCenter
             }

             MouseArea {
                 id: mousearea1
                 x: 0
                 y: 0
                 width: 220
                 height: 70
                 onClicked: {
                     broadmessage(commandstring + "F0S$")
                 }
             }
             states: State {
                 name: "clicked"; when: mousearea1.pressed
                 PropertyChanges { target: button_on; color: "red" }
             }
        }
        Rectangle{
            id: button_off
            x: 262
            y: 62
             width: (parent.width/2)-25; height: (parent.height/2);
             radius: 21
             border.width: 6
             border.color: "#000000"
             Text {
                 id: press_Off
                 x: 8
                 y: 8
                 width: 212
                 height: 55
                 text: "Off"
                 style: Text.Normal
                 font.italic: false
                 font.bold: true
                 font.pointSize: 21
                 horizontalAlignment: Text.AlignHCenter
                 verticalAlignment: Text.AlignVCenter
             }

             MouseArea {
                 id: mousearea2
                 x: -1
                 y: 0
                 width: 220
                 height: 70
                 onClicked: {
                     broadmessage(commandstring + "0FS$")
                 }
             }
             states: State {
                 name: "clicked"; when: mousearea2.pressed
                 PropertyChanges { target: button_off; color: "red" }
             }
        }

        Text {
            id: press_Off1
            x: 8
            y: 1
            width: 482
            height: 55
            text: buttentext
            font.italic: false
            style: Text.Normal
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 21
            font.bold: true
        }
    }

}
