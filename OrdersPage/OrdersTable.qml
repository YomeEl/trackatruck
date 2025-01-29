import QtQuick 2.15
import QtQuick.Controls 2.15

ScrollView {
    id: root
    signal selected(model: var)

    Column {
        id: col
        anchors.fill: parent
        spacing: -1
        Repeater {
            model: DataProvider.getOrdersList()
            delegate: Order {
                route: model.fromAddress + " - " + model.toAddress
                driver: model.driverName
                onSelected: { root.selected(model) }
            }
        }
    }
}
