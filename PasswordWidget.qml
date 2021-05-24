import QtQuick 2.0

Rectangle {
    id: mainRect
    radius: 5
    width: parent.width
    property int margin: 10
    height: 2*margin + titleRect.contentHeight

    property string title: ""
    signal clicked();

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

    MouseArea {
        anchors.fill: parent
        onClicked: mainRect.clicked();
    }
}
