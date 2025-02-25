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
            Action {
                text: qsTr("Дозаправка")
                onTriggered: newRefuelingWindow.show()
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
            Action {
                text: qsTr("О нагрузке")

                onTriggered: {
                    timePeriodWindow.title = "Выбор временного интервала для отчёта о нагрузке"

                    timePeriodWindow.callback = (begin, end) => {
                        const data = DataProvider.getDriverReportData(begin, end)
                        let rows = []
                        for (const o of data) {
                            rows.push([o.name, o.ordersFinished, o.hoursEnroute, o.distanceTraveled])
                        }
                        reportWindow.title = "Отчёт о нагрузке"
                        reportWindow.tableHeader = ["ФИО", "Заказов", "В пути (ч)", "Расстояние (км)"]
                        reportWindow.tableData = rows
                        reportWindow.signatures = { title: "Бухгалтер", fields: ["ФИО", "подпись", "дата"] }
                        reportWindow.periodBegin = begin
                        reportWindow.periodEnd = end
                        reportWindow.show()
                    }

                    timePeriodWindow.show()
                }
            }
            Action {
                text: qsTr("О расходах на топливо")
                onTriggered: {
                    timePeriodWindow = "Выбор временного интервала для отчёта расходах на топливо"

                    timePeriodWindow.callback = (begin, end) => {
                        console.log(begin, end)
                        DataProvider.getDriverReportData(begin, end)
                    }

                    timePeriodWindow.show()
                }
            }
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

    NewRefueling {
        id: newRefuelingWindow
        visible: false
    }

    TimePeriod {
        id: timePeriodWindow
        visible: false
    }

    Report {
        id: reportWindow
        visible: false
    }
}
