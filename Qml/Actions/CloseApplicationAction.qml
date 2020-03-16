import QtQuick 2.14
import QtQuick.Controls 2.14

import Flux 1.0

Action {
    id: closeApplicationAction
    objectName: "CloseApplicationAction"

    text: qsTr( "&Exit" )
    shortcut: StandardKey.Exit

    onTriggered: Qt.quit()
}
