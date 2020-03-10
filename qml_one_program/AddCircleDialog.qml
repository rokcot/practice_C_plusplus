import QtQuick 2.12
import QtQuick.Controls 2.12

Dialog {
    id: control
    implicitWidth: 300
    implicitHeight: 200

    property real radius: 0.0
//    property alias radius: addCircleSpinStart.value
    property bool isEditing: false

    onRadiusChanged: {
        addCircleSpinStart.value = radius * addCircleSpinStart.ratio
    }

    Item {
        id: addCircleIt
        anchors.fill: parent

        Item {
            anchors.fill: parent
            anchors.margins: 0
            width: 120

            DoubleSpinBox {
                id: addCircleSpinStart
                width: 275
                anchors.centerIn: parent
                value: 0.0

                onRealValueChanged: {
                    control.radius = realValue
                }
            }
        }

        Button {
            id: addCircleCencel
            text: qsTr("Cancel")
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: parent.width/2-1
            onClicked: control.reject()
        }
        Button {
            id: addCircleOk
            text: isEditing ? qsTr("Edit") : qsTr("Create")
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            width: parent.width/2-1
            onClicked: control.accept()
        }
    }
}
