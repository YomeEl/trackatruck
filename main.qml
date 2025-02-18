import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import 'OrdersPage'

ApplicationWindow {
    width: 800
    height: 600
    visible: true
    title: qsTr("Track a truck!")

    menuBar: MenuBar {
        Menu {
            title: qsTr("Новый")
            Action { text: qsTr("Заказ") }
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

    }

    Report {
        visible: false
        number: 1
    }

    NewOrder {
        visible: true
    }
}
