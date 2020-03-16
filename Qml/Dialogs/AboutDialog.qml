import QtQuick 2.0
import QtQuick.Controls 2.14

import Flux 1.0

import Style 1.0

Popup {
    id: rootAboutDialog
    objectName: "RootAboutDialog"

    x: Math.round( ( parent.width - width ) / 2 )
    y: Math.round( ( parent.height - height ) / 2 )

    width: Style.aboutPopup.width
    height: Style.aboutPopup.height

    parent: Overlay.overlay

    modal: true
    focus: true

    visible: applicationModel.dialog.showAboutDialog

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    onClosed: ActionProvider.showAboutDialog( false );

    Overlay.modal: Rectangle {
        color: Style.aboutPopup.overlayColor
    }

    Image {
        id: aboutDialogLeftBorder
        objectName: "aboutDialogLeftBorder"

        anchors.top: parent.top
        anchors.topMargin: Style.aboutPopup.ribbonTopMargin
        anchors.left: parent.left
        anchors.leftMargin: Style.aboutPopup.ribbonLeftMargin

        height: Style.aboutPopup.ribbonHeight
        width: Style.aboutPopup.ribbonWidth

        fillMode: Image.Tile

        source: "qrc:/Images/HeaderBackground.png"
    }

    Column {
        id: aboutDialogColumn
        objectName: "AboutDialogColumn"

        Text {
            id: applicationTitleLabel
            objectName: "ApplicationTitleLabel"

            anchors.left: parent.left
            anchors.leftMargin: Style.aboutPopup.leftPadding

            height: Style.aboutPopup.titleHeight

            font.pixelSize: Style.aboutPopup.bigFontSize

            color: Style.aboutPopup.textColor

            text: qsTr( "Event Viewer" )
        }

        Text {
            id: authorLabel
            objectName: "AuthorLabel"

            anchors.left: parent.left
            anchors.leftMargin: Style.aboutPopup.leftPadding

            height: Style.aboutPopup.textHeight

            font.pixelSize: Style.aboutPopup.normalFontSize

            color: Style.aboutPopup.textColor

            text: qsTr( "Author: Dominik Wojtaszek" )
        }

        Text {
            id: versionLabel
            objectName: "VersionLabel"

            anchors.left: parent.left
            anchors.leftMargin: Style.aboutPopup.leftPadding

            font.pixelSize: Style.aboutPopup.normalFontSize

            color: Style.aboutPopup.textColor

            text: qsTr( "Version: Alpha 0.1 (UNSTABLE)" )
        }
    }

    Text {
        id: closeMeLabel
        objectName: "CloseMeLabel"

        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        font.pixelSize: Style.aboutPopup.smallFontSize

        color: Style.aboutPopup.textColor

        text: qsTr( "Press ESC to close this window ..." )
    }
}
