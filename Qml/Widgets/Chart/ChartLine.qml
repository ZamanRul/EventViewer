import QtQuick 2.0
import QtQuick.Shapes 1.14

ShapePath {
    id: rootChartLine
    objectName: "RootChartLine"

    property int duration: 1000
    property color color: "black"
    property int stroke: 4

    property real innerPadding: 0
    property real innerWidth: 0
    property real innerHeight: 0

    property variant data: 0

    strokeWidth: stroke
    strokeColor: color

    capStyle: ShapePath.RoundCap

    startX: innerPadding
    startY: firstPoint.y

    fillColor : "transparent"

    PathLine { id: firstPoint; x: rootEventsChart.innerPadding; y: data[0] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.01; y: data[1] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.02; y: data[2] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.03; y: data[3] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.04; y: data[4] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.05; y: data[5] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.06; y: data[6] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.07; y: data[7] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.08; y: data[8] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.09; y: data[9] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.10; y: data[10] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }

    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.11; y: data[11] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.12; y: data[12] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.13; y: data[13] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.14; y: data[14] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.15; y: data[15] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.16; y: data[16] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.17; y: data[17] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.18; y: data[18] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.19; y: data[19] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.20; y: data[20] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }

    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.21; y: data[21] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.22; y: data[22] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.23; y: data[23] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.24; y: data[24] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.25; y: data[25] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.26; y: data[26] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.27; y: data[27] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.28; y: data[28] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.29; y: data[29] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.30; y: data[30] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }

    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.31; y: data[31] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.32; y: data[32] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.33; y: data[33] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.34; y: data[34] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.35; y: data[35] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.36; y: data[36] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.37; y: data[37] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.38; y: data[38] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.39; y: data[39] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.40; y: data[40] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }

    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.41; y: data[41] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.42; y: data[42] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.43; y: data[43] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.44; y: data[44] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.45; y: data[45] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.46; y: data[46] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.47; y: data[47] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.48; y: data[48] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.49; y: data[49] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.50; y: data[50] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }

    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.51; y: data[51] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.52; y: data[52] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.53; y: data[53] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.54; y: data[54] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.55; y: data[55] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.56; y: data[56] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.57; y: data[57] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.58; y: data[58] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.59; y: data[59] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.60; y: data[60] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }

    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.61; y: data[61] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.62; y: data[62] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.63; y: data[63] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.64; y: data[64] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.65; y: data[65] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.66; y: data[66] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.67; y: data[67] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.68; y: data[68] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.69; y: data[69] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.70; y: data[70] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }

    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.71; y: data[71] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.72; y: data[72] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.73; y: data[73] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.74; y: data[74] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.75; y: data[75] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.76; y: data[76] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.77; y: data[77] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.78; y: data[78] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.79; y: data[79] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.80; y: data[80] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }

    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.81; y: data[81] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.82; y: data[82] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.83; y: data[83] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.84; y: data[84] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.85; y: data[85] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.86; y: data[86] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.87; y: data[87] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.88; y: data[88] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.89; y: data[89] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.90; y: data[90] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }

    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.91; y: data[91] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.92; y: data[92] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.93; y: data[93] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.94; y: data[94] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.95; y: data[95] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.96; y: data[96] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.97; y: data[97] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.98; y: data[98] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
    PathLine { x: rootEventsChart.innerPadding + rootChartLine.innerWidth * 0.99; y: data[99] * rootChartLine.innerHeight; Behavior on y { PropertyAnimation { duration: duration } } }
}
