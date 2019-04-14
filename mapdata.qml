import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtPositioning 5.5
import QtLocation 5.6
import NavModel 1.0

Window {
    width: 700
    height: 500
    visible: true
    title: qsTr("Map of devices in TVWS")



    Map {
        id: mapOfEurope
        anchors.centerIn: parent;
        anchors.fill: parent
        plugin: Plugin {
            name: "osm"
        }

        center {
            latitude: 55.8642
            longitude: -4.2518
        }
        zoomLevel: 10

        MapItemView {
            id: miv
            NavModel{
                id: model
            }

            model: model
            //model: navModel
            delegate: MapCircle{
                center: position
                radius: 5000
                color: 'green'
                opacity: 0.5
                border.width: 1

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        popup.open()
                    }

                    Popup {
                        id: popup
                        padding: 10
                        contentItem: Text {
                            text: "Point : " + oaci + " " + position + " " + country
                        }
                        parent: MapCircle
                        x: Math.round((parent.width - width) / 2)
                        y: Math.round((parent.height - height) / 2)

                        width: 350
                        height: 50
                        modal: true
                        focus: true
                        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                    }
                }
            }

            Button {
                id: tmitBtn
                height:50
                width: 100
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                text: "Load transmitters"
                onClicked: {
                    model.readFromCSV("cctv1.csv")
                    miv.dataModelChanged()
                }
            }
            Button {
                id: userBtn
                height:50
                width: 100
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                text: "Load users"
            }
        }
    }


}



////import QtQuick 2.0
////import QtQuick.Controls 1.4
////import QtQuick.Controls.Styles 1.4
////import QtPositioning 5.6
////import QtLocation 5.6

//import QtQuick 2.6
////import QtQuick.Window 2.2
//import QtQuick.Controls 1.4
//import QtQuick.Controls.Styles 1.4
//import QtPositioning 5.5
//import QtLocation 5.6

//Row{
//Rectangle {

//    anchors.fill: parent
//    visible: true

//    Map {

//        plugin: Plugin {
//            id: mapPlugin
//            name: "osm"
//        }

//        anchors.fill: parent
//        center: QtPositioning.coordinate(55.8642, -4.2518)
//        zoomLevel: 10
//        MapItemView{
//            model: myModel
////            delegate: MapCircle{
////                center{
////                    latitude: 55.8642
////                    longitude: -4.2518
////                }
////                radius: 5000
////                color: 'green'
////                border.width: 3
////                MouseArea {
////                    anchors.fill: parent
////                    onDoubleClicked: {
////                        console.log("Doubleclick on " + oaci)
////                    }
////                    onClicked: {
////                        console.log("Point : " + oaci + " " + position + " " + country)
////                    }
////                }
////            }

//        }
//    }


////    Button {
////        id: blueBtn
////        height:50
////        width: 100
////        anchors.bottom: parent.bottom
////        anchors.right: parent.right

////        text: "Button"
////        style: ButtonStyle {
////            background: Rectangle {
////                implicitWidth: 100
////                implicitHeight: 25
////                color: "blue"
////                opacity: 0.5
////            }
////        }
////    }

//}


//}



