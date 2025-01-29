import QtQuick 2.15
import '../Theme'

Rectangle {
    id: root
    Theme { id: theme }
    height: childrenRect.height
    width: parent.width
    border.width: 1

    property string route;
    property string driver;
    property int warningLevel: 2;
    property var colors: [theme.background, theme.warningLow, theme.warningHigh]
    property var accentColors: [theme.accent, theme.warningLowAccent, theme.warningHighAccent]
    property bool useAccent: false

    signal selected()

    color: useAccent ? accentColors[warningLevel] : colors[warningLevel]

    Column {
        padding: 5
        Text {
            id: routeText
            text: route
        }
        Text {
            id: driverText
            text: driver === '' ? 'Водитель не назначен!' : driver
            color: driver === '' ? '#0000FF' : '#000000'
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onEntered: root.useAccent = true
        onExited: root.useAccent = false
        onClicked: selected()
    }
}
