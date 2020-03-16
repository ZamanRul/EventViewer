import QtQuick 2.0
import QtQuick.Shapes 1.14

import Style 1.0

Rectangle {
    id: rootEventsChart
    objectName: "RootEventsCahrt"

    property variant chartReferenceData: applicationModel.charts.eventsTimeline
    property variant chartData: applicationModel.charts.filteredEventsTimeline

    property real timeWindowMinimum: 0.0        // value from 0.0 to 1.0
    property real timeWindowMaximum: 0.0        // value from 0.0 to 1.0
    property real innerPadding: Style.chart.innerPadding

    width: parent.width
    height: Style.chart.height

    layer.enabled: true
    layer.samples: 16

    Shape {
        id: eventChartShape
        objectName: "EventChartShape"

        anchors.fill: parent

        ChartLine {
            id: chartReferencePath
            objectName: "ChartReferencePath"

            innerPadding: rootEventsChart.innerPadding

            innerWidth: parent.width - 2 * rootEventsChart.innerPadding
            innerHeight: rootEventsChart.height - rootEventsChart.innerPadding

            startX: rootEventsChart.innerPadding

            color: Style.chart.referenceLineColor

            data: chartReferenceData
        }

        ChartLine {
            id: chartPath
            objectName: "ChartPath"

            innerPadding: rootEventsChart.innerPadding

            innerWidth: parent.width - 2 * rootEventsChart.innerPadding
            innerHeight: rootEventsChart.height - rootEventsChart.innerPadding

            startX: rootEventsChart.innerPadding

            color: Style.chart.lineColor

            data: chartData
        }

        Rectangle {
            id: selectedTimeWindow
            objectName: "SelectedTimeWindow"

            x: rootEventsChart.timeWindowMinimum * chartPath.innerWidth  + rootEventsChart.innerPadding
            y: 0

            height: parent.height
            width: ( rootEventsChart.timeWindowMaximum - rootEventsChart.timeWindowMinimum ) * chartPath.innerWidth

            opacity: Style.chart.hightlightOpacity
            color: Style.chart.highlightColor
        }

        Rectangle {
            id: noDataBackground
            objectName: "NoDataBackground"

            visible: applicationModel.data.noData

            anchors.fill: parent

            z: Style.chart.noDataBackgroundZ

            color: Style.chart.noDataBackgroundColor

            Text {
                id: noDataLabel
                objectName: "NoDataLabel"

                anchors.centerIn: parent

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter

                font.pixelSize: Style.chart.noDataFontSize

                color: Style.chart.noDataTextColor

                text: qsTr( "No data" )
            }
        }
    }
}
