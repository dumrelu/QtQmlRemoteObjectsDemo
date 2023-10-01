#pragma once

#include <QHash>

#include <memory>

#include "rep_server_source.h"

class ServerSource : public ServerRemoteObjectSimpleSource
{
    Q_OBJECT
public:
    ServerSource(QRemoteObjectHost& host, QObject* parent = nullptr);

    QString createClientChannel(QString clientName) override;

private:
    QString clientChannelName(QString clientName) const;

    QRemoteObjectHost& m_host;
    QHash<QString, std::shared_ptr<ClientChannelRemoteObjectSimpleSource>> m_clientChannels;
};