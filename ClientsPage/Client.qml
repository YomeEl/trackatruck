import QtQuick 2.15
import '../Theme'

Rectangle {
    id: root
    Theme { id: theme }

    height: childrenRect.height
    width: parent ? parent.width : 0
    border.width: isSelected ? 3 : 0

    property var clientModel
    property bool useAccent: false
    property bool isSelected: false

    signal selected()

    color: useAccent || isSelected ? theme.accent : theme.background

    Column {
        spacing: 5
        padding: 10
        Text {
            text: clientModel.name
        }
        Text {
            text: 'Адрес: ' + clientModel.address
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
