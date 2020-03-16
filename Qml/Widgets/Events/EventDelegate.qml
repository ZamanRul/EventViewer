import QtQuick 2.0

import Style 1.0

Rectangle {
    id: rootEventDelegate
    objectName: "RootEventDelegate"

    height: Style.eventDelegate.height
    width: parent.width

    color: index % 2 == 0 ? Style.eventDelegate.evenBackgroundColor : Style.eventDelegate.oddBackgroundColor

    Row {
        id: rowEventDelegate
        objectName: "RowEventDelegate"

        height: parent.height

        Text {
            id: eventDelegateFieldOne

            height: parent.height
            width: Style.eventDelegate.column1Aspect * rootEventDelegate.width

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            elide: Text.ElideRight

            font.pixelSize: Style.eventDelegate.fontSize

            color: Style.eventDelegate.fontColor

            text: time
        }

        Text {
            id: eventDelegateFieldTwo

            height: parent.height
            width: Style.eventDelegate.column2Aspect * rootEventDelegate.width

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            elide: Text.ElideRight

            font.pixelSize: Style.eventDelegate.fontSize

            color: Style.eventDelegate.fontColor

            text: type
        }

        Text {
            id: eventDelegateFieldThree

            height: parent.height
            width: Style.eventDelegate.column3Aspect * rootEventDelegate.width

            verticalAlignment: Text.AlignVCenter

            elide: Text.ElideRight

            font.pixelSize: Style.eventDelegate.fontSize

            color: Style.eventDelegate.fontColor

            text: target
        }

        Text {
            id: eventDelegateFieldFour

            height: parent.height
            width: Style.eventDelegate.column4Aspect * rootEventDelegate.width

            verticalAlignment: Text.AlignVCenter

            elide: Text.ElideRight

            font.pixelSize: Style.eventDelegate.fontSize

            color: Style.eventDelegate.fontColor

            text: description
        }
    }
}
