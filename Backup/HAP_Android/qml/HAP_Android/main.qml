import QtQuick 2.0

Rectangle {
    width: 2048
    height: 1536
    signal broadencryptedmessage (string sMessage)
    signal broadmessage (string sMessage)

    ButtonExit{
        x:1925; y:6
        width: 116
        height: 62
    }
    ButtonM{
        buttentext: "Mute"
        commandstring: "Supperlappie|volumemute"
        color: "black"
        x:1024; y:87
    }
    ButtonM{
        buttentext: "Vol +"
        commandstring: "Supperlappie|volumeup"
        color: "black"
        x:1241; y:87
    }
    ButtonM{
        buttentext: "Vol -"
        commandstring: "Supperlappie|volumedown"
        color: "black"
        x:808; y:87
    }
    ButtonM{
        buttentext: "^"
        commandstring: "Supperlappie|arrowup"
        color: "black"
        x:372; y:251
    }
    ButtonM{
        buttentext: "V"
        commandstring: "Supperlappie|arrowdown"
        color: "black"
        x:372; y:420
    }
    ButtonM{
        buttentext: "<-"
        commandstring: "Supperlappie|arrowleft"
        color: "black"
        x:144; y:420
    }
    ButtonM{
        buttentext: "->"
        commandstring: "Supperlappie|arrowright"
        color: "black"
        x:592; y:420
    }
    ButtonM{
        buttentext: "Enter"
        commandstring: "Supperlappie|Enter"
        color: "black"
        x:592; y:251
    }
    ButtonM{
        buttentext: ">>"
        commandstring: "Supperlappie|nexttrack"
        color: "black"
        x:592; y:87
    }
    ButtonM{
        buttentext: "<<"
        commandstring: "Supperlappie|prevtrack"
        color: "black"
        x:144; y:87
    }
    ButtonM{
        buttentext: "Play"
        commandstring: "Supperlappie|play"
        color: "black"
        x:372; y:87
    }

    ButtonM {
        x: 144; y: 251
        color: "black"
        commandstring: "Supperlappie|escape"
        buttentext: "Esc"
    }

    ButtonM {
        x: 808
        y: 420
        color: "#000000"
        commandstring: "Supperlappie|mouseleft"
        buttentext: "<--"
    }

    ButtonM {
        x: 1241
        y: 251
        color: "#000000"
        commandstring: "Supperlappie|rclick"
        buttentext: "RClick"
    }

    ButtonM {
        x: 1024
        y: 251
        color: "#000000"
        commandstring: "Supperlappie|mouseup"
        buttentext: "^"
    }

    ButtonM {
        x: 808
        y: 251
        color: "#000000"
        commandstring: "Supperlappie|lclick"
        buttentext: "Click"
    }

    ButtonM {
        x: 1024
        y: 420
        color: "#000000"
        commandstring: "Supperlappie|mousedown"
        buttentext: "V"
    }

    ButtonM {
        x: 1241
        y: 420
        color: "#000000"
        commandstring: "Supperlappie|mouseright"
        buttentext: "-->"
    }

    ButtonM {
        x: 357
        y: 586
        color: "#000000"
        commandstring: "Supperlappie|nPause"
        buttentext: "netflixpauze"
    }

    ButtonM {
        x: 592
        y: 594
        color: "#000000"
        commandstring: "Supperlappie|nFocus"
        buttentext: "netflix select"
    }
    SwitchRF{
        x: 1478
        y: 87
        color: "#000000"
        buttentext: "Miden Lamp"
        commandstring:    "Supperwir|!@0F*F1F1FFFF0F"
    }

    SwitchRF {
        x: 1478
        y: 257
        color: "#000000"
        buttentext: "Lamp A"
        commandstring:    "Supperwir|!@0F*F1F100FFFF"
    }

    SwitchRF {
        x: 1478
        y: 427
        color: "#000000"
        buttentext: "Scherm"
        commandstring:    "Supperwir|!@0F*F1F10F0FFF"
    }

    SwitchRF {
        x: 1478
        y: 601
        color: "#000000"
        buttentext: "Supperlappie|nFocus"
        commandstring:    "Supperwir|!@0F*F1F1FFF0FF"
    }
}
