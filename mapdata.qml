import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.0
import QtPositioning 5.5
import QtLocation 5.6

Window {
    width: 700
    height: 700
    visible: true
    title: qsTr("Map of devices in TVWS")

    Map {
        id: theMap
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
            id: miv1
            model:TVModel1
            delegate: MapCircle{
                id: mc1
                center: position
                radius: 9656
                color: 'green'
                opacity: 0.5
                border.width: 1

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        popup1.open()
                    }
                }

                Popup {
                    id: popup1
                    padding: 10
                    contentItem: Text {
                        text: "Transmitter " + id + " at " + position
                    }
                    parent: mc1
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

        MapItemView {
            id: miv1m
            model:TVModel1
            delegate: MapQuickItem {
                id: marker1
                anchorPoint.x: markerImg1.width/2
                anchorPoint.y: markerImg1.height
                coordinate: position

                sourceItem: Image {
                    id: markerImg1
                    source: "qrc:marker1.png"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        popup1a.open()
                    }
                }

                Popup {
                    id: popup1a
                    padding: 10
                    contentItem: Text {
                        text: "Transmitter " + id + " at " + position
                    }
                    parent: marker1
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
            anchors.left: parent.left
            text: "Load transmitters"
            onClicked: {
                //TVModel1.removeItems? some clear function
                TVModel1.readFromCSV("C:\\Users\\Zsuzsi\\Desktop\\arqiva_transmitters_final.csv")
            }
//            FileDialog {
//                id: fileDialog
//                title: "Please choose a file"
//                folder: shortcuts.home
//                onAccepted: {
//                    console.log("You chose: " + fileDialog.fileUrls)
//                    Qt.quit()
//                }
//                onRejected: {
//                    console.log("Canceled")
//                    Qt.quit()
//                }
//                Component.onCompleted: visible = true
//            }
        }

        MapItemView {
            id: miv2
            model:TVModel2
            delegate: MapCircle{
                id: mc2
                center: position
                radius: 804
                color: 'red'
                opacity: 0.5
                border.width: 1

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        popup2.open()
                    }
                }

                Popup {
                    id: popup2
                    padding: 10
                    contentItem: Text {
                        text: "User " + id + " at " + position
                    }
                    parent: mc2
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

        MapItemView {
            id: miv2a
            model:TVModel2
            delegate: MapQuickItem {
                id: marker2
                anchorPoint.x: markerImg2.width/2
                anchorPoint.y: markerImg2.height
                coordinate: position

                sourceItem: Image {
                    id: markerImg2
                    source: "qrc:marker2.png"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        popup2a.open()
                    }
                }

                Popup {
                    id: popup2a
                    padding: 10
                    contentItem: Text {
                        text: "User " + id + " at " + position
                    }
                    parent: marker2
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
            id: userBtn
            height:50
            width: 100
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            text: "Load users"
            onClicked: {
                //some clear function
                TVModel2.readFromCSV("C:\\Users\\Zsuzsi\\Desktop\\testusers.csv")
            }
        }
    }
}
