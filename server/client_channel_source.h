#pragma once

#include "rep_server_source.h"

class ServerSource;

class ClientChannelSource : public ClientChannelRemoteObjectSimpleSource
{
    Q_OBJECT
public:
    ClientChannelSource(QObject* parent = nullptr);
};
