#include "server_replica.h"


ServerReplica::~ServerReplica()
{
    if(m_clientChannel)
    {
        m_clientChannel->deleteLater();
        m_clientChannel = nullptr;
    }
}

QString ServerReplica::clientName() const
{
    return m_clientName;
}

ClientChannelRemoteObjectReplica* ServerReplica::clientChannel()
{
    connectSignals();

    if(state() != QRemoteObjectReplica::Valid)
    {
        qCritical() << "Server not connected";
        return nullptr;
    }

    if(!m_clientChannel)
    {
        //TODO: For some reason we can't block here...
        QMetaObject::invokeMethod(
            this, [this]()
            {
                auto channelNameReply = createClientChannel(m_clientName);
                if(!channelNameReply.waitForFinished(1000))
                {
                    qCritical() << "Failed to create client channel:" << channelNameReply.error();
                    return;
                }

                auto channelName = channelNameReply.returnValue();
                if(!channelName.startsWith(clientChannelPrefix()))
                {
                    qDebug() << "Got error from server when creating client channel:" << channelName;

                    //TODO: Probably invalid name
                    emit errorNameAlreadySet();
                    return;
                }

                m_clientChannel = node()->acquire<ClientChannelRemoteObjectReplica>(channelName);
                emit clientChannelChanged();
            }, 
            Qt::QueuedConnection
        );
    }

    return m_clientChannel;
}

void ServerReplica::setClientName(QString clientName)
{
    if(m_clientChannel)
    {
        qCritical() << "Channel was already created";
        return;
    }

    m_clientName = clientName;
    emit clientNameChanged();
    emit clientChannelChanged();
}

void ServerReplica::connectSignals()
{
    if(m_signalsConnected)
        return;

    // Need to reestablish the connection every time we reconnect to the server
    connect(this, &ServerReplica::stateChanged, 
        this, [this](QRemoteObjectReplica::State state)
        {
            if(state == QRemoteObjectReplica::Valid)
            {
                if(m_clientChannel)
                {
                    m_clientChannel->deleteLater();
                    m_clientChannel = nullptr;
                }
                emit clientChannelChanged();
            }
        }
    );
    m_signalsConnected = true;
}
