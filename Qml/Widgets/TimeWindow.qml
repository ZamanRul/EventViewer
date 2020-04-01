import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Shapes 1.14
import QtQuick.Layouts 1.14

import "./Chart"
import "./Others"

import Style 1.0
import Flux 1.0

Item {
    id: rootTimeWindow
    objectName: "RootTimeWindow"

    property alias timeWindowMinimum: rangeSelector.first.value
    property alias timeWindowMaximum: rangeSelector.second.value

    width: parent.width
    height: Style.timeFilterWidget.height

    function epochToString(epoch)
    {
        if ( applicationModel.data.noData )
            return "_ _ _";

        var date = new Date(0);
        date.setUTCMilliseconds(epoch);
        var results = date.getHours() + ":" + date.getMinutes() + ":" + date.getSeconds() + ":" + ( '00' + date.getMilliseconds() ).slice( -3 ) + "\n"
                + date.getDate() + "/" + ( date.getMonth() + 1 ) + "/" + date.getUTCFullYear();

        return results;
    }

    Column {
        id: timeWindowColumn
        objectName: "TimeWindowColumn"

        width: parent.width

        Header {
            id: fileterByTimelineLabel
            objectName: "FileterByTimelineLabel"

            text: "Timeline"
        }

        Rectangle {
            id: emptyRectangle
            objectName: "EmptyRectangle"

            height: 20
            width: parent.width

            color: "transparent"
        }

        EventsChart {
            id: eventsChart
            objectName: "EventsChart"

            width: parent.width

            color: "transparent"

            timeWindowMinimum:  ( rangeSelector.first.value - rangeSelector.from ) / ( rangeSelector.to - rangeSelector.from )
            timeWindowMaximum:  ( rangeSelector.second.value - rangeSelector.from ) / ( rangeSelector.to - rangeSelector.from )
        }

        RangeSlider {
            id: rangeSelector
            objectName: "RangeSelector"

            width: parent.width

            from: applicationModel.data.eventsList.minimumEpoch
            to: applicationModel.data.eventsList.maximumEpoch
            first.value: applicationModel.data.eventsList.currentMinimum
            second.value: applicationModel.data.eventsList.currentMaximum

            first.onPressedChanged: if ( first.pressed === false ) ActionProvider.filterByTime( rangeSelector.first.value, rangeSelector.second.value )
            second.onPressedChanged: if ( second.pressed === false ) ActionProvider.filterByTime( rangeSelector.first.value, rangeSelector.second.value )
        }

        Item {
            id: timeWindowLabels
            objectName: "TimeWindowLabels"

            height: Style.timeFilterWidget.labelHeight
            width: parent.width

            Label {
                id: timeWindowMinimum
                objectName: "TimeWindowMinimum"

                anchors.left: parent.left
                anchors.leftMargin: Style.timeFilterWidget.labelMargin

                horizontalAlignment: Text.AlignHCenter

                text: rootTimeWindow.epochToString(rangeSelector.first.value)
            }

            Label {
                id: timeWindowMaximum
                objectName: "TimeWindowMaximum"

                anchors.right: parent.right
                anchors.rightMargin: Style.timeFilterWidget.labelMargin

                horizontalAlignment: Text.AlignHCenter

                text: rootTimeWindow.epochToString(rangeSelector.second.value)
            }
        }
    }
}
