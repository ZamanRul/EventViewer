import QtQuick 2.0

import Style 1.0

Text {
    id: rootTableField
    objectName: "rootTableField"

    property bool inactive: false

    height: parent.height

    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter

    elide: Text.ElideRight

    font.pixelSize: Style.tableTextField.fontSize

    color: inactive ? Style.tableTextField.inactiveFontColor : Style.tableTextField.fontColor
}
