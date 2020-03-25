import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12

import Flux 1.0
import Style 1.0

import "../Widgets/Others"
import "../Widgets/Comparison"

Popup {
    id: rootCompareDialog
    objectName: "RootCompareDialog"

    visible: applicationModel.dialog.showCompareDialog

    height: parent.height
    width: parent.width

    bottomPadding: Style.compareDialog.padding
    topPadding: Style.compareDialog.padding
    leftPadding: Style.compareDialog.padding
    rightPadding: Style.compareDialog.padding

    parent: Overlay.overlay

    modal: true
    focus: true

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    onClosed: ActionProvider.showCompareDialog( false );

    background: Rectangle {
        id: compareDialogBackground
        objectName: "CompareDialogBackground"

        color: Style.compareDialog.backgroundColor

        Image {
            id: compareDialogBackgroundImage
            objectName: "CompareDialogBackgroundImage"

            anchors.fill: parent

            sourceSize.height: Style.compareDialog.backgroundImageSize
            sourceSize.width: Style.compareDialog.backgroundImageSize

            smooth: true

            fillMode: Image.Tile

            source: "qrc:/Images/Lines.png"
        }
    }

    Column {
        id: compareDialogColumn
        objectName: "CompareDialogColumn"

        height: parent.height
        width: parent.width

        Header {
            id: compareDialogHeader
            objectName: "CompareDialogHeader"

            text: qsTr( "Comparison" )

            Button {
                id: compareDialogCloseButton
                objectName: "CompareDialogCloseButton"

                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter

                font.bold: true
                font.pixelSize: Style.compareDialog.closeButtonSize

                Material.background: "transparent"

                text: "X"

                onClicked: ActionProvider.showCompareDialog( false );
            }
        }

        ComparisonWidget {
            id: comparisonWidget
            objectName: "ComparisonWidget"

            height: parent.height - compareDialogHeader.height
        }
    }
}
