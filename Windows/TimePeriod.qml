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
    modality: Qt.ApplicationModal

    property int orderId: -1
    property var callback: null

    Theme { id: theme }

    ColumnLayout {
        anchors.centerIn: parent
        width: parent.width - 40
        spacing: 5

        RowLayout {
            spacing: 5
            Label {
                text: "Начало периода: "
                Layout.minimumWidth: 150
            }
            CalendarControl {
                id: begin
                selectedDate: {
                    var currentDate = new Date()

                    var year = currentDate.getFullYear()
                    var month = currentDate.getMonth()
                    var day = currentDate.getDate()

                    currentDate.setFullYear(year, month - 1, day)
                    currentDate.setHours(0)
                    currentDate.setMinutes(0)
                    currentDate.setSeconds(0)
                    currentDate.setMilliseconds(0)

                    return currentDate
                }
            }
        }

        RowLayout {
            spacing: 5
            Label {
                text: "Конец периода: "
                Layout.minimumWidth: 150
            }
            CalendarControl {
                id: end
                selectedDate: {
                    var currentDate = new Date()

                    currentDate.setHours(23)
                    currentDate.setMinutes(59)
                    currentDate.setSeconds(59)
                    currentDate.setMilliseconds(99)

                    return currentDate
                }
            }
        }

        Button {
            text: "Сформировать"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                const beginDate = begin.selectedDate
                beginDate.setHours(0)
                beginDate.setMinutes(0)
                beginDate.setSeconds(0)
                beginDate.setMilliseconds(0)

                const endDate = end.selectedDate
                endDate.setHours(23)
                endDate.setMinutes(59)
                endDate.setSeconds(59)
                endDate.setMilliseconds(99)

                const datesErrorMessage = 'Дата начала периода должна наступить раньше даты его окончания'

                var errors = []
                if (beginDate > endDate) errors.push(datesErrorMessage)

                errorsRepeater.model = errors
                if (errors.length > 0) return

                root.close();

                if (!callback) return
                callback(beginDate, endDate)
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
