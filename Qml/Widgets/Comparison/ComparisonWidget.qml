import QtQuick 2.14
import QtQuick.Controls 2.14

import Flux 1.0
import Style 1.0

Item {
    id: rootComparisonWidget
    objectName: "RootComparisonWidget"

    height: parent.height
    width: parent.width

    Column {
        id: comparisonWidgetColumn
        objectName: "ComparisonWidgetColumn"

        height: parent.height
        width: parent.width

        ComparisonHeader {
            id: comparisonHeader
            objectName: "ComparisonHeader"
        }

        ListView {
            id: comparisonView
            objectName: "ComparisionView"

            height: parent.height - comparisonHeader.height
            width: parent.width

            clip: true

            model: applicationModel.comparison.compareEventsModel

            delegate: ComparisonDelegate { }

            ScrollBar.vertical: ScrollBar { }

            Rectangle {
                id: noDataBackground
                objectName: "NoDataBackground"

                visible: comparisonView.count < 1

                anchors.fill: parent

                color: Style.comparisonDelegate.noDataBackgroundColor

                Text {
                    id: noDataLabel
                    objectName: "NoDataLabel"

                    anchors.centerIn: parent

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                    font.pixelSize: Style.comparisonDelegate.noDataFontSize

                    color: Style.comparisonDelegate.noDataTextColor

                    text: qsTr( "No data to compare" )
                }
            }
        }
    }
}
