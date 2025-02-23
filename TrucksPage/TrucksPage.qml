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
    rowSpacing: 0

    signal generateReport(var order)

    Text {
        text: 'Грузовики'
        font.pointSize: 20
        horizontalAlignment: Text.AlignHCenter
        Layout.preferredWidth: parent.width / 3
        Layout.columnSpan: 2
        Layout.fillWidth: true
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
        }
    }
}
