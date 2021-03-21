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

    ColumnLayout {
        id: layout
        anchors.margins: margin
        anchors.fill: parent
        spacing: 5

        Text {
            Layout.fillWidth: true
            color: "#ffffff"
            text: title
            font.pointSize: 12
        }

        Text {
            Layout.fillWidth: true
            color: "#ffffff"
            text: description
        }

        RowLayout {
            id: logpas
            visible: false
            Layout.fillWidth: true
            spacing: 5
            Text {
                Layout.fillWidth: true
                text: login
            }
            Text {
                Layout.fillWidth: true
                text: password
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: parent.state == 'clicked' ? parent.state = "" : parent.state = 'clicked';
    }

    states: [
        State {
            name: "clicked"
            PropertyChanges {target: logpas; visible: true;}
        }
    ]
}
