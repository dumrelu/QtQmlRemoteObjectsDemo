import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
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

        onErrorNameAlreadySet: () => {
            console.log("Client name already set");
        }
    }

    Loader {
        id: contentLoader
        anchors.fill: parent

        states: [
            State {
                name: "serverNotConnected"
                when: server.state !== ServerReplica.Valid
                PropertyChanges {
                    target: contentLoader
                    sourceComponent: serverNotConnectedComponent
                }
            }, 
            State {
                name: "loginToServer"
                when: server.state === ServerReplica.Valid && !server.clientChannel
                PropertyChanges {
                    target: contentLoader
                    sourceComponent: loginToServerComponent
                }
            }, 
            State {
                name: "connectedToServer"
                when: server.state === ServerReplica.Valid && !!server.clientChannel
                PropertyChanges {
                    target: contentLoader
                    sourceComponent: connectedToServerComponent
                }
            }
        ]   
    }

    Component {
        id: serverNotConnectedComponent
        Item {
            RowLayout {
                anchors.centerIn: parent
                
                Label {
                    text: qsTr("Connecting to server...")
                }

                BusyIndicator {
                    running: true
                }
            }
        }
    }

    Component {
        id: loginToServerComponent
        Item {
            RowLayout {
                anchors.centerIn: parent

                Label {
                    text: qsTr("Username:")
                }

                TextField {
                    id: userField
                    validator: RegularExpressionValidator { regularExpression: /[0-9a-zA-Z_]+/ }
                    onAccepted: () => {
                        console.log("Using username:", userField.text);
                        server.clientName = userField.text;
                    }
                }
            }
        }
    }

    Component {
        id: connectedToServerComponent

        Item {
            ColumnLayout {
                anchors.centerIn: parent

                Label {
                    text: qsTr("Connected to server as: %1").arg(server.clientName)
                }
            }
        }
    }
}