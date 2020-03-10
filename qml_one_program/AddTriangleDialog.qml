import QtQuick 2.0
import QtQuick.Controls 2.12

Dialog {
    id: control
    width: 300
    height: 200
    anchors.centerIn: parent

    property real rA: 0.0
    property real rB: 0.0
    property real rC: 0.0
    property bool isEditing: false
    onRAChanged: {
        addTriangleSpinA.value = rA * addTriangleSpinA.ratio
    }
    onRBChanged: {
        addTriangleSpinB.value = rB * addTriangleSpinB.ratio
    }
    onRCChanged: {
        addTriangleSpinC.value = rC * addTriangleSpinC.ratio
    }
    Item {
        id: addTriangleIt
        anchors.fill: parent

        Item {
            anchors.fill: parent
            anchors.topMargin: -130
            width: 120

            DoubleSpinBox {
                id: addTriangleSpinA
                width: 275
                anchors.centerIn: parent
                value: 0.0
                onRealValueChanged: {
                    control.rA = realValue
                }
            }
        }
        Item {
            anchors.fill: parent
            anchors.topMargin: -45
            width: 120

            DoubleSpinBox {
                id: addTriangleSpinB
                width: 275
                anchors.centerIn: parent
                value: 0.0
                onRealValueChanged: {
                    control.rB = realValue
                }
            }
        }
        Item {
            anchors.fill: parent
            anchors.topMargin: 40
            width: 120

            DoubleSpinBox {
                id: addTriangleSpinC
                width: 275
                anchors.centerIn: parent
                value: 0.0
                onRealValueChanged: {
                    control.rC = realValue
                }
            }
        }
        Button {
            id: addTriangleCencel
            text: "Cancel"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: parent.width/2-1
            onClicked: control.reject()
        }
        Button {
            id: addTriangleOk
            text: isEditing ? "Edit" : "Create"
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            width: parent.width/2-1
            onClicked: control.accept()
        }
    }
}
