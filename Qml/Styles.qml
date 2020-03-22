pragma Singleton

import QtQuick 2.0

QtObject {

    readonly property QtObject application: QtObject
    {
        readonly property int minimalHeight: 600
        readonly property int minimalWidth: 1024
    }

    readonly property QtObject groupStatus: QtObject
    {
        readonly property int width: 200
        readonly property color hoverColor: "#AF164C"

        readonly property int iconLeftMargin: 2
        readonly property int iconTopMargin: 4

        readonly property int iconSize: 18

        readonly property int textLeftMargin: 2
    }

    readonly property QtObject statusBar: QtObject
    {
        readonly property int height: 25

        readonly property int fontSize: 14

        readonly property color error: "red"
        readonly property color warning: "orange"
        readonly property color info: "#e91e63"

        readonly property int warningIconLeftPadding: 10
        readonly property int warningIconTopPadding: 7
        readonly property int warningIconSize: 12

        readonly property int statusMessageLeftPadding: 25
        readonly property color statusMessageColor: "white"

        readonly property int fileNameWidth: 250

        readonly property int fileIconLeftPadding: 6
        readonly property int fileIconTopPadding: 7
        readonly property int fileIconSize: 12

        readonly property int fileNameRightMargin: 20
        readonly property color fileNameFontColor: "white"
    }

    readonly property QtObject aboutPopup: QtObject
    {
        readonly property int height: 200
        readonly property int width: 400

        readonly property color overlayColor: "#f0303030"

        readonly property int titleHeight: 50
        readonly property int textHeight: 35

        readonly property int ribbonLeftMargin: -12
        readonly property int ribbonTopMargin: -12

        readonly property int ribbonHeight: 200
        readonly property int ribbonWidth: 20

        readonly property int bigFontSize: 30
        readonly property int normalFontSize: 18
        readonly property int smallFontSize: 12

        readonly property int leftPadding: 20

        readonly property color textColor: "white"
    }

    readonly property QtObject eventDelegate: QtObject
    {
        readonly property int height: 70

        readonly property color evenBackgroundColor: "#343434"
        readonly property color oddBackgroundColor: "transparent"

        readonly property int fontSize: 16
        readonly property color fontColor: "white"

        readonly property int groupIconSize: 32

        readonly property real column0Aspect: 0.05
        readonly property real column1Aspect: 0.15
        readonly property real column2Aspect: 0.20
        readonly property real column3Aspect: 0.30
        readonly property real column4Aspect: 0.30
    }

    readonly property QtObject chart: QtObject
    {
        readonly property int height: 136

        readonly property int innerPadding: 10

        readonly property color lineColor: "#e91e63"
        readonly property color referenceLineColor: "#404040"

        readonly property color highlightColor: "#e91e63"
        readonly property real hightlightOpacity: 0.5

        readonly property int noDataBackgroundZ: 10
        readonly property color noDataBackgroundColor: "#303030"
        readonly property color noDataTextColor: "#606060"
        readonly property int noDataFontSize: 16
    }

    readonly property QtObject eventFilterWidget: QtObject
    {
        readonly property int buttonBarHeight: 50
        readonly property color buttonBarColor: "#424242"
        readonly property int buttonBarSpacing: 30

        readonly property color noDataBackgroundColor: "#303030"
        readonly property color noDataTextColor: "#606060"
        readonly property int noDataFontSize: 16
    }

    readonly property QtObject filterField: QtObject
    {
        readonly property int clearButtonSize: 20
        readonly property int clearButtonRightPadding: 15

        readonly property color backgroundColor: "#303030"

        readonly property color borderColor: "#e91e63"
        readonly property int borderWidth: 2

        readonly property int z: 100

        readonly property int fontSize: 16

        readonly property int leftPadding: 20
        readonly property int rightPadding: 30
        readonly property int topPadding: 12
    }

    readonly property QtObject header: QtObject
    {
        readonly property int height: 40

        readonly property int leftPadding: 20
        readonly property int fontSize: 22
    }

    readonly property QtObject button: QtObject
    {
        readonly property int buttonSize: 20
        readonly property color buttonColor: "#606060"
    }

    readonly property QtObject timeFilterWidget: QtObject
    {
        readonly property int height: 310
        readonly property color buttonColor: "#606060"

        readonly property int labelMargin: 10
        readonly property int labelHeight: 50
    }

    readonly property QtObject eventsList: QtObject
    {
        readonly property int noDataFontSize: 20
        readonly property color noDataFontColor: "#606060"

        readonly property int labelMargin: 10
        readonly property int labelHeight: 50
    }
}
