import QtQuick 2.14
import QtQuick.Controls 2.14

import Flux 1.0
import Style 1.0

TextField {
    id: rootFilterField
    objectName: "RootFilterField"

    width: parent.width

    leftPadding: Style.filterField.leftPadding
    rightPadding: Style.filterField.rightPadding
    topPadding: Style.filterField.topPadding

    font.pixelSize: Style.filterField.fontSize

    placeholderText: qsTr( "Search" )

    enabled: true
    readOnly: !visible

    z: Style.filterField.z

    maximumLength: 25

    background: Rectangle {
        id: filterFieldBackground
        objectName: "FilterFieldBackground"

        border.width: Style.filterField.borderWidth
        border.color: Style.filterField.borderColor

        color: Style.filterField.backgroundColor
    }

    Image {
        id: clearFilterField
        objectName: "ClearFilterField"

        visible: parent.activeFocus || rootFilterField.text.length > 0

        anchors.right: parent.right
        anchors.rightMargin: Style.filterField.clearButtonRightPadding

        anchors.verticalCenter: parent.verticalCenter

        height: Style.filterField.clearButtonSize
        width: Style.filterField.clearButtonSize

        sourceSize.height: Style.filterField.clearButtonSize
        sourceSize.width: Style.filterField.clearButtonSize

        source: rootFilterField.text.length > 0 ? "qrc:/Icons/delete_highlighted.svg" : "qrc:/Icons/delete.svg"

        MouseArea {
            id: clearFilterFieldMouseArea
            objectName: "ClearFilterFieldMouseArea"

            anchors.fill: parent

            hoverEnabled: true

            onClicked: rootFilterField.clear()
        }
    }
}
