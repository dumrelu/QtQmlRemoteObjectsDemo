#include "server_source.h"

ServerSource::ServerSource(QRemoteObjectHost& host, QObject* parent)
    : ServerRemoteObjectSimpleSource{ parent }
    , m_host{ host }
{
    setVotingChannel(&m_votingChannel);

    m_votingChannel.setPrompt("Is this working?");
}

QString ServerSource::createClientChannel(QString clientName)
{
    const auto channelName = clientChannelName(clientName);

    if(m_clientChannels.contains(clientName))
    {
        //TODO: This should probably be an error. Need to check if the channel is actually used
        qWarning() << "Channel already exists for" << clientName;
        return "ERROR: Client already exists";
    }

    auto channel = std::make_shared<ClientChannelSource>();
    connect(channel.get(), &ClientChannelSource::clientDisconnected, this, &ServerSource::clientDisconnected);
    
    channel->setClientName(clientName);
    
    m_clientChannels.insert(clientName, channel);

    if(!m_host.enableRemoting(channel.get(), channelName))
    {
        qCritical() << "Failed to enable remoting for" << clientName;
        return "Failed to enable remoting for client channel" + channelName;
    }
    qDebug() << "Communication channel" << channelName << "created for" << clientName;
    return channelName;
}

QString ServerSource::clientChannelName(QString clientName) const
{
    return clientChannelPrefix() + clientName;
}

void ServerSource::clientDisconnected(ClientChannelSource *clientChannel)
{
    Q_ASSERT(clientChannel);
    
    qDebug() << "Client" << clientChannel->clientName() << "disconnected";
    m_clientChannels.remove(clientChannel->clientName());
}
