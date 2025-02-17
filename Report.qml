import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    visible: true
    width: 595   // A4 width in points
    height: 842  // A4 height in points
    title: "Накладная"

    property int number: 0
    property var tableData: [
        { key: 'row 1', value: 'val 1' },
        { key: 'row 2', value: 'val 2' },
        { key: 'row 3', value: 'val 3' },
        { key: 'row 4', value: 'val 4'.repeat(30) },
        { key: 'row 5', value: 'val 5' },
    ]
    property var signatures: [
        { title: 'Отправил', fields: ['ФИО', 'должность', 'подпись', 'дата'] },
        { title: 'Получил', fields: ['ФИО', 'должность', 'подпись', 'дата'] },
        { title: 'Водитель', fields: ['ФИО', 'подпись', 'дата'] }
    ]

    function getDateString() {
        let date = new Date
        let d = String(date.getDate()).padStart(2, '0')
        let m = String(date.getMonth() + 1).padStart(2, '0')
        let y = date.getFullYear()
        let hrs = date.getHours()
        let min = String(date.getMinutes()).padStart(2, '0')

        return [d, m, y].join('.') + ' в ' + [hrs, min].join(':')
    }

    Rectangle {
        width: parent.width
        height: parent.height
        color: "white"
        border.color: "black"

        // Заголовок
        Text {
            text: root.title + ' №' + root.number
            font.pointSize: 24
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20
        }

        // Таблица
        Column {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 80
            anchors.leftMargin: 20
            width: parent.width - 40
            spacing: -1

            Repeater {
                model: root.tableData
                Row {
                    spacing: -1
                    width: parent.width
                    Rectangle {
                        width: parent.width / 2 - 10
                        height: Math.max(40, txt.height + 10)
                        border.color: "black"

                        Text {
                            anchors.centerIn: parent
                            text: modelData.key
                        }
                    }

                    Rectangle {
                        width: parent.width / 2 - 10
                        height: Math.max(40, txt.height + 10)
                        border.color: "black"

                        Text {
                            id: txt
                            width: parent.width
                            wrapMode: Text.WordWrap
                            anchors.centerIn: parent
                            text: modelData.value
                        }
                    }
                }
            }
        }

        // Подписи
        Rectangle {
            width: parent.width
            height: 160
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            Column {
                anchors.centerIn: parent
                spacing: 10

                Text {
                    text: 'Документ сформирован ' + root.getDateString()
                }

                Repeater {
                    model: root.signatures
                    delegate: Row {
                        spacing: 5
                        Text {
                            text: modelData.title
                        }
                        Repeater {
                            model: modelData.fields
                            delegate: ColumnLayout {
                                spacing: 5
                                Text { text: '_'.repeat(15) }
                                Text {
                                    text: modelData
                                    horizontalAlignment: Text.AlignHCenter
                                    Layout.fillWidth: true
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
