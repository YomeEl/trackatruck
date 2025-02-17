import QtQuick 2.15
import QtQuick.Controls 2.15

import '../Theme'

Rectangle {
    Theme { id: theme }

    id: root

    property var model: null;

    height: childrenRect.height
    width: childrenRect.width

    function formatMoney(number) {
        const split = String(number).split('.')
        let integer = split[0]
        let decimal = split[1] ? split[1] : '00'

        decimal = decimal.padEnd(2, '0')

        const zeroes = (3 - (integer.length % 3)) % 3
        integer = integer.padStart(integer.length + zeroes, '0')

        let groupsCnt = integer.length / 3
        let groups = []
        for (let i = 0; i < groupsCnt; i++) {
            let from = i === 0 ? zeroes : 3 * i
            let to = 3 * i + 3
            let sub = integer.substring(from, to)
            groups.push(sub)
        }
        return groups.join('.') + ' руб. ' + decimal + ' коп.'
    }

    Column {
        spacing: 5
        padding: 5
        visible: root.model !== null
        Text {
            id: driverName_text
            visible: root.model && root.model.driverName
            text: root.model ? 'Имя водителя: ' + root.model.driverName : 'Загрузка...'
        }
        Text {
            id: truckModel_text
            visible: root.model && root.model.truckModel
            text: root.model ? 'Грузовик: ' + root.model.truckModel : 'Загрузка...'
        }
        Text {
            id: truckNumber_text
            visible: root.model && root.model.truckModel
            text: root.model ? 'Гос. номер: ' + root.model.truckNumber : 'Загрузка...'
        }
        Text {
            id: fromName_text
            text: root.model ? 'Отправитель: ' + root.model.fromName + ', ' + root.model.fromAddress : 'Загрузка...'
        }
        Text {
            id: toName_text
            text: root.model ? 'Получатель: ' + root.model.toName + ', ' + root.model.toAddress : 'Загрузка...'
        }
        Text {
            id: createdAt_text
            text: root.model ? 'Создан: ' + root.model.createdAtString : 'Загрузка...'
        }
        Text {
            id: sentAt_text
            text: root.model ? 'Отправлен: ' + root.model.sentAtString : 'Загрузка...'
        }
        Text {
            id: receivedAt_text
            text: root.model ? 'Получен: ' + root.model.receivedAtString : 'Загрузка...'
        }
        Text {
            id: distance_text
            text: root.model ? 'Расстояние: ' + root.model.distance : 'Загрузка...'
        }
        Text {
            id: description_text
            text: root.model ? 'Описание: ' + root.model.description : 'Загрузка...'
        }
        Text {
            id: value_text
            text: root.model ? 'Объявленная стоимость груза: ' + formatMoney(root.model.value) : 'Загрузка...'
        }
        Column {
            id: buttonsColumn
            spacing: 5

            Button {
                text: 'Сформировать накладную'
                visible: root.model && root.model.driverName
            }
            Button {
                visible: root.model && root.model.driverName
                text: 'Отметить как выполненный'
            }
            Button {
                visible: root.model && !root.model.driverName
                text: 'Назначить водителя и грузовик'
            }
            Button {
                text: 'Отменить'
            }
        }
    }
}
