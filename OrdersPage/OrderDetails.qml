import QtQuick 2.15
import '../Theme'

Rectangle {
    Theme { id: theme }

    id: root

    property var model: null;

    color: theme.background

    Column {
        spacing: 5
        padding: 5
        visible: root.model !== null
        Text {
            id: driverName_text
            text: root.model ? 'Имя водителя: ' + root.model.driverName : 'Загрузка...'
        }
        Text {
            id: driverContractDate_text
            text: root.model ? 'Дата договора: ' + root.model.driverContractDate : 'Загрузка...'
        }
        Text {
            id: truckModel_text
            text: root.model ? 'Грузовик: ' + root.model.truckModel : 'Загрузка...'
        }
        Text {
            id: truckNumber_text
            text: root.model ? 'Гос. номер: ' + root.model.truckNumber : 'Загрузка...'
        }
        Text {
            id: truckLastMilage_text
            text: root.model ? 'Пробег: ' + root.model.truckLastMilage : 'Загрузка...'
        }
        Text {
            id: truckLastMaintananceDate_text
            text: root.model ? 'Дата ТО: ' + root.model.truckLastMaintananceDate : 'Загрузка...'
        }
        Text {
            id: fromName_text
            text: root.model ? 'Отправитель: ' + root.model.fromName : 'Загрузка...'
        }
        Text {
            id: fromAddress_text
            text: root.model ? 'Адрес отправителя: ' + root.model.fromAddress : 'Загрузка...'
        }
        Text {
            id: toName_text
            text: root.model ? 'Получатель: ' + root.model.toName : 'Загрузка...'
        }
        Text {
            id: toAddress_text
            text: root.model ? 'Адрес получателя: ' + root.model.toAddress : 'Загрузка...'
        }
        Text {
            id: createdAt_text
            text: root.model ? 'Создан: ' + root.model.createdAt : 'Загрузка...'
        }
        Text {
            id: sentAt_text
            text: root.model ? 'Отправлен: ' + root.model.sentAt : 'Загрузка...'
        }
        Text {
            id: receivedAt_text
            text: root.model ? 'Получен: ' + root.model.receivedAt : 'Загрузка...'
        }
        Text {
            id: finished_text
            text: root.model ? 'Закончен: ' + root.model.finished : 'Загрузка...'
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
            text: root.model ? 'Объявленная стоимость груза: ' + root.model.value : 'Загрузка...'
        }
    }
}
