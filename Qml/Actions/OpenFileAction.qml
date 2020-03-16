import QtQuick 2.14
import QtQuick.Controls 2.14

import Flux 1.0

Action {
    id: openFileAction
    objectName: "OpenFileAction"

    text: qsTr( "&Open" )
    shortcut: StandardKey.Open

    onTriggered: ActionProvider.showFileDialog( true );
}
