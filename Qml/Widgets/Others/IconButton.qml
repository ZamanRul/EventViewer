import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12

import Style 1.0

Button {
    id: rootIconButton
    objectName: "RootIconButton"

    property string iconPath: ""

    icon.source: iconPath

    icon.width: Style.button.buttonSize
    icon.height: Style.button.buttonSize

    Material.background: Style.button.buttonColor
}
