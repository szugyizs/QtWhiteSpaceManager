import QtQuick 2.6
import QtQuick.Window 2.2
import QtPositioning 5.5
import QtLocation 5.6

Window {
    width: 700
    height: 500
    visible: true
    title: qsTr("Test ")

    property variant topLeftEurope: QtPositioning.coordinate(56.542533, -7.362202)
    property variant bottomRightEurope: QtPositioning.coordinate(55.102085, -2.241001)
    property variant viewOfEurope:
        QtPositioning.rectangle(topLeftEurope, bottomRightEurope)

    Map {
        id: mapOfEurope
        anchors.centerIn: parent;
        anchors.fill: parent
        plugin: Plugin {
            name: "osm"
        }
        MapItemView {
            model: navaidsModel
            delegate: MapCircle{
                center: position
                radius: 5000
                color: 'green'
                border.width: 3
                MouseArea {
                    anchors.fill: parent
                    onDoubleClicked: {
                        console.log("Doubleclick on " + oaci)
                    }
                    onClicked: {
                        console.log("Point : " + oaci + " " + position + " " + country)
                    }
                }
            }
        }
        visibleRegion: viewOfEurope
    }
}
