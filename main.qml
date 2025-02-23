import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import 'OrdersPage'
import 'DriversPage'
import 'Windows'
import 'helpers.js' as Helpers

ApplicationWindow {
    id: root

    width: 800
    height: 600
    visible: true
    title: qsTr("Track a truck!")

    function pushPage(page) {
        if (stackView.currentItem === page) return;
        if (stackView.depth > 1) stackView.pop()
        if (stackView.currentItem !== page) stackView.push(page)
    }

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
            Action {
                text: qsTr("Заказы")
                onTriggered: root.pushPage(ordersPage)
            }
            Action {
                text: qsTr("Водители")
                onTriggered: root.pushPage(driversPage)
            }
            Action { text: qsTr("Автопарк") }
            Action { text: qsTr("Клиенты") }
        }
        Menu {
            title: qsTr("Отчёт")
            Action { text: qsTr("О заказах") }
            Action { text: qsTr("О расходах на топливо") }
        }
    }

    StackView {
        id: stackView
        initialItem: ordersPage
        anchors.fill: parent
    }

    Component {
        id: ordersPage
        OrdersPage {}
    }

    Component {
        id: driversPage
        DriversPage {}
    }

    NewOrder {
        id: newOrderWindow
        visible: false
    }
}
