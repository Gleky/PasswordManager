import QtQuick 2.12
import QtQuick.Controls 2.5
import passwordmodel 1.0


ApplicationWindow {
    title: qsTr("Password manager")
    visible: true
    width: 640
    height: 480

    PasswordModel {
        id: pwmodel
    }

    ScrollView {
        anchors.fill: parent

        ListView {
            width: parent.width
            model: pwmodel
            delegate: ItemDelegate {
                width: parent.width
                text: "Animal: " + title + ", " + description
            }
        }
    }
}
