import QtQuick 2.0
import QtPositioning 5.6
import QtLocation 5.6

Item {

    property variant topLeftView: QtPositioning.coordinate(56.542533, -7.362202)
    property variant bottomRightView: QtPositioning.coordinate(55.102085, -2.241001)
    property variant viewSpace: QtPositioning.rectangle(topLeftView, bottomRightView)

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(55.8642, -4.2518)
        zoomLevel: 15
        visibleRegion: viewSpace
    }
}

