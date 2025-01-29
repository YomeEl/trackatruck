import QtQuick 2.15

Rectangle {
    anchors.fill: parent

    OrdersTable {
        id: table
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }
        width: parent.width / 3
        onSelected: details.model = model
    }

    OrderDetails {
        id: details
        anchors {
            left: table.right
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }
    }
}
