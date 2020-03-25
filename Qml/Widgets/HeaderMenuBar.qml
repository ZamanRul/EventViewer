import QtQuick 2.0
import QtQuick.Controls 2.14

import "../Actions"

MenuBar {

    Menu {
        title: qsTr( "&File" )

        OpenFileAction { }
        MenuSeparator { }
        CloseApplicationAction { }
    }

    Menu {
        title: qsTr( "&Comparisons" )

        OpenCompareAction { }
    }

    Menu {
        title: qsTr( "&Help" )

        AboutAction { }
    }
}

