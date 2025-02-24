import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ColumnLayout {
    id: root

    anchors {
        margins: 50
    }

    spacing: 5

    signal generateReport(var order)

    Text {
        text: 'Клиенты'
        font.pointSize: 20
        horizontalAlignment: Text.AlignHCenter
        Layout.preferredWidth: parent.width / 2
        Layout.fillWidth: true
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
        }
    }
}
