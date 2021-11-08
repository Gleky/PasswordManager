import QtQuick 2.12
import QtQuick.Controls 2.5
import QmlQClipboard 1.0


Item {
    id: mainItem

    property string title
    property string login
    property string password
    property int idx: -1

    signal save()
    signal remove()

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
        onClicked: { mainItem.close(); }
    }

    Rectangle {
        id: cardBackground
        anchors.verticalCenter: mainItem.verticalCenter
        anchors.horizontalCenter: mainItem.horizontalCenter
        color: "#404040"
        width: 400
        radius: 5
        height: titleText.anchors.topMargin +
                titleText.height +
                loginText.anchors.topMargin +
                loginText.height +
                passwordText.anchors.topMargin +
                passwordText.height

        MouseArea {
            anchors.fill: parent
            onClicked: {}
        }

        TextField {
            id: titleText
            text: title
            placeholderText: "title"
            onEditingFinished: { title = text; }

            color: "#ffffff"
            font.pointSize: 18
            horizontalAlignment: Qt.AlignHCenter
            readOnly: true

            anchors.margins: 10
            anchors.top: cardBackground.top
            anchors.left: cardBackground.left
            anchors.right: cardBackground.right

            background: {}
        }

        TextField {
            id: loginText
            text: login
            placeholderText: "login"
            onEditingFinished: { login = text; }

            color: "#ffffff"
            font.pointSize: 14
            horizontalAlignment: Qt.AlignHCenter
            readOnly: true

            anchors.topMargin: 15
            anchors.top: titleText.bottom
            anchors.left: titleText.left
            anchors.right: titleText.right

            background: {}
        }

        TextField {
            id: passwordText
            text: password
            placeholderText: "password"
            onEditingFinished: { password = text; Clipboard.copy(""); }

            color: "#ffffff"
            font.pointSize: 14
            horizontalAlignment: Qt.AlignHCenter
            echoMode: TextInput.Password
            readOnly: true

            anchors.topMargin: 10
            anchors.top: loginText.bottom
            anchors.left: loginText.left
            anchors.right: loginText.right

            background: {}
        }

        RectButton {
            id: editButton
            icon.source: "qrc:///button_icons/edit.png"
            anchors.top: cardBackground.top
            anchors.right: cardBackground.right
            anchors.rightMargin: 5

            onClicked: {
                if (mainItem.state == "shown") mainItem.state = "editing";
                else if (mainItem.state == "editing" || mainItem.state == "creating"){
                    mainItem.state = "shown";
                    save();
                }
            }
        }

        RectButton {
            id: copyLoginButton
            icon.source: "qrc:///button_icons/copy.png"

            anchors.verticalCenter: loginText.verticalCenter
            anchors.right: editButton.right

            onPressedChanged: { Clipboard.copy(loginText.text); }
        }
        RectButton {
            id: copyPassButton
            icon.source: "qrc:///button_icons/copy.png"

            anchors.verticalCenter: passwordText.verticalCenter
            anchors.right: editButton.right

            onPressedChanged: { Clipboard.copy(passwordText.text); }
        }
        RectButton {
            id: showButton
            icon.source: "qrc:///button_icons/show_password.png"

            anchors.verticalCenter: passwordText.verticalCenter
            anchors.right: copyPassButton.left

            onPressedChanged: { pressed ? passwordText.echoMode = TextInput.Normal : passwordText.echoMode = TextInput.Password }
        }

        RectButton {
            id: removeButton
            icon.source: "qrc:///button_icons/remove.png"
            y: 0
            x: 5

            onClicked: { remove(); }
        }
    }

    function show() {
        state = "shown"
    }

    function close() {
        idx = -1;
        state = "";
        title = "";
        login = "";
        password = "";
        Clipboard.clear();
    }

    states: [
        State {
            name: "shown"
            PropertyChanges { target: mainItem; opacity: 1; }
        },
        State {
            name: "editing"
            extend: "shown"
            PropertyChanges { target: titleText; readOnly: false; }
            PropertyChanges { target: loginText; readOnly: false; }
            PropertyChanges { target: passwordText; readOnly: false; }
            PropertyChanges { target: editButton; icon.source: "qrc:///button_icons/save.png"; }
            PropertyChanges { target: cardBackground; color: "#483035"; }
        },
        State {
            name: "creating"
            extend: "editing"
            PropertyChanges { target: titleText; focus: true; }
        }
    ]

    transitions: Transition {
        PropertyAnimation { target: mainItem; property: "opacity"; easing.type: Easing.OutQuad}
        PropertyAnimation { target: cardBackground; property: "color"; easing.type: Easing.OutQuad}
    }

    onOpacityChanged: visible = (opacity != 0);
}
