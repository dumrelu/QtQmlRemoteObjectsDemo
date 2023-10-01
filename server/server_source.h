#pragma once

#include <QHash>

#include <memory>

#include "client_channel_source.h"
#include "rep_server_source.h"

class ServerSource : public ServerRemoteObjectSimpleSource
{
    Q_OBJECT
public:
    ServerSource(QRemoteObjectHost& host, QObject* parent = nullptr);

    QString createClientChannel(QString clientName) override;

private:
    QString clientChannelName(QString clientName) const;
    void clientDisconnected(ClientChannelSource* clientChannel);
    void computeVotingResults();

    QRemoteObjectHost& m_host;
    QHash<QString, std::shared_ptr<ClientChannelSource>> m_clientChannels;
    VotingChannelRemoteObjectSimpleSource m_votingChannel;
};