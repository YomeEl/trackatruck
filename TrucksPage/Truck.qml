import QtQuick 2.15
import '../Theme'

Rectangle {
    id: root
    Theme { id: theme }

    visible: free === truckModel.isFree
    height: visible ? childrenRect.height : 0
    width: parent ? parent.width : 0

    property var truckModel
    property bool useAccent: false
    property bool free

    color: useAccent ? theme.accent : theme.background

    Grid {
        columns: 2
        padding: 5

        Text {
            text: truckModel.name
        }
        Text {
            text: truckModel.lastMilage
        }
        Text {
            text: truckModel.number
        }
        Text {
            text: truckModel.lastMaintananceDate
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
