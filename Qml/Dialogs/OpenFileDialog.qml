import QtQuick 2.14
import QtQuick.Dialogs 1.3

import Flux 1.0

import "../Actions"

FileDialog {
    id: rootOpenFileDialog
    objectName: "RootOpenFileDialog"

    title: qsTr( "Please choose a file" )

    folder: shortcuts.home
    nameFilters: [ "Logs (*.dat)" ]

    visible: applicationModel.dialog.showFileDialog

    onAccepted: {
        ActionProvider.showFileDialog( false );
        ActionProvider.openFile( rootOpenFileDialog.fileUrl );
    }

    onRejected: {
        ActionProvider.showFileDialog( false );
    }
}
