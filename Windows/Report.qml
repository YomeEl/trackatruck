import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    visible: true

    readonly property int a4width: 210  // A4 width in mm
    readonly property int a4height: 297 // A4 height in mm

    property int windowMargin: 50

    property double scale: (Screen.desktopAvailableHeight - windowMargin) / a4height
    width: scale * a4width
    height: scale * a4height
    x: 0
    y: 0

    property int number: 0
    property var tableData: []
    property var signatures: []

    property var tableHeader: []
    property var pageTableData: tableData.slice(currentPage * rowsOnPage, (currentPage + 1) * rowsOnPage)

    property int rowsOnPage: 16
    property int currentPage: 0
    readonly property int pages: (tableData.length / rowsOnPage) + 1

    property var periodBegin: null
    property var periodEnd: null

    function getDateString(joinWith = ' в ', date = new Date) {
        if (!date) date = new Date
        let d = String(date.getDate()).padStart(2, '0')
        let m = String(date.getMonth() + 1).padStart(2, '0')
        let y = date.getFullYear()
        let hrs = date.getHours()
        let min = String(date.getMinutes()).padStart(2, '0')

        return [d, m, y].join('.') + joinWith + [hrs, min].join(':')
    }

    FileDialog {
        id: saveFileDialog
        title: 'Сохранение отчёта'
        selectExisting: false
        defaultSuffix: 'png'
        folder: shortcuts.desktop
        nameFilters: ['Изображение (*.png)']
        onAccepted: {
            let str = saveFileDialog.fileUrl.toString()
            let path = saveFileDialog.fileUrl.toString().substring(8, str.length)
            docRoot.grabToImage(function(result) {
                result.saveToFile(saveFileDialog.fileUrl.toString().substring(8, str.length));
            });
        }
    }

    // Документ
    Rectangle {
        id: docRoot
        width: parent.width
        height: parent.height
        color: "white"

        // Заголовок
        Text {
            id: titleText
            text: root.title + (root.number > 0 ? (' №' + root.number) : '')
            font.pointSize: Math.round(root.scale * 9.6)
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: root.scale * 8
        }

        Text {
            id: periodText
            visible: periodBegin && periodEnd
            text: "За период с " + getDateString(' ', root.periodBegin) + " по " + getDateString(' ', root.periodEnd)
            font.pointSize: Math.round(root.scale * 5)
            anchors.top: titleText.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: root.scale * 4
        }

        // Таблица
        Column {
            anchors.top: periodText.bottom
            anchors.left: parent.left
            anchors.topMargin: root.scale * 4
            anchors.leftMargin: root.scale * 8
            width: parent.width - root.scale * 16
            spacing: -1

            ReportRow {
                visible: tableHeader.length > 0
                scale: root.scale
                rowModel: tableHeader
                borderWidth: 3
            }

            Repeater {
                model: root.pageTableData
                ReportRow {
                    scale: root.scale
                    rowModel: modelData
                }
            }
        }

        // Подписи
        Rectangle {
            width: parent.width
            height: signatures.length > 0 ? root.scale * 64 : pageText.height
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: root.scale * 8
            anchors.bottomMargin: root.scale * 8

            Column {
                spacing: root.scale * 8

                Repeater {
                    visible: signatures.length > 0
                    model: root.signatures
                    delegate: Row {
                        spacing: root.scale * 2
                        Text {
                            font.pointSize: root.scale * 2.8
                            text: modelData.title
                        }
                        Repeater {
                            model: modelData.fields
                            delegate: ColumnLayout {
                                spacing: root.scale * 2
                                Text {
                                    font.pointSize: root.scale * 2.8
                                    text: '_'.repeat(root.scale * 6)
                                }
                                Text {
                                    font.pointSize: root.scale * 2.8
                                    text: modelData
                                    horizontalAlignment: Text.AlignHCenter
                                    Layout.fillWidth: true
                                }
                            }
                        }
                    }
                }

                Row {
                    spacing: root.scale * 16

                    Text {
                        font.pointSize: root.scale * 2.8
                        text: 'Документ сформирован ' + root.getDateString()
                    }

                    Text {
                        id: pageText
                        font.pointSize: root.scale * 2.8
                        text: 'Страница ' + (currentPage + 1) + ' из ' + pages
                    }
                }
            }
        }
    }

    Row {
        anchors {
            top: root.top
            left: root.left
        }

        Button {
            text: 'Сохранить страницу...'
            onClicked: saveFileDialog.open()
        }

        Button {
            text: 'Предыдущая страница'
            enabled: root.currentPage > 0
            onClicked: root.currentPage--
        }

        Button {
            text: 'Следующая страница'
            enabled: root.currentPage + 1 < root.pages
            onClicked: root.currentPage++
        }
    }
}
