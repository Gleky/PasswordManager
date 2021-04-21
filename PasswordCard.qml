import QtQuick 2.12


Item {
    id: mainItem

    property string title
    property string login
    property string password

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
        onClicked: mainItem.close()
    }

    Rectangle {
        id: cardBackground
        anchors.verticalCenter: mainItem.verticalCenter
        anchors.horizontalCenter: mainItem.horizontalCenter
        color: "#404040"
        width: 400
        height: titleText.anchors.topMargin * 2 +
                titleText.contentHeight +
                loginText.anchors.topMargin +
                loginText.contentHeight +
                passwordText.anchors.topMargin +
                passwordText.contentHeight

        TextInput {
            id: titleText
            text: title

            color: "#ffffff"
            font.pointSize: 18
            horizontalAlignment: Qt.AlignHCenter

            anchors.margins: 15
            anchors.top: cardBackground.top
            anchors.left: cardBackground.left
            anchors.right: cardBackground.right
        }

        TextInput {
            id: loginText
            text: login

            color: "#ffffff"
            font.pointSize: 14
            horizontalAlignment: Qt.AlignHCenter

            anchors.topMargin: 20
            anchors.top: titleText.bottom
            anchors.left: titleText.left
            anchors.right: titleText.right
        }

        TextInput {
            id: passwordText
            text: password

            color: "#ffffff"
            font.pointSize: 14
            horizontalAlignment: Qt.AlignHCenter
            echoMode: TextInput.Password

            anchors.topMargin: 10
            anchors.top: loginText.bottom
            anchors.left: loginText.left
            anchors.right: loginText.right
        }
    }

    function show() {
        state = "shown"
    }

    function close() {
        state = ""
    }

    states: [
        State {
            name: "shown"
            PropertyChanges { target: mainItem; opacity: 1; }
        }
    ]

    transitions: Transition {
        PropertyAnimation { target: mainItem; property: "opacity"; easing.type: Easing.OutQuad}
    }

    onOpacityChanged: visible = (opacity != 0);
}
