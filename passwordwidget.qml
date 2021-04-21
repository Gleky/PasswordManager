import QtQuick 2.0

Rectangle {
    id: mainRect
    radius: 5
    width: parent.width
    property int margin: 10
    height: 2*margin + titleRect.contentHeight

    property string title: ""

    Text {
        id: titleRect
        anchors.margins: margin
        anchors.top: mainRect.top
        anchors.left: mainRect.left
        anchors.right: mainRect.right

        color: "#ffffff"
        text: title
        font.pointSize: 14
    }

    TextInput {
        id: descriptionRect
        anchors.left: titleRect.left
        anchors.right: titleRect.right
        anchors.top: titleRect.bottom
        anchors.topMargin: margin

        color: "#ffffff"
        text: description
    }
}
