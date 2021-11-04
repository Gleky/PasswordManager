import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

import passwordmodel 1.0
import filestorage 1.0
import encryptedfilestorage 1.0


ApplicationWindow {
    title: qsTr("Password manager")
    visible: true
    width: 600
    height: 800

    FileStorage{
        id:fs
    }

    EncryptedFileStorage{
        id:encryptedfs
    }

    PasswordModel {
        id: pwmodel
        storage: fs
    }

    ListView {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: topBar.bottom

        spacing: 10
        leftMargin: 10
        rightMargin: 10
        topMargin: 10
        bottomMargin: 10

        model: pwmodel
        delegate: PasswordWidget {
            color: "#404040"
            title: pwTitle

            onClicked: {
                card.idx = index;
                card.title = pwTitle;
                card.login = pwLogin;
                card.password = pwPassword;
                card.show();
            }
        }
    }

    Rectangle {
        id: topBar
        height: 30

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        color: "#303030"

        Button {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 60
            text: "Add"

            onClicked: {
                card.show();
                card.state = "creating"
            }
        }

        Button {
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 60
            text: "Dir"

            onClicked: { fileDialog.show(); }
        }
    }

    PasswordCard {
        id: card
        onSave: {
            if (idx == -1) pwmodel.addNew(title,login,password);
            pwmodel.save();
            idx = pwmodel.rowCount()-1;
        }
        onRemove: {
            pwmodel.remove(idx);
            pwmodel.save();
            card.close();
        }

        onTitleChanged:    { pwmodel.setData(pwmodel.index(card.idx, 0), title,    PasswordModel.TitleRole) }
        onLoginChanged:    { pwmodel.setData(pwmodel.index(card.idx, 0), login,    PasswordModel.LoginRole) }
        onPasswordChanged: { pwmodel.setData(pwmodel.index(card.idx, 0), password, PasswordModel.PasswordRole) }
    }

    FileDialog {
        id: fileDialog
        selectFolder: true
        function show() {
            fileDialog.folder = "file:///" + Qt.resolvedUrl( fstorage.storageDir() );
            fileDialog.open();
        }

        onAccepted: { fstorage.setDir(folder.toString().replace("file:///","")); }
    }
}
