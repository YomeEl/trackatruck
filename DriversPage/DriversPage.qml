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

    property var selectedDriver: null

    Text {
        text: 'Водители'
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
        visible: selectedDriver !== null

        TextField {
            id: newName
            text: ""
        }

        Button {
            text: "Изменить фио"
            enabled: newName.text && newName.text !== "" && newName.text !== selectedDriver.name
            onClicked: DataProvider.updateDriverName(selectedDriver.id, newName.text)
        }

        Button {
            text: "Отмена"
            onClicked: selectedDriver = null
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

        model: DataProvider.getDriversList()
        delegate: Driver {
            free: true
            driverModel: model
            isSelected: selectedDriver === model
            onSelected: selectedDriver = model
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

        model: DataProvider.getDriversList()
        delegate: Driver {
            free: false
            driverModel: model
            isSelected: selectedDriver === model
            onSelected: selectedDriver = model
        }
    }

    onSelectedDriverChanged: newName.text = selectedDriver ? selectedDriver.name : ""
}
