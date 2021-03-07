import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    title: qsTr("Password manager")
    visible: true
    width: 640
    height: 480

    ScrollView {
        anchors.fill: parent

        ListView {
            width: parent.width
            model: 20
            delegate: ItemDelegate {
                text: "Item " + (index + 1)
                width: parent.width
            }
        }
    }
}
