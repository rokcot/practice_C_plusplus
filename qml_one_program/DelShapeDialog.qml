import QtQuick 2.12
import QtQuick.Controls 2.12

Dialog {
    id: control
    width: 300
    height: 200
    anchors.centerIn: parent
    property int indexFirst: 0
    property int indexLast: 0

    Item {
        id: delIt
        anchors.fill: parent

        Item {
            anchors.fill: parent
            anchors.margins: 0
            width: 120

            SpinBox {
                id: spinStart
                width: 275
                to: 1000
                value: indexFirst

            }
        }
        Item {
            anchors.fill: parent
            anchors.topMargin: 50
            width: 120

            SpinBox {
                id: spinCount
                width: 275
                to: 1000
                value: indexLast
            }
        }

        Button {
            id: cencel
            text: "Cencel"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: parent.width/2-1
            onClicked: control.reject()
        }
        Button {
            id: okDelete
            text: "Delete"
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            width: parent.width/2-1
            onClicked: control.accept()
        }
    }
}
