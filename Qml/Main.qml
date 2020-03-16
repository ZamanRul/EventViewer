import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14

import QtQuick.Dialogs 1.3
import QtQuick.Controls.Material 2.12

import "./Actions"
import "./Dialogs"
import "./Widgets"
import "./Widgets/Events"

ApplicationWindow  {
    id: root

    visible: true

    visibility: Window.Maximized

    title: qsTr( "Events Viewer" )

    OpenFileDialog { }

    AboutDialog { }

    menuBar: HeaderMenuBar { }

    SplitView {
        id: splitView
        objectName: "SplitView"

        anchors.fill: parent

        EventsList {
            SplitView.minimumWidth: 600
            SplitView.fillWidth: true
        }

        FilterPane {
            SplitView.minimumWidth: 350
            SplitView.preferredWidth: 400
        }
    }

    footer: StatusBar { }
}
