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
            color: topBar.color
            title: pwTitle
            description: pwDescription

            onTitleChanged: model.pwTitle = title;
            onDescriptionChanged: model.pwDescription = description
        }
    }

    Rectangle {
        id: topBar
        height: 30

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        color: "#404040"

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

            onClicked: pwmodel.save()
        }
    }
}
