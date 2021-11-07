import QtQuick 2.12
import QtQuick.Controls 2.5


Item {
    id: mainItem

    property string password

    signal accept()

    anchors.fill: parent
    opacity: 0
    visible: false

    Rectangle {
        id: background
        anchors.fill: parent
        color: "#202020"
        opacity: 0.5
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {}
    }

    Rectangle {
        id: cardBackground
        anchors.verticalCenter: mainItem.verticalCenter
        anchors.horizontalCenter: mainItem.horizontalCenter
        color: "#404040"
        width: 400
        radius: 5
        height: passphraseText.anchors.topMargin * 2 +
                passphraseText.height +
                cardTitle.contentHeight +
                acceptButton.height +
                passphraseTextConfirm.visible*passphraseTextConfirm.height

        Text {
            id: cardTitle
            text: "Input storage key"
            color: "#ffffff"
            font.pointSize: 16
            y: 5
            x: (parent.width - width)/2
        }

        Rectangle {
            id: passphraseBackground
            color: "#fb0d0d"
            radius: 5
            opacity: 0
            anchors.fill: passphraseText

            PropertyAnimation {
                id: wrongKey
                target: passphraseBackground;
                to: 0.3
                duration: 100
                property: "opacity";
                easing.type: Easing.InQuad
                onFinished: { wrongKey_end.start(); }
            }
            PropertyAnimation {
                id: wrongKey_end
                target: passphraseBackground;
                to: 0
                duration: 600
                property: "opacity";
                easing.type: Easing.OutQuad
            }
        }

        TextField {
            id: passphraseText
            onEditingFinished: { password = text; }

            color: "#ffffff"
            font.pointSize: 16
            horizontalAlignment: Qt.AlignHCenter
            echoMode: TextInput.Password
            focus: true
            placeholderText: "key"

            background: {}

            anchors.margins: 5
            anchors.top: cardTitle.bottom
            anchors.left: cardBackground.left
            anchors.right: cardBackground.right

            Keys.onReturnPressed: { password = text; checkAccept(); }
        }

        TextField {
            id: passphraseTextConfirm
            onEditingFinished: { password = text; }

            color: "#ffffff"
            font.pointSize: 16
            horizontalAlignment: Qt.AlignHCenter
            echoMode: TextInput.Password
            visible: false
            focus: false
            placeholderText: "confirm key"

            background: {}

            anchors.topMargin: -5
            anchors.top: passphraseText.bottom
            anchors.left: cardBackground.left
            anchors.right: cardBackground.right

            Keys.onReturnPressed: { password = text; checkAccept(); }
        }

        RectButton {
            id: acceptButton
            text: "Proceed"
            y: parent.height - height - 5
            x: (parent.width - width)/2

            Keys.onReturnPressed: { checkAccept(); }
            onClicked: { checkAccept(); }
        }
    }

    function askKey() {
        state = "key_input"
    }

    function setKey() {
        state = "key_set"
    }

    function close() {
        state = "";
        password = "";
    }

    function showPasswordIsWrong() {
        wrongKey.start();
        shakeInputText();
    }

    function shakeInputText() {

    }

    function checkAccept() {
        if (state !== "key_set") {
            accept();
            return;
        }
        if (passphraseText.text === passphraseTextConfirm.text) accept();
        else showPasswordIsWrong();
    }

    states: [
        State {
            name: "key_input"
            PropertyChanges { target: mainItem; opacity: 1; }
        },
        State {
            name: "key_set"
            extend: "key_input"
            PropertyChanges { target: cardTitle; text: "Set storage key"; }
            PropertyChanges { target: passphraseTextConfirm; visible: true; }
            PropertyChanges { target: passphraseText; focus: true; }
        }
    ]

    transitions: Transition {
        PropertyAnimation { target: mainItem; property: "opacity"; easing.type: Easing.OutQuad}
        PropertyAnimation { target: cardBackground; property: "color"; easing.type: Easing.OutQuad}
    }

    onOpacityChanged: visible = (opacity != 0);
}
