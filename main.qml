import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import 'OrdersPage'
import 'DriversPage'
import 'TrucksPage'
import 'ClientsPage'

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
            Action {
                text: qsTr("Водитель")
                onTriggered: newDriverWindow.show()
            }
            Action {
                text: qsTr("Грузовик")
                onTriggered: newTruckWindow.show()
            }
            Action {
                text: qsTr("Клиент")
                onTriggered: newClientWindow.show()
            }
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
            Action {
                text: qsTr("Автопарк")
                onTriggered: root.pushPage(trucksPage)
            }
            Action {
                text: qsTr("Клиенты")
                onTriggered: root.pushPage(clientsPage)
            }
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
        anchors {
            fill: parent
        }
    }

    // Pages

    Component {
        id: ordersPage
        OrdersPage {}
    }

    Component {
        id: driversPage
        DriversPage {}
    }

    Component {
        id: trucksPage
        TrucksPage {}
    }

    Component {
        id: clientsPage
        ClientsPage {}
    }

    // Windows

    NewOrder {
        id: newOrderWindow
        visible: false
    }

    NewDriver {
        id: newDriverWindow
        visible: false
    }

    NewTruck {
        id: newTruckWindow
        visible: false
    }

    NewClient {
        id: newClientWindow
        visible: false
    }
}
