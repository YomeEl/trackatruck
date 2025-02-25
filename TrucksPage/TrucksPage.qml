import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

GridLayout {
    id: root

    anchors {
        margins: 10
    }

    columns: 2
    columnSpacing: 0
    rowSpacing: 5

    property var selectedTruck: null

    Text {
        text: 'Грузовики'
        font.pointSize: 20
        horizontalAlignment: Text.AlignHCenter
        Layout.preferredWidth: parent.width / 3
        Layout.columnSpan: 2
        Layout.fillWidth: true
    }

    RowLayout {
        Layout.columnSpan: 2
        Layout.alignment: Qt.AlignHCenter
        height: childrenRect.height
        visible: selectedTruck !== null

        Button {
            text: "Отметить ТО"
            onClicked: DataProvider.markMaintanance(selectedTruck.id)
        }
        TextField {
            id: newNumber
            text: ""
        }

        Button {
            text: "Изменить гос. номер"
            enabled: newNumber.text && newNumber.text !== "" && newNumber.text !== selectedTruck.number
            onClicked: DataProvider.updateTruckNumber(selectedTruck.id, newNumber.text)
        }

        Button {
            text: "Отмена"
            onClicked: selectedTruck = null
        }
    }

    ListView {
        header: Text {
            text: 'Свободные'
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 16
        }
        headerPositioning: ListView.OverlayHeader
        Layout.fillWidth: true
        Layout.fillHeight: true

        ScrollBar.vertical: ScrollBar {
            active: true
        }

        model: DataProvider.getTrucksList()
        delegate: Truck {
            free: true
            truckModel: model
            isSelected: selectedTruck === model
            onSelected: selectedTruck = model
        }
    }

    ListView {
        header: Text {
            text: 'На заказе'
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 16
        }
        headerPositioning: ListView.OverlayHeader
        Layout.fillWidth: true
        Layout.fillHeight: true

        ScrollBar.vertical: ScrollBar {
            active: true
        }

        model: DataProvider.getTrucksList()
        delegate: Truck {
            free: false
            truckModel: model
            isSelected: selectedTruck === model
            onSelected: selectedTruck = model
        }
    }

    onSelectedTruckChanged: newNumber.text = selectedTruck ? selectedTruck.number : ""
}
