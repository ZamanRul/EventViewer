import QtQuick 2.0
import QtQuick.Controls 2.14

Item {
    id: rootFilterPane
    objectName: "RootFilterPane"

    Column {
        id: filterPaneColumn
        objectName: "FilterPaneColumn"

        height: parent.height
        width: parent.width

        TimeWindow {
            id: timeWindow
            objectName: "TimeWindow"
        }

        EventTypesWindow {
            id: eventTypesWindow
            objectName: "EventTypesWindow"

            height: parent.height - timeWindow.height
        }
    }
}
