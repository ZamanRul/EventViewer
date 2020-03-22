import QtQuick 2.14
import QtQuick.Controls 2.14

import Style 1.0
import Flux 1.0

import "../Animations"
import "./Others"

Item {
    id: rootStatusBar
    objectName: "RootStatusBar"

    height: Style.statusBar.height

    state: applicationModel.status.state

    Rectangle {
        id: statusBarBackground
        objectName: "StatusBarBackground"

        anchors.fill: parent

        color: Style.statusBar.info
    }

    Image {
        id: warningIcon
        objectName: "WarningIcon"

        visible: applicationModel.status.state === "error" || applicationModel.status.state === "warning"

        anchors.left: parent.left
        anchors.leftMargin: Style.statusBar.warningIconLeftPadding
        anchors.top: parent.top
        anchors.topMargin: Style.statusBar.warningIconTopPadding

        height: Style.statusBar.warningIconSize
        width: Style.statusBar.warningIconSize

        sourceSize.height: Style.statusBar.warningIconSize
        sourceSize.width: Style.statusBar.warningIconSize

        smooth: true

        source: "qrc:/Icons/warning.svg"

        Behavior on visible { FadeAnimation { target: warningIcon } }
    }

    Text {
        id: statusBarMessage
        objectName: "StatusBarMessage"

        anchors.left: parent.left
        anchors.leftMargin: Style.statusBar.statusMessageLeftPadding
        anchors.right: groupAStatus.left

        height: parent.height

        elide: Text.ElideRight

        color: Style.statusBar.statusMessageColor

        verticalAlignment: Text.AlignVCenter
        font.pixelSize: Style.statusBar.fontSize

        text: applicationModel.status.message

        Behavior on text { FadeAnimation { target: statusBarMessage } }
    }

    GroupStatus {
        id: groupAStatus
        objectName: "GroupAStatus"

        anchors.right: groupBStatus.left

        icon: "qrc:/Icons/a_white.svg"

        groupId: 65

        count: applicationModel.data.groupACount
    }

    GroupStatus {
        id: groupBStatus
        objectName: "GroupBStatus"

        anchors.right: loadedFilename.left

        icon: "qrc:/Icons/b_white.svg"

        groupId: 66

        count: applicationModel.data.groupBCount
    }

    Item {
        id: loadedFilename
        objectName: "LoadedFilename"

        opacity: 0

        anchors.right: parent.right

        height: parent.height
        width: Style.statusBar.fileNameWidth

        clip: true

        Image {
            id: fileIcon
            objectName: "FileIcon"

            anchors.right: statusBarFileName.left
            anchors.rightMargin: Style.statusBar.fileIconLeftPadding
            anchors.top: parent.top
            anchors.topMargin: Style.statusBar.fileIconTopPadding

            height: Style.statusBar.fileIconSize
            width: Style.statusBar.fileIconSize

            sourceSize.height: Style.statusBar.fileIconSize
            sourceSize.width: Style.statusBar.fileIconSize

            smooth: true

            source: "qrc:/Icons/file.svg"
        }

        Text {
            id: statusBarFileName
            objectName: "StatusBarFileName"

            anchors.right: parent.right
            anchors.rightMargin: Style.statusBar.fileNameRightMargin

            height: parent.height

            elide: Text.ElideRight
            color: Style.statusBar.fileNameFontColor

            verticalAlignment: Text.AlignVCenter
            font.pixelSize: Style.statusBar.fontSize

            text: applicationModel.status.fileName

            Behavior on text { FadeAnimation { target: loadedFilename } }
        }
    }

    states: [
        State {
            name: "error"
            PropertyChanges { target: statusBarBackground; color: Style.statusBar.error }
        },
        State {
            name: "warning"
            PropertyChanges { target: statusBarBackground; color: Style.statusBar.warning }
        },
        State {
            name: "info"
            PropertyChanges { target: statusBarBackground; color: Style.statusBar.info }
        }
    ]

    transitions: [
        Transition {
            to: "error"

            SequentialAnimation {
                loops: Animation.Infinite

                ColorAnimation { target: statusBarBackground; to: "red"; duration: 1000; }
                ColorAnimation { target: statusBarBackground; to: "#E91E63"; duration: 1000; }
            }
        },
        Transition {
            to: "info"

            SequentialAnimation {
                ColorAnimation { target: statusBarBackground; to: "#E91E63"; duration: 1000; }
            }
        }
    ]
}
