#pragma once

#include <QTimer>

#include "rep_server_source.h"

class ServerSource;

class ClientChannelSource : public ClientChannelRemoteObjectSimpleSource
{
    Q_OBJECT
public:
    ClientChannelSource(QObject* parent = nullptr);

    void pong() override;

signals:
    void clientDisconnected(ClientChannelSource* clientChannel);

private:
    QTimer m_timeout;
    bool m_pongReceived = false;
};
