import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0

Window {
    visible: true
    width: 480
    height: 600
    title: qsTr("Hello World")

    Item {
        id: root
        width: 200
        height: 100
        anchors.fill: parent

        MouseArea
        {
            anchors.fill: parent

            onClicked:
            {
                filler.currentIndex = index;
            }
        }
        ListView {
            id: filler
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: generateShape.top
            model: dataModel


            delegate: Text {
                text: " "+model.text
                font.pixelSize: 14
                color: "black"
                }



            boundsBehavior: ListView.StopAtBounds
        }

        Button {
            id: addShape
            width: parent.width/2-1
            text: "AddShape"
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            onClicked: {
                menu.open()
            }
            Menu {
                id: menu
                y: addShape.height

                MenuItem {
                    text: "Circle"
                    onClicked: {
                        console.log("Circle")
                        addCircle.open()
                    }
                }
                MenuItem {
                    text: "Triangle"
                    onClicked: {
                        console.log("Triangle")
                        addTriangle.open()
                    }
                }
                MenuItem {
                    text: "Rectangle"
                    onClicked: {
                        console.log("Rectangle")
                        addRectangle.open()
                    }
                }
            }
        }
        Button {
            id: delShape
            width: parent.width/2-1
            text: "DelShape"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            onClicked:  {
                delShapeDialog.open();
            }
        }
        Button {
            id: generateShape
            width: parent.width
            text: "GenerateShape"
            anchors.bottom: addShape.top
            anchors.bottomMargin: 2
            onClicked: {
                dataModel.generateShape()
            }
        }
    }

    Dialog {
        id: delShapeDialog
        width: 300
        height: 200
        anchors.centerIn: parent

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
                    value: 0
                }
            }
            Item {
                anchors.fill: parent
                anchors.topMargin: 50
                width: 120

                SpinBox {
                    id: spinCount
                    width: 275
                    value: 1
                }
            }

            Button {
                id: cencel
                text: "Cencel"
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                width: parent.width/2-1
                onClicked: delShapeDialog.close()
            }
            Button {
                id: okDelete
                text: "Delete"
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                width: parent.width/2-1
                onClicked: dataModel.delShape(spinStart.value, spinCount.value)
            }
        }
    }

    Dialog {
        id: addCircle
        width: 300
        height: 200
        anchors.centerIn: parent

        Item {
            id: addCircleIt
            anchors.fill: parent

            Item {
                anchors.fill: parent
                anchors.margins: 0
                width: 120

                SpinBox {
                    id: addCircleSpinStart
                    width: 275
                    anchors.centerIn: parent
                    value: 0
                }
            }

            Button {
                id: addCircleCencel
                text: "Cencel"
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                width: parent.width/2-1
                onClicked: addCircle.close()
            }
            Button {
                id: addCircleOk
                text: "Create"
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                width: parent.width/2-1
                onClicked: dataModel.addCircle(addCircleSpinStart.value)
            }
        }
    }
    Dialog {
        id: addTriangle
        width: 300
        height: 200
        anchors.centerIn: parent

        Item {
            id: addTriangleIt
            anchors.fill: parent

            Item {
                anchors.fill: parent
                anchors.topMargin: -130
                width: 120

                SpinBox {
                    id: addTriangleSpinA
                    width: 275
                    anchors.centerIn: parent
                    value: 0
                }
            }
            Item {
                anchors.fill: parent
                anchors.topMargin: -45
                width: 120

                SpinBox {
                    id: addTriangleSpinB
                    width: 275
                    anchors.centerIn: parent
                    value: 0
                }
            }
            Item {
                anchors.fill: parent
                anchors.topMargin: 40
                width: 120

                SpinBox {
                    id: addTriangleSpinC
                    width: 275
                    anchors.centerIn: parent
                    value: 0
                }
            }
            Button {
                id: addTriangleCencel
                text: "Cencel"
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                width: parent.width/2-1
                onClicked: addTriangle.close()
            }
            Button {
                id: addTriangleOk
                text: "Create"
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                width: parent.width/2-1
                onClicked: dataModel.addTriangle(addTriangleSpinA.value,
                                                 addTriangleSpinB.value,
                                                 addTriangleSpinC.value)
            }
        }
    }
    Dialog {
        id: addRectangle
        width: 300
        height: 200
        anchors.centerIn: parent

        Item {
            id: addRectangleIt
            anchors.fill: parent

            Item {
                anchors.fill: parent
                anchors.topMargin: -100
                width: 120

                SpinBox {
                    id: addRectangleSpinWindth
                    width: 275
                    anchors.centerIn: parent
                    value: 0
                }
            }

            Item {
                anchors.fill: parent
                anchors.topMargin: 0
                width: 120

                SpinBox {
                    id: addRectangleSpinHeight
                    width: 275
                    anchors.centerIn: parent
                    value: 0
                }
            }

            Button {
                id: addRectangleCencel
                text: "Cencel"
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                width: parent.width/2-1
                onClicked: addRectangle.close()
            }
            Button {
                id: addRectangleOk
                text: "Create"
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                width: parent.width/2-1
                onClicked: dataModel.addRectangle(addRectangleSpinWindth.value,
                                                  addRectangleSpinHeight.value)
            }
        }
    }
}
