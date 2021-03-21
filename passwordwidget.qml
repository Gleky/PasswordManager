import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    radius: 5
    width: parent.width
    property int margin: 5
    implicitHeight: layout.implicitHeight + 2*margin

    property string title: ""
    property string description: ""
    property string login: ""
    property string password: ""

    MouseArea {
        anchors.fill: parent
        onClicked: parent.state = "expanded";
    }

    ColumnLayout {
        id: layout
        anchors.margins: margin
        anchors.fill: parent
        spacing: 5

        TextInput {
            Layout.fillWidth: true
            color: "#ffffff"
            text: title
            font.pointSize: 12
            onAccepted: {title = text; focus = false;}
        }

        TextInput {
            Layout.fillWidth: true
            color: "#ffffff"
            text: description
            onAccepted: {description = text; focus = false;}
        }

        RowLayout {
            id: logpas
            visible: false
            Layout.fillWidth: true
            spacing: 5
            TextInput {
                Layout.fillWidth: true
                color: "#ffffff"
                text: login
                onAccepted: {login = text; focus = false;}
            }
            TextInput {
                Layout.fillWidth: true
                color: "#ffffff"
                text: password
                onAccepted: {password = text; focus = false;}
            }
        }
    }

    states: [
        State {
            name: "expanded"
            PropertyChanges {target: logpas; visible: true;}
        }
    ]
}
