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
    title: qsTr("Форма добавления дозаправки")
    modality: Qt.ApplicationModal

    Theme { id: theme }

    ColumnLayout {
        anchors.centerIn: parent
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
            }
        }

        RowLayout {
            spacing: 5
            Label {
                text: "К оплате: "
                Layout.minimumWidth: 150
            }
            TextField {
                id: price
                placeholderText: "Введите сумму..."
                Layout.fillWidth: true
                validator: DoubleValidator {
                    bottom: 0.0
                }
            }
        }

        RowLayout {
            spacing: 5
            Label {
                text: "Дата: "
                Layout.minimumWidth: 150
            }
            CalendarControl {
                id: date
                maximumDate: new Date()
            }
        }

        Button {
            text: "Добавить"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                DataProvider.addTruck(driver.currentValue, Number(price), date.selectedDate)
                root.close();
            }
        }
    }
}
