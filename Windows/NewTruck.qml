import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.15

import '../Theme'

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Форма добавления грузовика")
    modality: Qt.ApplicationModal

    Theme { id: theme }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 5

        RowLayout {
            spacing: 5
            Label {
                text: "Модель: "
                Layout.minimumWidth: 150
            }
            TextField {
                id: model
                placeholderText: "Введите модель грузовика..."
                Layout.fillWidth: true
            }
        }

        RowLayout {
            spacing: 5
            Label {
                text: "Гос. номер: "
                Layout.minimumWidth: 150
            }
            TextField {
                id: number
                placeholderText: "Введите гос. номер..."
                Layout.fillWidth: true
            }
        }

        RowLayout {
            spacing: 5
            Label {
                text: "Пробег (км): "
                Layout.minimumWidth: 150
            }
            TextField {
                id: milage
                placeholderText: "Введите пробег..."
                Layout.fillWidth: true
                validator: DoubleValidator {
                    bottom: 0.0
                }
            }
        }

        RowLayout {
            spacing: 5
            Label {
                text: "Дата последнего ТО: "
                Layout.minimumWidth: 150
            }
            Calendar {
                id: lastMaintanance
                maximumDate: new Date()
            }
        }

        Button {
            text: "Добавить"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                const emptyModelMessage = 'ФИО водителя не может быть пустым'
                const emptyNumberMessage = 'ФИО водителя не может быть пустым'

                var errors = []
                if (!model.text || model.text === '') errors.push(emptyModelMessage)
                if (!number.text || number.text === '') errors.push(emptyNumberMessage)

                errorsRepeater.model = errors
                if (errors.length > 0) return

                const modelText = model.text
                const numberText = number.text
                const lastMilage = Number(milage.text)
                const lastMaintananceDate = lastMaintanance.selectedDate

                DataProvider.addTruck(modelText, numberText, lastMilage, lastMaintananceDate)
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
