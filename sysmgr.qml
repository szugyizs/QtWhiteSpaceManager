/**
 * @package QTWhiteSpaceManager
 * @module sysmgr.qml
 * A button to shut the whole system down all at the same time.
 * ----------------------------
 * Updates
 * @date: 18/04/2019
 * @abstract: Added comments, indented code
 * @author:
 */

import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

Window {
    id:sysManager
    visible: true
    x: 1500
    y: 100
    title: qsTr("System Power Button")

    Button {
        id: powerBtn
        anchors.fill: parent
        text: "Shut down"
        onClicked: Qt.quit()
    }

}
