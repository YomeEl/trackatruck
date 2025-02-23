import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import 'Theme'

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Форма создания заказа")
    modality: Qt.ApplicationModal

    Theme { id: theme }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 5

        RowLayout {
            spacing: 5
            Label {
                text: "Отправитель:"
                Layout.minimumWidth: 150
            }
            ComboBox {
                id: from
                model: DataProvider.getClientsList()
                textRole: "summary"
                valueRole: "id"
                Layout.fillWidth: true
            }
            Button {
                text: "Новый..."
            }
        }

        RowLayout {
            spacing: 5
            Label {
                text: "Получатель:"
                Layout.minimumWidth: 150
            }
            ComboBox {
                id: to
                model: DataProvider.getClientsList()
                textRole: "summary"
                valueRole: "id"
                Layout.fillWidth: true
            }
            Button {
                text: "Новый..."
            }
        }

        RowLayout {
            spacing: 5
            Label {
                text: "Расстояние:"
                Layout.minimumWidth: 150
            }
            TextField {
                id: distance
                placeholderText: "Введите число..."
                validator: IntValidator {}
                Layout.fillWidth: true
            }
        }

        RowLayout {
            spacing: 5
            Label {
                text: "Описание:"
                Layout.minimumWidth: 150
            }
            TextField {
                id: description
                placeholderText: "Введите текст..."
                Layout.fillWidth: true
            }
        }

        RowLayout {
            spacing: 5
            Label {
                text: "Объявленная стоимость:"
                Layout.minimumWidth: 150
            }
            TextField {
                id: declaredValueR
                text: '0'
                validator: IntValidator {
                    bottom: 0
                }
                Layout.fillWidth: true

                onFocusChanged: {
                    if (declaredValueR.focus && text === '0')
                        declaredValueR.text = ''
                    else
                        declaredValueR.text = Number(declaredValueR.text)
                }
            }
            Label {
                text: "руб."
            }
            TextField {
                id: declaredValueK
                text: '00'
                validator: IntValidator {
                    bottom: 0
                    top: 99
                }
                Layout.fillWidth: true

                onFocusChanged: {
                    if (declaredValueK.focus && text === '00')
                        declaredValueK.text = ''
                    else
                        declaredValueK.text = declaredValueK.text.padStart(2, '0')
                }
            }
            Label {
                text: "коп."
            }
        }

        Button {
            text: "Добавить"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                const fromIsToMessage = 'Отправитель и получатель должны различаться'
                const noDistMessage = 'Расстояние не указано'
                const negDistMessage = 'Расстояние должно быть больше 0'
                const noValMessage = 'Объявленная стоимость не указана'
                const negValMessage = 'Объявленная стоимость должна быть больше нуля'

                var errors = []
                if (from.currentValue === to.currentValue) errors.push(fromIsToMessage)
                if (distance.text === '') errors.push(noDistMessage)
                if (Number(distance.text) <= 0) errors.push(negDistMessage)
                if (declaredValueR.text === '' || declaredValueK.text === '') errors.push(noValMessage)
                if (Number(declaredValueR.text) <= 0 || Number(declaredValueK.text) < 0) errors.push(negValMessage)

                errorsRepeater.model = errors
                if (errors.length > 0) return

                const fromId = from.currentValue
                const toId = to.currentValue
                const dist = Number(distance.text)
                const desc = description.text
                const val = Number(declaredValueR.text + '.' + declaredValueK.text.padStart('0', 2))

                DataProvider.addOrder(fromId, toId, dist, desc, val)
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
