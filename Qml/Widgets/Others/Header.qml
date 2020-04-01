import QtQuick 2.14
import QtQuick.Controls 2.14

import Style 1.0

Item {
    id: rootHeader
    objectName: "RootHeader"

    property string text: ""

    height: Style.header.height
    width: parent.width

    Image {
        id: headerBackground
        objectName: "HeaderBackground"

        anchors.fill: parent

        fillMode: Image.Tile

        source: "qrc:/Images/HeaderBackground.png"
    }

    Label {
        id: headerText
        objectName: "HeaderText"

        anchors.left: parent.left
        anchors.leftMargin: Style.header.leftPadding

        anchors.verticalCenter: parent.verticalCenter

        font.pixelSize: Style.header.fontSize
        font.bold: true

        text: rootHeader.text
    }
}
