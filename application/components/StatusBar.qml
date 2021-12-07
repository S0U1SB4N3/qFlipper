import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.impl 2.15

import Theme 1.0

Rectangle {
    id: control

    property var deviceState

    color: (deviceState && deviceState.isError) ? Theme.color.darkred2 : Theme.color.darkorange1

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 10
        spacing: 10

        IconImage {
            color: message.color
            sourceSize: Qt.size(22, 22)
            source: "qrc:/assets/gfx/symbolic/info-small.svg"
            rotation: deviceState && deviceState.isError ? 180 : 0
        }

        TextLabel {
            id: message
            text: !deviceState ? qsTr("Waiting for devices ...") :
                   deviceState.isError ? qsTr("Something went wrong. Check logs for details.") :
                   deviceState.isPersistent? qsTr("Do not unplug the device ...") : qsTr("Ready.")

            color: (deviceState && deviceState.isError) ? Theme.color.lightred1 : Theme.color.lightorange2

            verticalAlignment: Text.AlignVCenter
            Layout.fillWidth: true
        }
    }
}