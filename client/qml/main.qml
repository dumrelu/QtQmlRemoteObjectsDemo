import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtRemoteObjects

import custom

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Client Window")

    ServerReplica {
        id: server

        node: Node { registryUrl: "local:registry" }
        clientName: "myClient1"

        onErrorNameAlreadySet: () => {
            console.log("Client name already set");
        }
    }

    Label {
        anchors.centerIn: parent
        text: "Server replica state: " + server.state + ", channel: " + server.clientChannel
    }
}