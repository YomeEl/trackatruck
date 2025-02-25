import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import '../Theme'

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Форма назначения водителя и грузовика")
    modality: Qt.ApplicationModal

    property int orderId: -1

    Theme { id: theme }

    ColumnLayout {
        anchors.centerIn: parent
        width: parent.width - 40
        spacing: 5

        RowLayout {
            spacing: 5
            Label {
                text: "Водитель:"
                Layout.minimumWidth: 150
            }
            ComboBox {
                id: driver
                model: DataProvider.getDriversList()
                textRole: "name"
                valueRole: "id"
                Layout.fillWidth: true
                delegate: ItemDelegate {
                    visible: model.isFree
                    width: driver.width
                    height: model.isFree ? implicitHeight : 0
                    Text {
                        text: model.name
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: 10
                        }
                    }
                }
            }
        }

        RowLayout {
            spacing: 5
            Label {
                text: "Грузовик:"
                Layout.minimumWidth: 150
            }
            ComboBox {
                id: truck
                model: DataProvider.getTrucksList()
                textRole: "truckModel"
                valueRole: "id"
                Layout.fillWidth: true
                delegate: ItemDelegate {
                    visible: model.isFree
                    width: truck.width
                    height: model.isFree ? implicitHeight : 0
                    Text {
                        text: model.name
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: 10
                        }
                    }
                }
            }
        }

        RowLayout {
            spacing: 5
            Label {
                text: "Ожидаемая дата доставки: "
                Layout.minimumWidth: 150
            }
            CalendarControl {
                id: date
                minimumDate: new Date()
            }
        }

        Button {
            text: "Назначить"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                const driverId = driver.currentValue
                const truckId = truck.currentValue
                DataProvider.assignTruckAndDriver(driverId, truckId, date.selectedDate)
                root.close();
            }
        }
    }
}
