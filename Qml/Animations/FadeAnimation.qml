import QtQuick 2.0

SequentialAnimation {
    id: rootFadeAnimation
    objectName: "RootFadeAnimation"

    property QtObject target
    property int fadeDuration: 1000

    NumberAnimation {
        id: outAnimation
        objectName: "OutAnimation"

        target: rootFadeAnimation.target

        property: "opacity"
        duration: rootFadeAnimation.fadeDuration

        to: 0
    }

    PropertyAction { }

    NumberAnimation {
        id: inAnimation
        objectName: "InAnimation"

        target: rootFadeAnimation.target

        property: "opacity"
        duration: rootFadeAnimation.fadeDuration

        to: 1
    }
}
