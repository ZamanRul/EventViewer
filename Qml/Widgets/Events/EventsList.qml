import QtQuick 2.14
import QtQuick.Controls 2.14

import Style 1.0

ListView {
    id: rootEventsList
    objectName: "RootEventsList"

    property bool pressedA: false
    property bool pressedB: false

    focus: true

    model: applicationModel.data.eventsList

    ScrollBar.vertical: ScrollBar { }

    delegate: EventDelegate { }

    Keys.onPressed: {
        if (event.key === Qt.Key_A)
        {
            pressedA = true;
            event.accepted = true;
        }
        else if ( event.key === Qt.Key_B )
        {
            pressedB = true;
            event.accepted = true;
        }
    }

    Keys.onReleased: { pressedA = false; pressedB = false; }

    Text {
        id: noDataLabel
        objectName: "NoDataLabel"

        visible: applicationModel.data.noData

        anchors.centerIn: parent

        font.pixelSize: Style.eventsList.noDataFontSize
        color: Style.eventsList.noDataFontColor

        text: "To open a new document select FILE > OPEN or press CTRL + O"
    }

    MouseArea {
        id: eventListFocusReceiver
        objectName: "EventListFocusReceiver"

        anchors.fill: parent
        propagateComposedEvents: true

        onClicked: { rootEventsList.focus = true; mouse.accepted = false; }
    }
}
