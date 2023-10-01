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
                when: server.state === ServerReplica.Valid && !!server.clientChannel && server.votingChannel.prompt.length === 0
                PropertyChanges {
                    target: contentLoader
                    sourceComponent: connectedToServerComponent
                }
            }, 
            State {
                name: "voting"
                when: server.state === ServerReplica.Valid && !!server.clientChannel && server.votingChannel.prompt.length > 0
                PropertyChanges {
                    target: contentLoader
                    sourceComponent: votingComponent
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
                    focus: true
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
                    text: qsTr("Connected to server as: %1. Waiting for a vote...").arg(server.clientName)
                }
            }
        }
    }

    Component {
        id: votingComponent

        Item {
            Label {
                anchors.right: parent.right
                text: qsTr("Username: %1").arg(server.clientName)
            }

            ColumnLayout {
                anchors.centerIn: parent

                Label {
                    text: server.votingChannel.prompt
                    font.pixelSize: Qt.application.font.pixelSize * 2
                    font.bold: true
                }

                RowLayout {
                    Layout.alignment: Qt.AlignHCenter
                    Button {
                        id: yesButton

                        text: "Yes"
                        highlighted: server.clientChannel.voteSelection.length > 0
                        visible: server.clientChannel.voteSelection.length === 0 || server.clientChannel.voteSelection === yesButton.text

                        onClicked: () => {
                            if(server.clientChannel.voteSelection.length === 0)
                            {
                                server.clientChannel.pushVoteSelection(yesButton.text);
                            }
                            else
                            {
                                server.clientChannel.pushVoteSelection("");
                            }
                        }
                    }

                    Button {
                        id: noButton

                        text: "No"
                        highlighted: server.clientChannel.voteSelection.length > 0
                        visible: server.clientChannel.voteSelection.length === 0 || server.clientChannel.voteSelection === noButton.text

                        onClicked: () => {
                            if(server.clientChannel.voteSelection.length === 0)
                            {
                                server.clientChannel.pushVoteSelection(noButton.text);
                            }
                            else
                            {
                                server.clientChannel.pushVoteSelection("");
                            }
                        }
                    }
                }

                Label {
                    text: qsTr("Votes: %1% yes, %2% no, %3% abstain").arg(server.votingChannel.percentageOfYesVotes * 100.0).arg(server.votingChannel.percentageOfNoVotes * 100.0).arg( (1.0 - server.votingChannel.percentageOfYesVotes - server.votingChannel.percentageOfNoVotes) * 100.0)
                    font.pixelSize: Qt.application.font.pixelSize * 2
                    font.bold: true
                }
            }
        }
    }
}