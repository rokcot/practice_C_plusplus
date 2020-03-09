import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4

Window {
    visible: true
    width: 520
    height: 600
    title: qsTr("Hello World")
    property int aNumber: 0
    property int iNumber: 0

    Item {
        id: root
        width: 200
        height: 100
        anchors.fill: parent

        ListView {
            id: filler
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: generateShape.top
            model: dataModel

            delegate: Rectangle {
                focus: true
                width: root.width
                height: 20
                color: ((index <= filler.currentIndex) && (index >= aNumber)) ||
                       ((index >= filler.currentIndex) && (index <= aNumber))
                       ? "#800000" : "black"

                MouseArea {
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    anchors.fill: parent
                    onClicked: {
                        switch (mouse.button)
                        {
                        case Qt.RightButton:
                            delObject.open()
                            break;
                        case Qt.LeftButton:
                            if(mouse.modifiers === Qt.ControlModifier){
                                aNumber = filler.currentIndex
                            }else{
                                aNumber = model.index
                            }
                            filler.currentIndex = model.index
                            console.log(filler.currentIndex, " - ",
                                        index, aNumber)
                            break;
                        default:
                            break;
                        }
                    }
                }
                Menu {
                    id: delObject
                    y: addShape.height
                    MenuItem {
                        text: "Delete"
                        onClicked: {
                            if(aNumber > filler.currentIndex){
                                iNumber = filler.currentIndex
                                iNumber = (aNumber+1) - iNumber
                                dataModel.delShape(iNumber, aNumber)
                            }else if(aNumber != filler.currentIndex){
                                iNumber = filler.currentIndex
                                iNumber = (iNumber+1) - aNumber
                                dataModel.delShape(aNumber, iNumber)
                            }else{
                                dataModel.delShape(aNumber, 1)
                            }
                        }
                    }
                }
                Text {
                    id: textBlock
                    function getColor(name) {
                        switch (name)
                        {
                        case "circle":
                            return "lime"
                        case "triangle":
                            return "Yellow"
                        case "rectangle":
                            return "Fuchsia"
                        default:
                            return "black"
                        }
                    }
                    leftPadding: 5
                    text: model.text + "(" + getColor(model.name) + ")"
                    font.pixelSize: 14
                    color: getColor(model.name)
                }
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
                if(aNumber > filler.currentIndex){
                    iNumber = filler.currentIndex
                    iNumber = (aNumber+1) - iNumber
                }else if(aNumber != filler.currentIndex){
                    iNumber = filler.currentIndex
                    iNumber = (iNumber+1) - aNumber
                }
                console.log("iNumber="+iNumber+" filler="+filler.currentIndex+
                            "aNumber="+aNumber)
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
                    value: filler.currentIndex >= aNumber
                           ? aNumber : filler.currentIndex
                }
            }
            Item {
                anchors.fill: parent
                anchors.topMargin: 50
                width: 120

                SpinBox {
                    id: spinCount
                    width: 275
                    value: filler.currentIndex == aNumber
                           ? 1 : iNumber
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
                onClicked: {
                    dataModel.delShape(spinStart.value, spinCount.value)
                }
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
