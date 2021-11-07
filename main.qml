import QtQuick 2.12
import QtQuick.Controls 2.5

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
        onStoredSuccessfully: encryptedfs.removeFile();
    }

    EncryptedFileStorage {
        id:encryptedfs
        onAskPassPhrase: {
            if (fileFound())passwordInput.askKey();
            else passwordInput.setKey();
        }
        onPassPhraseAccepted: {
            if (accepted) passwordInput.close();
            else passwordInput.showPasswordIsWrong();
        }
        onNeedLoad: pwmodel.load();
        onNeedStore: pwmodel.save();
        onStoredSuccessfully: fs.removeFile();
    }

    PasswordModel {
        id: pwmodel
        storage: findStorage()
        Component.onCompleted: load();
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
        height: newButton.height

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        color: "#303030"

        RectButton {
            id: newButton
            anchors.margins: 7
            anchors.right: parent.right
            anchors.top: parent.top

            rectHeight: 40
            rectWidth: 40

            text: "+"
            font.pointSize: 18

            onClicked: {
                card.show();
                card.state = "creating"
            }
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

    SettingsWidget {
        id: settings
        storages: [encryptedfs, fs]
    }

    RectButton {
        id: menuButton
        anchors.margins: newButton.anchors.margins
        anchors.left: parent.left
        anchors.top: parent.top

        rectHeight: newButton.rectHeight
        rectWidth: newButton.rectWidth

        icon.source: "qrc:///button_icons/menu.png"

        onClicked: {
            if (settings.visible) settings.close();
            else settings.show();
        }
    }

    StoragePasswordInput {
        id:passwordInput
        onAccept: { encryptedfs.passPhrase = password; }
    }

    function findStorage() {
        if (fs.fileFound()) return fs;
        return encryptedfs; //default storage
    }
}
