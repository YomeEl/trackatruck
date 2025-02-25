import QtQuick 2.15
import QtQuick.Controls 2.15

ListView {
    id: listView
    spacing: -1
    model: DataProvider.getOrdersList()
    cacheBuffer: 200
    property int selectedId: -1

    signal selected(var model)

    function selectWarningLevel(model) {
        const finished = 0
        const ok = 1
        const pending = 2
        const late = 3

        if (model.finished) return finished
        if (!model.driverName) return pending
        if (new Date(model.receivedAt) < Date.now() && !model.finished) return late
        return ok
    }

    ScrollBar.vertical: ScrollBar {
        active: true
    }

    delegate: Order {
        route: model.fromAddress + " - " + model.toAddress
        driver: model.driverName
        warningLevel: selectWarningLevel(model)
        isSelected: model.id === listView.selectedId
        onSelected: {
            listView.selectedId = model.id
            listView.selected(model)
        }
    }
}
