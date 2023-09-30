#pragma once

#include "rep_server_source.h"

class ServerSource : public ServerRemoteObjectSimpleSource
{
    Q_OBJECT
public:
    ServerSource(QObject* parent = nullptr);

    QString createClientChannel(QString clientName) override;
};