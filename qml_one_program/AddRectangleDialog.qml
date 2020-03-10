import QtQuick 2.12
import QtQuick.Controls 2.12

Dialog {
    id: control
    width: 300
    height: 200
    anchors.centerIn: parent
    property real rHeight: 0.0
    property real rWidth: 0.0

    property bool isEditing: false

    onRWidthChanged: {
        addRectangleSpinWindth.value = rWidth * addRectangleSpinWindth.ratio
    }

    onRHeightChanged: {
        addRectangleSpinHeight.value = rHeight * addRectangleSpinHeight.ratio
    }

    Item {
        id: addRectangleIt
        anchors.fill: parent

        Item {
            anchors.fill: parent
            anchors.topMargin: -100
            width: 120

            DoubleSpinBox {
                id: addRectangleSpinWindth
                width: 275
                anchors.centerIn: parent
                value: 0.0
                onRealValueChanged: {
                    control.rWidth = realValue
                }
            }
        }

        Item {
            anchors.fill: parent
            anchors.topMargin: 0
            width: 120

            DoubleSpinBox {
                id: addRectangleSpinHeight
                width: 275
                anchors.centerIn: parent
                value: 0.0
                onRealValueChanged: {
                    control.rHeight = realValue
                }
            }
        }

        Button {
            id: addRectangleCencel
            text: "Cancel"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: parent.width/2-1
            onClicked: control.reject()
        }
        Button {
            id: addRectangleOk
            text: isEditing ? "Edit" : "Create"
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            width: parent.width/2-1
            onClicked: control.accept()
        }
    }
}
