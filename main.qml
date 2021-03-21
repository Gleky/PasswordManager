import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import passwordmodel 1.0
import filestorage 1.0


ApplicationWindow {
    title: qsTr("Password manager")
    visible: true
    width: 600
    height: 800

    FileStorage{
        id:fstorage
    }

    PasswordModel {
        id: pwmodel
        storage: fstorage
    }

    ColumnLayout
    {
        anchors.fill: parent

        Rectangle {
            Layout.fillWidth: true
            height: 30
            color: "#424551"

            Button {
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: 60
                text: "Add"

                onClicked: pwmodel.addNew()
            }

            Button {
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: 60
                text: "Save"
            }
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true

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

                onTitleChanged: model.pwTitle = title;
                onDescriptionChanged: model.pwDescription = description
                onLoginChanged: model.pwLogin = login;
                onPasswordChanged: model.pwPassword = password
            }
        }
    }
}
