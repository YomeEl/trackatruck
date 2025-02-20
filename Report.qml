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

    function getDateString() {
        let date = new Date
        let d = String(date.getDate()).padStart(2, '0')
        let m = String(date.getMonth() + 1).padStart(2, '0')
        let y = date.getFullYear()
        let hrs = date.getHours()
        let min = String(date.getMinutes()).padStart(2, '0')

        return [d, m, y].join('.') + ' в ' + [hrs, min].join(':')
    }

    FileDialog {
        id: saveFileDialog
        title: 'Сохранение отчёта'
        selectExisting: false
        defaultSuffix: 'png'
        folder: shortcuts.desktop
        nameFilters: ['Изображение (*.png)']
        onAccepted: {
            var str = saveFileDialog.fileUrl.toString()
            var path = saveFileDialog.fileUrl.toString().substring(8, str.length)
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
            text: root.title + ' №' + root.number
            font.pointSize: Math.round(root.scale * 9.6)
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: root.scale * 8
        }

        // Таблица
        Column {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: root.scale * 32
            anchors.leftMargin: root.scale * 8
            width: parent.width - root.scale * 16
            spacing: -1

            Repeater {
                model: root.tableData
                Row {
                    spacing: -1
                    width: parent.width
                    Rectangle {
                        width: parent.width / 2 - root.scale * 4
                        height: txt.height + root.scale * 4.8
                        border.color: "black"

                        Text {
                            font.pointSize: root.scale * 2.8
                            anchors.centerIn: parent
                            text: modelData.key
                        }
                    }

                    Rectangle {
                        width: parent.width / 2 - root.scale * 4
                        height: txt.height + root.scale * 4.8
                        border.color: "black"

                        Text {
                            id: txt
                            font.pointSize: root.scale * 2.8
                            width: parent.width - root.scale * 4
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
            height: root.scale * 64
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: root.scale * 8
            anchors.bottomMargin: root.scale * 8

            Column {
                spacing: root.scale * 8

                Text {
                    font.pointSize: root.scale * 2.8
                    text: 'Документ сформирован ' + root.getDateString()
                }

                Repeater {
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
            }
        }
    }

    Button {
        text: 'Сохранить...'
        onClicked: saveFileDialog.open()
        anchors {
            top: root.top
            left: root.left
        }
    }
}
