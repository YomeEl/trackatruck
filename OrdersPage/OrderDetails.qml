import QtQuick 2.15
import QtQuick.Controls 2.15

import '../Windows/'
import '../Theme'
import '../helpers.js' as Helpers

Rectangle {
    Theme { id: theme }

    id: root

    property var model: null;

    signal generateReport(var order)

    height: childrenRect.height
    width: childrenRect.width

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
            text: root.model ? 'Расстояние: ' + Helpers.splitWithDots(root.model.distance) + ' км' : 'Загрузка...'
        }
        Text {
            id: description_text
            text: root.model ? 'Описание: ' + root.model.description : 'Загрузка...'
        }
        Text {
            id: value_text
            text: root.model ? 'Объявленная стоимость груза: ' + Helpers.formatMoney(root.model.value) : 'Загрузка...'
        }
        Column {
            id: buttonsColumn
            spacing: 5

            Button {
                text: 'Сформировать накладную'
                visible: root.model && root.model.driverName
                onClicked: generateReport(root.model)
            }
            Button {
                visible: root.model && root.model.driverName
                text: 'Отметить как выполненный'
            }
            Button {
                visible: root.model && !root.model.driverName
                text: 'Назначить водителя и грузовик'
                onClicked: assignDriverAndTruckWindow.show()
            }
            Button {
                visible: root.model && !root.model.finished
                text: 'Отменить'
                onClicked: DataProvider.cancelOrder(root.model.id)
            }
        }
    }

    AssignDriverAndTruck {
        id: assignDriverAndTruckWindow
        visible: false
    }
}
