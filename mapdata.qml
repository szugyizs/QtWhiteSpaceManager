import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
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
                            text: "Transmitter " + id + " at " + position
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
                anchors.left: parent.left
                text: "Load transmitters"
                onClicked: {
                    TVModel1.readFromCSV("C:\\Users\\Zsuzsi\\Desktop\\arqiva_transmitters_final.csv")
                }
            }
        }

        MapItemView {
            id: miv2
            model:TVModel2
            delegate: MapCircle{
                center: position
                radius: 1000
                color: 'red'
                opacity: 0.5
                border.width: 1

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        popup2.open()
                    }

                    Popup {
                        id: popup2
                        padding: 10
                        contentItem: Text {
                            text: "User " + id + " at " + position
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
                id: userBtn
                height:50
                width: 100
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                text: "Load users"
                onClicked: {
                    TVModel2.readFromCSV("C:\\Users\\Zsuzsi\\Desktop\\testusers.csv")
                }
            }

        }

    }


}
