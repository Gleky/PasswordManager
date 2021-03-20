import QtQuick 2.12
import QtQuick.Controls 2.5

import passwordmodel 1.0
import filestorage 1.0


ApplicationWindow {
    title: qsTr("Password manager")
    visible: true
    width: 640
    height: 480

    FileStorage{
        id:fstorage
    }

    PasswordModel {
        id: pwmodel
        storage: fstorage
    }

    ListView {
        anchors.fill: parent
        spacing: 10

        leftMargin: 10
        rightMargin: 10
        topMargin: 10
        bottomMargin: 10

        model: pwmodel
        delegate: PasswordWidget {
            title: pwTitle
            description: pwDescription
            login: pwLogin
            password: pwPassword
        }
    }
}
