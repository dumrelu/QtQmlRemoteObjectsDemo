#include "client_channel_source.h"

#include "server_source.h"

ClientChannelSource::ClientChannelSource(QObject* parent)
    : ClientChannelRemoteObjectSimpleSource{ parent }
{
    m_timeout.setInterval(1000);
    m_timeout.start();
    connect(&m_timeout, &QTimer::timeout, 
        this, [this]()
        {
            if(!m_pongReceived)
            {
                emit clientDisconnected(this);
            }
            else
            {
                m_pongReceived = false;
                emit ping();
                m_timeout.start();
            }
        }
    );
}

void ClientChannelSource::pong()
{
    m_pongReceived = true;
    m_timeout.start();
}
