import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle{
    color: "#77a6ad"
    radius: 5

    property string title: ""
    property string description: ""
    property string login: ""
    property string password: ""

    ColumnLayout {
        id: layout
        anchors.fill: parent
        spacing: 5

        Text {
            color: "#ffffff"
            text: title
            font.pointSize: 12
        }

        Text {
            color: "#ffffff"
            text: description
        }

        RowLayout{
            Text {
                text: login
            }
            Text {
                text: password
            }
        }
    }

    width: parent.width
    height: layout.implicitHeight
}
