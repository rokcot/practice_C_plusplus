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
    property bool iFlag: false
//    property double iRadius: 0.0
//    property double iHeight: 0.0
//    property double iWidth: 0.0
//    property double iA: 0.0
//    property double iB: 0.0
//    property double iC: 0.0

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
//                    onPressAndHold:
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
                                //dataModel.delShape(filler.currentIndex, iNumber)
                            }else if(aNumber != filler.currentIndex){
                                iNumber = filler.currentIndex
                                iNumber = (iNumber+1) - aNumber
                                //dataModel.delShape(aNumber, iNumber)
                            }else{
                                //dataModel.delShape(aNumber, 1)
                            }
                            delShapeDialog.open();
                        }
                    }
                    MenuItem {
                        text: "Edit"
                        onClicked: {
                            iFlag = true
                            switch (name)
                            {
                            case "circle":
//                                iRadius = model.data
                                addCircle.radius = model.data.radius
                                addCircle.open()
                                break
                            case "triangle":
//                                 dataModel.setShapeIndex(1)
//                                iA = model.data
//                                dataModel.setShapeIndex(2)
//                                iB = model.data
//                                dataModel.setShapeIndex(3)
//                                iC = model.data
                                addTriangle.rA = model.data.a
                                addTriangle.rB = model.data.b
                                addTriangle.rC = model.data.c
                                addTriangle.open()
                                break
                            case "rectangle":
//                                dataModel.setShapeIndex(1)
//                                iHeight = model.data
//                                dataModel.setShapeIndex(2)
//                                iWidth = model.data
                                addRectangle.rWidth = model.data.width
                                addRectangle.rHeight = model.data.height
                                addRectangle.open()
                                break
                            default:
                                return "black"
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
            ScrollBar.vertical: ScrollBar { }
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
                        iFlag = false
                        addCircle.radius = 0.1
                        addCircle.open()
                    }
                }
                MenuItem {
                    text: "Triangle"
                    onClicked: {
                        console.log("Triangle")
                        iFlag = false
                        addTriangle.rA = 0.1
                        addTriangle.rB = 0.1
                        addTriangle.rC = 0.1
                        addTriangle.open()
                    }
                }
                MenuItem {
                    text: "Rectangle"
                    onClicked: {
                        console.log("Rectangle")
                        iFlag = false
                        addRectangle.rWidth = 0.1
                        addRectangle.rHeight = 0.1
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

    AddCircleDialog {
        id: addCircle
        width: 300
        height: 200
        anchors.centerIn: parent
        radius: 0.0
        isEditing: iFlag
        onAccepted: {
            console.log("@@@@", addCircle.radius, addCircle.isEditing)
            iFlag ? dataModel.editShape(filler.currentIndex,"circle",
                                               addCircle.radius)
                         : dataModel.addCircle(addCircle.radius)
            filler.currentIndex = aNumber
        }
    }

    AddTriangleDialog {
        id: addTriangle
        width: 300
        height: 200
        anchors.centerIn: parent
        rA: 0.0
        rB: 0.0
        rC: 0.0
        isEditing: iFlag
        onAccepted: {
            iFlag ? dataModel.editShape(filler.currentIndex,"triangle",
                                               addTriangle.rA,
                                               addTriangle.rB,
                                               addTriangle.rC)
                         : dataModel.addTriangle(addTriangle.rA,
                                                 addTriangle.rB,
                                                 addTriangle.rC)
            filler.currentIndex = aNumber
        }
    }

    AddRectangleDialog {
        id: addRectangle
        width: 300
        height: 200
        anchors.centerIn: parent

        rHeight: 0.0
        rWidth: 0.0

        isEditing: iFlag

        onAccepted: {
            iFlag ? dataModel.editShape(filler.currentIndex,"rectangle",
                                        addRectangle.rHeight,
                                        addRectangle.rWidth)
                  : dataModel.addRectangle(addRectangle.rHeight,
                                           addRectangle.rWidth)
            filler.currentIndex = aNumber
        }
    }

}
