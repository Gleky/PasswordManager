import QtQuick 2.12
import QtQuick.Dialogs 1.2

Item {
    id: mainItem
    anchors.fill: parent
    visible: false;

    Rectangle {
        id: background
        anchors.fill: parent
        color: "#202020"
        onOpacityChanged: mainItem.visible = (opacity != 0);
        opacity: 0
    }

    MouseArea {
        anchors.fill: parent
        onClicked: { mainItem.close(); }
    }

    Rectangle {
        id: menuBackground
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        color: "#353535"

        width: 300
        x: -width

        MouseArea {
            anchors.fill: parent
            onClicked: {}
        }

        Flickable {
            x: 0
            y: topBar.height
            height: menuBackground.height - y
            width: menuBackground.width
            flickableDirection: Flickable.VerticalFlick
            contentWidth: width
            contentHeight: lastItem.y + lastItem.height

            Text {
                x: 6
                y: 5
                color: "#ffffff"
                text: "Storage folder"
                font.pointSize: 14
            }
            Text {
                x: (parent.width - width)/2
                y: 35
                color: "#ffffff"
                text: pwmodel.storage.storageDir()
                font.pointSize: 10
            }
            RectButton {
                x: (parent.width - width)/2
                y: 55
                width: parent.width * 0.8
                text: "Change folder"
                onClicked: {fileDialog.show();}
                font.pointSize: 10
            }

            Text {
                x: 6
                y: 120
                color: "#ffffff"
                text: "Storage type"
                font.pointSize: 14
            }
            Text {
                x: (parent.width - width)/2
                y: 150
                color: "#ffffff"
                text: pwmodel.storage.storageDescription()
                font.pointSize: 10
            }
            RectButton {
                id: lastItem
                x: (parent.width - width)/2
                y: 170
                width: parent.width * 0.8
                text: "Change type"
                font.pointSize: 10
                onClicked: {}
            }
        }
    }

    FileDialog {
        id: fileDialog
        selectFolder: true
        function show() {
            fileDialog.folder = "file:///" + Qt.resolvedUrl( pwmodel.storage.storageDir() );
            fileDialog.open();
        }

        onAccepted: { pwmodel.storage.setDir(folder.toString().replace("file:///","")); }
    }


    transitions: Transition {
        PropertyAnimation {
            target: background
            property: "opacity"
            easing.type: Easing.InOutQuad
        }
        PropertyAnimation {
            target: menuBackground
            property: "x"
            easing.type: Easing.InOutQuad
        }
    }

    function show() { state = "shown"; }
    function close() { state = ""; }

    states: State {
        name: "shown"
        PropertyChanges { target: background; opacity: 0.6; }
        PropertyChanges {
            target: menuBackground
            x: 0
        }
    }
}
