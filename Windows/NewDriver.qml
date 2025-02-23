import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import '../Theme'

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Форма добавления водителя")
    modality: Qt.ApplicationModal

    Theme { id: theme }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 5

        RowLayout {
            spacing: 5
            Label {
                text: "ФИО: "
                Layout.minimumWidth: 150
            }
            TextField {
                id: name
                placeholderText: "Введите ФИО водителя..."
                Layout.fillWidth: true
            }
        }

        Button {
            text: "Добавить"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                const emptyNameMessage = 'ФИО водителя не может быть пустым'

                var errors = []
                if (!name.text || name.text === '') errors.push(emptyNameMessage)

                errorsRepeater.model = errors
                if (errors.length > 0) return

                DataProvider.addDriver(name.text)
                root.close();
            }
        }

        Text {
            visible: errorsRepeater.model.length > 0
            text: "Ошибки:"
        }

        Repeater {
            id: errorsRepeater
            model: []
            delegate: Text {
                color: theme.warningHigh
                text: modelData
            }
        }
    }
}
