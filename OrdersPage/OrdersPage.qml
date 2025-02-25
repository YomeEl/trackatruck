import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import '../Windows'
import '../helpers.js' as Helpers

GridLayout {
    id: root

    columns: 2
    columnSpacing: 0
    rowSpacing: 0

    Text {
        text: 'Активные заказы'
        font.pointSize: 20
        horizontalAlignment: Text.AlignHCenter
        Layout.preferredWidth: parent.width / 3
        Layout.columnSpan: 2
        Layout.fillWidth: true
    }

    OrdersTable {
        id: table
        Layout.fillWidth: true
        Layout.fillHeight: true
        onSelected: details.model = model
    }

    OrderDetails {
        id: details
        Layout.preferredWidth: 2 * parent.width / 3
        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
        onGenerateReport: root.generateReport(order)
    }

    function appendTableRow(rows, key, value) {
        rows.push([key, value])
    }

    function appendSignature(signatures, title, fields) {
        signatures.push({ title: title, fields: fields })
    }

    function generateReport(order) {
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
        if (!order.finished) {
            appendTableRow(rows, 'Дата получения заказа (расчётная)', order.receivedAtString)
            appendTableRow(rows, 'Дата получения заказа (фактическая)', '')
        } else {
            appendTableRow(rows, 'Дата получения заказа', order.receivedAtString)
        }
        appendTableRow(rows, 'Описание груза', order.description)
        appendTableRow(rows, 'Объяевленная стоимость груза', Helpers.formatMoney(order.value))

        appendSignature(signatures, 'Отправил', ['ФИО', 'должность', 'подпись', 'дата'])
        appendSignature(signatures, 'Получил', ['ФИО', 'должность', 'подпись', 'дата'])
        appendSignature(signatures, 'Водитель', ['ФИО', 'подпись', 'дата'])

        reportWindow.tableData = rows
        reportWindow.signatures = signatures

        reportWindow.show()
    }

    Report {
        id: reportWindow
        visible: false
    }
}
