import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ColumnLayout {
    id: root

    anchors {
        margins: 50
    }

    spacing: 5

    property var selectedClient: null

    Text {
        text: 'Клиенты'
        font.pointSize: 20
        horizontalAlignment: Text.AlignHCenter
        Layout.preferredWidth: parent.width / 2
        Layout.fillWidth: true
    }

    RowLayout {
        Layout.alignment: Qt.AlignHCenter
        height: childrenRect.height
        visible: selectedClient !== null

        Text {
            text: "Название"
        }

        TextField {
            id: newName
            text: ""
        }

        Text {
            text: "Адрес"
        }

        TextField {
            id: newAddress
            text: ""
        }

        Button {
            text: "Изменить"
            enabled:
                newName.text && newName.text !== "" && newAddress.text && newAddress.text !== "" &&
                (newName.text !== selectedClient.name || newAddress.text !== selectedClient.address)
            onClicked: DataProvider.updateClient(selectedClient.id, newName.text, newAddress.text)
        }

        Button {
            text: "Отмена"
            onClicked: selectedClient = null
        }
    }

    ListView {
        id: list
        headerPositioning: ListView.OverlayHeader
        Layout.fillWidth: true
        Layout.fillHeight: true

        ScrollBar.vertical: ScrollBar {
            active: true
        }

        model: DataProvider.getClientsList()
        delegate: Client {
            clientModel: model
            isSelected: selectedClient === model
            onSelected: selectedClient = model
        }
    }

    onSelectedClientChanged: {
        newName.text = selectedClient ? selectedClient.name : ""
        newAddress.text = selectedClient ? selectedClient.address : ""
    }
}
