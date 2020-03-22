import QtQuick 2.14

import Style 1.0
import Flux 1.0

import "../../Animations"

Item {
    id: rootGroupStatus
    objectName: "RootGroupStatus"

    property string icon: ""
    property int count: 0
    property int groupId: 0

    property bool hovered: false

    visible: count > 0

    height: parent.height
    width: Style.groupStatus.width

    Rectangle {
        id: groupStatusBackground
        objectName: "GroupStatusBackground"

        anchors.fill: parent

        color: rootGroupStatus.hovered === true ? Style.groupStatus.hoverColor : "transparent"
    }

    Item {
        id: groupStatusContent
        objectName: "GroupStatusContent"

        anchors.centerIn: parent

        height: parent.height
        width: groupStatusLabel.width + groupStatusIcon.width + groupStatusEndLabel.width + 4

        Text {
            id: groupStatusLabel
            objectName: "GroupStatusLabel"

            height: parent.height

            verticalAlignment: Text.AlignVCenter

            color: Style.statusBar.statusMessageColor
            font.pixelSize: Style.statusBar.fontSize

            text: qsTr( "Group" )
        }

        Image {
            id: groupStatusIcon
            objectName: "GroupStatusIcon"

            anchors.left: groupStatusLabel.right
            anchors.leftMargin: Style.groupStatus.iconLeftMargin
            anchors.top: parent.top
            anchors.topMargin: Style.groupStatus.iconTopMargin

            height: Style.groupStatus.iconSize
            width: Style.groupStatus.iconSize

            sourceSize.height: Style.groupStatus.iconSize
            sourceSize.width: Style.groupStatus.iconSize

            smooth: true

            source: icon
        }

        Text {
            id: groupStatusEndLabel
            objectName: "GroupStatusEndLabel"

            anchors.left: groupStatusIcon.right
            anchors.leftMargin: Style.groupStatus.textLeftMargin
            anchors.top: parent.top

            height: parent.height

            verticalAlignment: Text.AlignVCenter

            color: Style.statusBar.statusMessageColor
            font.pixelSize: Style.statusBar.fontSize

            text: qsTr( ": " ) +  count + qsTr( " element(s)" )
        }
    }

    MouseArea {
        id: groupStatusMouseArea
        objectName: "GroupStatusMouseArea"

        anchors.fill: parent

        hoverEnabled: true

        onContainsMouseChanged: rootGroupStatus.hovered = containsMouse

        onClicked: ActionProvider.clearGroup( groupId );
    }

    Behavior on visible { FadeAnimation { target: rootGroupStatus; fadeDuration: 500 } }
}
