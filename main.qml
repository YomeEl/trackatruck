import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import 'OrdersPage'
import 'helpers.js' as Helpers

ApplicationWindow {
    width: 800
    height: 600
    visible: true
    title: qsTr("Track a truck!")

    menuBar: MenuBar {
        Menu {
            title: qsTr("Новый")
            Action {
                text: qsTr("Заказ")
                onTriggered: newOrderWindow.show()
            }
            Action { text: qsTr("Водитель") }
            Action { text: qsTr("Грузовик") }
        }

        Menu {
            title: qsTr("Открыть")
            Action { text: qsTr("Заказы") }
            Action { text: qsTr("Водители") }
            Action { text: qsTr("Автопарк") }
            Action { text: qsTr("Клиенты") }
        }
        Menu {
            title: qsTr("Отчёт")
            Action { text: qsTr("О заказах") }
            Action { text: qsTr("О расходах на топливо") }
        }
    }

    OrdersPage {
        function appendTableRow(rows, key, value) {
            rows.push({ key: key, value: value })
        }

        function appendSignature(signatures, title, fields) {
            signatures.push({ title: title, fields: fields })
        }

        onGenerateReport: {
            let rows = []
            let signatures = []

            reportWindow.title = 'Накладная'
            reportWindow.number = order.id

            appendTableRow(rows, 'Водитель', order.driverName)
            appendTableRow(rows, 'Автомобиль', order.truckModel)
            appendTableRow(rows, 'Гос. номер', order.truckNumber)
            appendTableRow(rows, 'Отправитель', order.fromName)
            appendTableRow(rows, 'Адрес отправителя', order.fromAddress)
            appendTableRow(rows, 'Получатель', order.toName)
            appendTableRow(rows, 'Адрес получателя', order.toAddress)
            appendTableRow(rows, 'Расстояние', Helpers.splitWithDots(order.distance) + ' км')
            appendTableRow(rows, 'Дата создания заказа', order.createdAtString)
            appendTableRow(rows, 'Дата отправления заказа', order.sentAtString)
            appendTableRow(rows, 'Дата получения заказа (расчётная)', order.receivedAtString)
            appendTableRow(rows, 'Дата получения заказа (фактическая)', '')
            appendTableRow(rows, 'Описание груза', order.description)
            appendTableRow(rows, 'Объяевленная стоимость груза', Helpers.formatMoney(order.value))

            appendSignature(signatures, 'Отправил', ['ФИО', 'должность', 'подпись', 'дата'])
            appendSignature(signatures, 'Получил', ['ФИО', 'должность', 'подпись', 'дата'])
            appendSignature(signatures, 'Водитель', ['ФИО', 'подпись', 'дата'])

            reportWindow.tableData = rows
            reportWindow.signatures = signatures

            reportWindow.show()
        }
    }

    Report {
        id: reportWindow
        visible: false
    }

    NewOrder {
        id: newOrderWindow
        visible: false
    }
}
