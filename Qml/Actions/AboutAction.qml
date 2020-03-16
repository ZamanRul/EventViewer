import QtQuick 2.14
import QtQuick.Controls 2.14

import Flux 1.0

Action {
    id: aboutAction
    objectName: "AboutAction"

    text: qsTr( "&About" )
    shortcut: StandardKey.HelpContents

    onTriggered: ActionProvider.showAboutDialog( true );
}
