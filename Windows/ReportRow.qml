import QtQuick 2.15

Row {
    id: root
    spacing: -1
    width: parent.width

    property double scale: 1
    property var rowModel: null
    property int borderWidth: 1

    Repeater {
        model: root.rowModel
        delegate: Rectangle {
            width: parent.width / rowModel.length - root.scale * 4
            height: txt.height + root.scale * 4.8
            border.color: "black"
            border.width: root.borderWidth

            Text {
                id: txt
                font.pointSize: root.scale * 2.8
                anchors.centerIn: parent
                text: modelData
            }
        }
    }
}
