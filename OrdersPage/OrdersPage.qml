import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

GridLayout {
    id: root

    anchors.fill: parent
    columns: 2
    columnSpacing: 0
    rowSpacing: 0

    signal generateReport(var order)

    Text {
        text: 'Активные заказы'
        font.pixelSize: 20
        horizontalAlignment: Text.AlignHCenter
        Layout.preferredWidth: parent.width / 3
        Layout.columnSpan: 2
        Layout.fillWidth: true
    }

    //OrdersTable {
    //    id: table
    //    onSelected: details.model = model
    //    Layout.preferredWidth: parent.width / 3
    //    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
    //}

    OrdersTable {
        id: table
        Layout.fillWidth: true
        Layout.fillHeight: true
        onSelected: details.model = model
    }

    OrderDetails {
        id: details
        Layout.preferredWidth: 2 * parent.width / 3
        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
        onGenerateReport: root.generateReport(order)
    }
}
