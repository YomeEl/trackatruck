import QtQuick 2.15
import '../Theme'

Rectangle {
    id: root
    Theme { id: theme }

    visible: free === driverModel.isFree
    height: visible ? childrenRect.height : 0
    width: parent ? parent.width : 0
    border.width: isSelected ? 3 : 0

    property var driverModel
    property bool useAccent: false
    property bool free
    property bool isSelected: false

    signal selected()

    color: useAccent || isSelected ? theme.accent : theme.background

    Column {
        padding: 5
        Text {
            text: driverModel.name
        }
        Text {
            text: 'Дата заключения договора: ' + new Date(driverModel.contractDate).toLocaleDateString()
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
