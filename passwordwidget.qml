import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: mainRect
    radius: 5
    width: parent.width
    property int margin: 10
    height: margin + logpas.y - titleRect.y + logpas.height

    property string title: ""
    property string description: ""
    property string login: ""
    property string password: ""

    TextInput {
        id: titleRect
        anchors.margins: margin
        anchors.top: mainRect.top
        anchors.left: mainRect.left
        anchors.right: mainRect.right

        color: "#ffffff"
        text: title
        font.pointSize: 14
        onAccepted: {title = text; focus = false;}
    }

    TextInput {
        id: descriptionRect
        anchors.left: titleRect.left
        anchors.right: titleRect.right
        anchors.top: titleRect.bottom
        anchors.topMargin: margin

        color: "#ffffff"
        text: description
        onAccepted: {description = text; focus = false;}
    }

    RowLayout {
        id: logpas
        anchors.top: descriptionRect.bottom
        anchors.topMargin: margin
        anchors.left: titleRect.left
        anchors.right: titleRect.right

        opacity: 0
        spacing: 5
        height: 0

        TextInput {
            Layout.alignment: Qt.AlignTop
            id: loginRect
            color: "#ffffff"
            height: logpas.height
            text: login
            onAccepted: {login = text; focus = false;}
        }
        TextInput {
            Layout.alignment: Qt.AlignTop
            color: "#ffffff"
            height: logpas.height
            text: password
            onAccepted: {password = text; focus = false;}
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: parent.state = "expanded";
    }

    states: [
        State {
            name: "expanded"
            PropertyChanges {target: logpas; visible: true; opacity: 1; height: loginRect.contentHeight + margin;}
            PropertyChanges {target: mouseArea; visible: false;}
        }
    ]

    transitions: Transition {
            PropertyAnimation { target: logpas; property: "opacity"; easing.type: Easing.OutQuad}
            PropertyAnimation { target: logpas; property: "height"; easing.type: Easing.OutQuad}
        }
}
