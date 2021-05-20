import QtQuick 2.12
import QtQuick.Controls 2.5


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
        height: titleText.anchors.topMargin * 2 +
                titleText.contentHeight +
                loginText.anchors.topMargin +
                loginText.contentHeight +
                passwordText.anchors.topMargin +
                passwordText.contentHeight

        MouseArea {
            anchors.fill: parent
            onClicked: {}
        }

        TextInput {
            id: titleText
            text: title
            onEditingFinished: { title = text; }

            color: "#ffffff"
            font.pointSize: 18
            horizontalAlignment: Qt.AlignHCenter
            readOnly: true

            anchors.margins: 15
            anchors.top: cardBackground.top
            anchors.left: cardBackground.left
            anchors.right: cardBackground.right
        }

        TextInput {
            id: loginText
            text: login
            onEditingFinished: { login = text; }

            color: "#ffffff"
            font.pointSize: 14
            horizontalAlignment: Qt.AlignHCenter
            readOnly: true

            anchors.topMargin: 20
            anchors.top: titleText.bottom
            anchors.left: titleText.left
            anchors.right: titleText.right
        }

        TextInput {
            id: passwordText
            text: password
            onEditingFinished: { password = text; }

            color: "#ffffff"
            font.pointSize: 14
            horizontalAlignment: Qt.AlignHCenter
            echoMode: TextInput.Password
            readOnly: true

            anchors.topMargin: 10
            anchors.top: loginText.bottom
            anchors.left: loginText.left
            anchors.right: loginText.right
        }

        RectButton {
            id: editButton
            text: "Edit"
            y: 5
            x: parent.width - width - y

            onClicked: {
                if (mainItem.state == "shown") mainItem.state = "editing";
                else if (mainItem.state == "editing"){
                    mainItem.state = "shown";
                    save();
                }
            }
        }

        RectButton {
            id: showButton
            text: "show"

            anchors.verticalCenter: passwordText.verticalCenter
            anchors.right: editButton.right

            onPressedChanged: { pressed ? passwordText.echoMode = TextInput.Normal : passwordText.echoMode = TextInput.Password }
        }

        RectButton {
            id: removeButton
            text: "Remove"
            y: 5
            x: y

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
            PropertyChanges { target: editButton; text: "save"; }
            PropertyChanges { target: cardBackground; color: "#483035"; }
        }
    ]

    transitions: Transition {
        PropertyAnimation { target: mainItem; property: "opacity"; easing.type: Easing.OutQuad}
        PropertyAnimation { target: cardBackground; property: "color"; easing.type: Easing.OutQuad}
    }

    onOpacityChanged: visible = (opacity != 0);
}
