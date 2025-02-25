import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import '../Theme'

Window {
    id: root
    width: 640
    height: 700
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
                        text: model.truckModel
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
                text: "Дата отправления: "
                Layout.minimumWidth: 150
            }
            CalendarControl {
                id: sentAt
                minimumDate: new Date()
            }
        }

        RowLayout {
            spacing: 5
            Label {
                text: "Ожидаемая дата прибытия: "
                Layout.minimumWidth: 150
            }
            CalendarControl {
                id: receivedAt
                minimumDate: new Date()
            }
        }

        Button {
            text: "Назначить"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                if (orderId === -1) {
                    console.log('Что-то пошло не так')
                    return
                }

                const driverId = driver.currentValue
                const truckId = truck.currentValue
                const sent = sentAt.selectedDate
                const received = receivedAt.selectedDate

                const datesErrorMessage = 'Дата отправления должна наступить раньше даты получения'

                var errors = []
                if (sent > received) errors.push(datesErrorMessage)

                errorsRepeater.model = errors
                if (errors.length > 0) return

                DataProvider.assignTruckAndDriver(root.orderId, driverId, truckId, sent, received)
                root.close();
            }
        }

        Text {
            visible: errorsRepeater.model.length > 0
            text: "Ошибки:"
        }

        Repeater {
            id: errorsRepeater
            model: []
            delegate: Text {
                color: theme.warningHigh
                text: modelData
            }
        }
    }
}
