import QtQuick 2.14
import QtQuick.Controls 2.14

import Style 1.0

ListView {
    id: rootEventsList
    objectName: "RootEventsList"

    model: applicationModel.data.eventsList

    ScrollBar.vertical: ScrollBar { }

    delegate: EventDelegate { }

    Text {
        id: noDataLabel
        objectName: "NoDataLabel"

        visible: applicationModel.data.noData

        anchors.centerIn: parent

        font.pixelSize: Style.eventsList.noDataFontSize
        color: Style.eventsList.noDataFontColor

        text: "To open a new document select FILE > OPEN or press CTRL + O"
    }
}
