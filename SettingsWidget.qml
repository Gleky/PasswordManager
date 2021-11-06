import QtQuick 2.0
import QtQuick.Dialogs 1.2

Flickable {
    FileDialog {
        id: fileDialog
        selectFolder: true
        function show() {
            fileDialog.folder = "file:///" + Qt.resolvedUrl( pwmodel.storage.storageDir() );
            fileDialog.open();
        }

        onAccepted: { pwmodel.storage.setDir(folder.toString().replace("file:///","")); }
    }
}
