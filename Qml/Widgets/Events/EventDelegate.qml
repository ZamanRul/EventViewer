import QtQuick 2.0

import Style 1.0
import Flux 1.0

Rectangle {
    id: rootEventDelegate
    objectName: "RootEventDelegate"

    property var view: ListView.view

    height: Style.eventDelegate.height
    width: parent.width

    color: index % 2 == 0 ? Style.eventDelegate.evenBackgroundColor : Style.eventDelegate.oddBackgroundColor

    Row {
        id: rowEventDelegate
        objectName: "RowEventDelegate"

        height: parent.height

        Item {
            id: eventDelegateFieldZero

            height: parent.height
            width: Style.eventDelegate.column0Aspect * rootEventDelegate.width

            Image {
                id: groupAIcon

                visible: group === 65

                anchors.centerIn: parent

                height: Style.eventDelegate.groupIconSize
                width: Style.eventDelegate.groupIconSize

                sourceSize.height: Style.eventDelegate.groupIconSize
                sourceSize.width: Style.eventDelegate.groupIconSize

                smooth: true

                source: "qrc:/Icons/a_purple.svg"
            }

            Image {
                id: groupBIcon

                visible: group === 66

                anchors.centerIn: parent

                height: Style.eventDelegate.groupIconSize
                width: Style.eventDelegate.groupIconSize

                sourceSize.height: Style.eventDelegate.groupIconSize
                sourceSize.width: Style.eventDelegate.groupIconSize

                smooth: true

                source: "qrc:/Icons/b_purple.svg"
            }
        }

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

    MouseArea {
        id: eventDelegateMouseArea
        objectName: "EventDelegateMouseArea"

        anchors.fill: parent

        onClicked:
        {
            if( view.pressedA )
            {
                ActionProvider.addToGroup( index, 65 );
            }
            else if ( view.pressedB )
            {
                ActionProvider.addToGroup( index, 66 );
            }
        }
    }
}
