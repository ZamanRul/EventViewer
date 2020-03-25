import QtQuick 2.14
import QtQuick.Controls 2.14

import Flux 1.0

Action {
    id: openCompareAction
    objectName: "OpenCompareAction"

    shortcut: "F2"

    text: qsTr( "C&ompare ..." )

    onTriggered: ActionProvider.showCompareDialog( true );
}
