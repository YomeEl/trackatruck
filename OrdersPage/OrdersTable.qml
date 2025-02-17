import QtQuick 2.15
import QtQuick.Controls 2.15

ScrollView {
    id: root
    signal selected(model: var)
    property int selectedId: -1

    function selectWarningLevel(model) {
        const ok = 0
        const pending = 1
        const late = 2

        if (!model.driverName) return pending
        if (new Date(model.receivedAt) < Date.now() && !model.finished) return late
        return ok
    }

    Column {
        id: col
        anchors.fill: parent
        spacing: -1
        Repeater {
            model: DataProvider.getOrdersList()
            delegate: Order {
                route: model.fromAddress + " - " + model.toAddress
                driver: model.driverName
                warningLevel: selectWarningLevel(model)
                isSelected: model.id === root.selectedId
                onSelected: { root.selected(model); root.selectedId = model.id }
            }
        }
    }
}
