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
    property int indexSelectionFirst: 0
    property int indexSelectionLast: 0
    property bool iFlag: false

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
                color: ((index <= filler.currentIndex) && (index >= indexSelectionFirst)) ||
                       ((index >= filler.currentIndex) && (index <= indexSelectionFirst))
                       ? "#800000" : "black"

                MouseArea {
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    anchors.fill: parent
//                  onPressAndHold:
                    onClicked: {
                        switch (mouse.button)
                        {
                        case Qt.RightButton:
                            delObject.open()
                            break;
                        case Qt.LeftButton:
                            if(mouse.modifiers === Qt.ControlModifier){
                                indexSelectionFirst = filler.currentIndex
                            }else{
                                indexSelectionFirst = model.index
                            }
                            filler.currentIndex = model.index
                            console.log(filler.currentIndex, " - ",
                                        index, indexSelectionFirst)
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
                            if(indexSelectionFirst > filler.currentIndex){
                                indexSelectionLast = filler.currentIndex
                                indexSelectionLast = (indexSelectionFirst+1) - indexSelectionLast
                                //dataModel.delShape(filler.currentIndex, iNumber)
                            }else if(indexSelectionFirst != filler.currentIndex){
                                indexSelectionLast = filler.currentIndex
                                indexSelectionLast = (indexSelectionLast+1) - indexSelectionFirst
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
                                addCircle.radius = model.data.radius
                                addCircle.open()
                                break
                            case "triangle":
                                addTriangle.rA = model.data.a
                                addTriangle.rB = model.data.b
                                addTriangle.rC = model.data.c
                                addTriangle.open()
                                break
                            case "rectangle":
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
                if(indexSelectionFirst > filler.currentIndex){
                    indexSelectionLast = filler.currentIndex
                    indexSelectionLast = (indexSelectionFirst+1) - indexSelectionLast
                }else if(indexSelectionFirst != filler.currentIndex){
                    indexSelectionLast = filler.currentIndex
                    indexSelectionLast = (indexSelectionLast+1) - indexSelectionFirst
                }
                console.log("iNumber="+indexSelectionLast+" filler="+filler.currentIndex+
                            "aNumber="+indexSelectionFirst)
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

    DelShapeDialog {
        id: delShapeDialog
        width: 300
        height: 200
        anchors.centerIn: parent
        indexFirst: filler.currentIndex >= indexSelectionFirst
                    ? indexSelectionFirst : filler.currentIndex
        indexLast: filler.currentIndex == indexSelectionFirst
                   ? 1 : indexSelectionLast
        onAccepted: dataModel.delShape(delShapeDialog.indexFirst,
                                       delShapeDialog.indexLast)
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
            isEditing ? dataModel.editShape(filler.currentIndex,"circle",
                                               addCircle.radius)
                         : dataModel.addCircle(addCircle.radius)
            filler.currentIndex = indexSelectionFirst
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
            isEditing ? dataModel.editShape(filler.currentIndex,"triangle",
                                               addTriangle.rA,
                                               addTriangle.rB,
                                               addTriangle.rC)
                         : dataModel.addTriangle(addTriangle.rA,
                                                 addTriangle.rB,
                                                 addTriangle.rC)
            filler.currentIndex = indexSelectionFirst
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
            isEditing ? dataModel.editShape(filler.currentIndex,"rectangle",
                                        addRectangle.rHeight,
                                        addRectangle.rWidth)
                  : dataModel.addRectangle(addRectangle.rHeight,
                                           addRectangle.rWidth)
            filler.currentIndex = indexSelectionFirst
        }
    }

}
