import QtQuick 2.0
import QtQuick.Dialogs 1.2

Item {
    id: mainItem
    anchors.fill: parent
    visible: false;

    property int topBarHeight: 0

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

        width: 300
        x: -width

        color: "#353535"
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
