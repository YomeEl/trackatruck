import QtQuick 2.15
import QtQuick.Layouts 1.15
import '../Theme'

Rectangle {
    id: root
    Theme { id: theme }

    visible: free === truckModel.isFree
    height: visible ? 40 : 0
    width: parent ? parent.width : 0

    property var truckModel
    property bool useAccent: false
    property bool free

    color: useAccent ? theme.accent : theme.background

    GridLayout {
        columns: 2
        rowSpacing: 5
        columnSpacing: 5
        anchors.margins: 5
        anchors.fill: parent

        Text {
            text: truckModel.truckModel
            Layout.minimumWidth: 75
        }
        Text {
            text: 'Пробег на момент последнего ТО: ' + truckModel.lastMilage + ' км'
            Layout.fillWidth: true
        }
        Text {
            text: truckModel.number
            Layout.minimumWidth: 75
        }
        Text {
            text: 'Последнее ТО: ' + truckModel.lastMaintananceDate.toLocaleDateString()
            Layout.fillWidth: true
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onEntered: root.useAccent = true
        onExited: root.useAccent = false
    }
}
