import QtQuick 2.14
import QtQuick.Controls 2.14

import "./Others"

import Flux 1.0
import Style 1.0

Item {
    id: rootEventTypesWindow
    objectName: "rootEventTypesWindow"

    property bool showFilterField: false

    width: parent.width

    focus: true

    Keys.onPressed: {
        if ( event.matches(StandardKey.Find) )
        {
            showFilterField = !showFilterField;
        }
    }

    FilterField {
        id: eventTypesFilterByName
        objectName: "EventTypesFilterByName"

        x: rootEventTypesWindowColumn.x
        y: eventTypesButtonBar.y + eventTypesButtonBar.height

        visible: showFilterField

        width: parent.width

        onVisibleChanged: if ( visible === true ) eventTypesFilterByName.forceActiveFocus()

        onTextChanged: ActionProvider.filterEventTypeName( eventTypesFilterByName.text );
    }

    Column {
        id: rootEventTypesWindowColumn
        objectName: "rootEventTypesWindowColumn"

        height: parent.height
        width: parent.width

        Header {
            id: fileterByEventTypeLabel
            objectName: "FileterByEventTypeLabel"

            text: "Events Type"
        }

        Rectangle {
            id: eventTypesButtonBar
            objectName: "EventTypesButtonBar"

            height: Style.eventFilterWidget.buttonBarHeight
            width: parent.width

            color: Style.eventFilterWidget.buttonBarColor

            Row {
                id: eventTypesButtonBarRow
                objectName: "EventTypesButtonBarRow"

                anchors.centerIn: parent

                spacing: Style.eventFilterWidget.buttonBarSpacing

                IconButton {
                    id: selectAllButton
                    objectName: "SelectAllButton"

                    enabled: !applicationModel.filters.running

                    iconPath: "qrc:/Icons/select_all.png"

                    text: qsTr( "Select All" )

                    onClicked: ActionProvider.filterByEventTypeSelectAll()
                }

                IconButton {
                    id: deselectAllButton
                    objectName: "DeselectAllButton"

                    enabled: !applicationModel.filters.running

                    iconPath: "qrc:/Icons/deselect_all.png"

                    text: qsTr( "Deselect All" )

                    onClicked: ActionProvider.filterByEventTypeDeselectAll()
                }
            }
        }

        Rectangle {
            id: emptyRectangle
            objectName: "EmptyRectangle"

            height: eventTypesFilterByName.visible ? eventTypesFilterByName.height : 0
            width: parent.width
        }

        ListView {
            id: eventTypesList
            objectName: "EventTypesList"

            height: parent.height - fileterByEventTypeLabel.height - eventTypesButtonBar.height - emptyRectangle.height
            width: parent.width

            clip: true

            model: applicationModel.filters.filteredEventTypes

            ScrollBar.vertical: ScrollBar { }

            delegate: CheckBox {

                enabled: occurence > 0

                checked: show

                text: id + ": " + name + " (" + occurence + ")"

                onClicked: ActionProvider.filterByEventType( id, checked )
            }

            Rectangle {
                id: noDataBackground
                objectName: "NoDataBackground"

                visible: applicationModel.data.noData

                anchors.fill: parent

                color: Style.eventFilterWidget.noDataBackgroundColor

                Text {
                    id: noDataLabel
                    objectName: "NoDataLabel"

                    anchors.centerIn: parent

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                    font.pixelSize: Style.eventFilterWidget.noDataFontSize

                    color: Style.eventFilterWidget.noDataTextColor

                    text: qsTr( "No data" )
                }
            }
        }
    }
}
