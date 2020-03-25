import QtQuick 2.0

import Style 1.0

Rectangle {
    id: rootComparisonHeader
    objectName: "RootComparisonHeader"

    height: Style.comparisonHeader.height
    width: parent.width

    color: Style.comparisonHeader.backgroundColor

    Row {
        id: comparisonHeaderRow
        objectName: "ComparisonHeaderRow"

        height: parent.height
        width: parent.width

        Item {
            id: leftGroupHeader
            objectName: "LeftGroupHeader"

            height: parent.height
            width: Style.comparisonHeader.leftGroupHeaderFill * parent.width

            Text {
                id: leftGroupHeaderText
                objectName: "LeftGroupHeaderText"

                anchors.centerIn: parent

                font.pixelSize: Style.comparisonHeader.fontSize
                color: Style.comparisonHeader.fontColor

                text: qsTr( "Group A" )
            }
        }

        Item {
            id: typeGroupHeader
            objectName: "TypeGroupHeader"

            height: parent.height
            width: Style.comparisonHeader.typeGroupHeaderFill * parent.width

            Text {
                id: typeGroupHeaderText
                objectName: "TypeGroupHeaderText"

                anchors.centerIn: parent

                font.pixelSize: Style.comparisonHeader.fontSize
                color: Style.comparisonHeader.fontColor

                text: qsTr( "Type" )
            }

            Rectangle {
                id: leftBorder
                objectName: "LeftBorder"

                anchors.left: parent.left

                height: parent.height
                width: Style.comparisonHeader.borderSize

                color: Style.comparisonHeader.borderColor
            }

            Rectangle {
                id: rightBorder
                objectName: "RightBorder"

                anchors.right: parent.right

                height: parent.height
                width: Style.comparisonHeader.borderSize

                color: Style.comparisonHeader.borderColor
            }
        }

        Item {
            id: rightGroupHeader
            objectName: "RightGroupHeader"

            height: parent.height
            width: Style.comparisonHeader.rightGroupHeaderFill * parent.width

            Text {
                id: rightGroupHeaderText
                objectName: "RightGroupHeaderText"

                anchors.centerIn: parent

                font.pixelSize: Style.comparisonHeader.fontSize
                color: Style.comparisonHeader.fontColor

                text: qsTr( "Group B" )
            }
        }
    }

    Rectangle {
        id: bottomBorder
        objectName: "BottonBorder"

        anchors.bottom: parent.bottom

        height: Style.comparisonHeader.borderSize
        width: parent.width

        color: Style.comparisonHeader.borderColor
    }
}
