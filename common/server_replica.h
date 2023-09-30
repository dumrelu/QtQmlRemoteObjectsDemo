#pragma once

#include "rep_server_replica.h"

class ServerReplica : public ServerRemoteObjectReplica
{
    Q_OBJECT

    Q_PROPERTY(QString clientName READ clientName WRITE setClientName NOTIFY clientNameChanged)
    Q_PROPERTY(ClientChannelRemoteObjectReplica* clientChannel READ clientChannel NOTIFY clientChannelChanged)
public:
    using ServerRemoteObjectReplica::ServerRemoteObjectReplica;

    ~ServerReplica();

    QString clientName() const;
    ClientChannelRemoteObjectReplica* clientChannel();

    Q_INVOKABLE void foo() { clientChannel(); }

    void setClientName(QString clientName);

signals:
    void errorNameAlreadySet();
    void clientNameChanged();
    void clientChannelChanged();

private:
    void connectSignals();

    QString m_clientName;
    bool m_signalsConnected = false;
    ClientChannelRemoteObjectReplica* m_clientChannel = nullptr;
};