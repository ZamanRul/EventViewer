import QtQuick 2.0

import Style 1.0

import "../Others"

Item {
    id: rootComparisonDelegate
    objectName: "RootComparisonDelegate"

    readonly property int operationEqual: 0
    readonly property int operationOnlyLeft: 1
    readonly property int operationOnlyRight: 2
    readonly property int operationSimilar: 3

    height: Style.comparisonDelegate.height
    width: parent.width

    Row {
        id: rootComparisonRow
        objectName: "RootComparisonRow"

        height: parent.height
        width: parent.width

        Rectangle {
            id: leftGroup
            objectName: "LeftGroup"

            height: parent.height
            width: Style.comparisonDelegate.leftGroupFill * parent.width

            color: {
                if ( operation === rootComparisonDelegate.operationOnlyRight )
                    return "transparent";
                else if ( index % 2 == 0 )
                    return Style.comparisonDelegate.evenBackgroundColor;
                else
                    return Style.comparisonDelegate.oddBackgroundColor;
            }

            Row {
                id: leftGroupRow
                objectName: "leftGroupRow"

                height: parent.height
                width: parent.width

                TableTextField {
                    id: leftTimeField
                    objectName: "LeftTimeField"

                    width: Style.comparisonDelegate.leftTimeFieldFill * parent.width

                    inactive: true

                    text: leftTime
                }

                TableTextField {
                    id: leftTargetField
                    objectName: "LeftTargetField"

                    width: Style.comparisonDelegate.leftTargetFieldFill * parent.width

                    text: leftTarget
                }

                TableTextField {
                    id: leftDescriptionField
                    objectName: "LeftDescriptionField"

                    width: Style.comparisonDelegate.leftDescriptionFill * parent.width

                    text: leftDescription
                }
            }
        }

        Rectangle {
            id: typeGroup
            objectName: "TypeGroup"

            height: parent.height
            width: Style.comparisonDelegate.typeGroupFill * parent.width

            color: ( index % 2 == 0 ) ? Style.comparisonDelegate.evenBackgroundColor : Style.comparisonDelegate.oddBackgroundColor

            Rectangle {
                id: typeGroupBackground
                objectName: "TypeGroupBackground"

                anchors.fill: parent

                opacity: Style.comparisonDelegate.typeGroupBackgroundOpacity

                color: {
                    if ( operation === rootComparisonDelegate.operationEqual )
                        return "green";
                    else if ( operation === rootComparisonDelegate.operationSimilar )
                        return "red";
                    else
                        return "transparent";
                }
            }

            TableTextField {
                id: typeTextField
                objectName: "TypeTextField"

                anchors.fill: parent

                font.bold: true
                font.pixelSize: Style.comparisonDelegate.typeFontSize

                text: type
            }

            Rectangle {
                id: leftBorder
                objectName: "LeftBorder"

                anchors.left: parent.left

                height: parent.height
                width: Style.comparisonDelegate.borderSize

                color: Style.comparisonDelegate.borderColor
            }

            Rectangle {
                id: rightBorder
                objectName: "RightBorder"

                anchors.right: parent.right

                height: parent.height
                width: Style.comparisonDelegate.borderSize

                color: Style.comparisonDelegate.borderColor
            }
        }

        Rectangle {
            id: rightGroup
            objectName: "RightGroup"

            height: parent.height
            width: Style.comparisonDelegate.rightGroupFill * parent.width

            color: {
                if ( operation === rootComparisonDelegate.operationOnlyLeft )
                    return "transparent";
                else if ( index % 2 == 0 )
                    return Style.comparisonDelegate.evenBackgroundColor;
                else
                    return Style.comparisonDelegate.oddBackgroundColor;
            }

            Row {
                id: rightGroupRow
                objectName: "RightGroupRow"

                height: parent.height
                width: parent.width

                TableTextField {
                    id: rightTimeField
                    objectName: "RightTimeField"

                    width: Style.comparisonDelegate.rightTimeFieldFill * parent.width

                    inactive: true

                    text: rightTime
                }

                TableTextField {
                    id: rightTargetField
                    objectName: "RightTargetField"

                    width: Style.comparisonDelegate.rightTargetFieldFill * parent.width

                    text: rightTarget
                }

                TableTextField {
                    id: rightDescriptionField
                    objectName: "RightDescriptionField"

                    width: Style.comparisonDelegate.rightDescriptionFieldFill * parent.width

                    text: rightDescription
                }
            }
        }
    }
}
