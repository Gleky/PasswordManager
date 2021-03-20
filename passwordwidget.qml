import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle{
    color: "#77a6ad"
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

        RowLayout{
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
}
