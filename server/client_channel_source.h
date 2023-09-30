#pragma once

#include "rep_server_source.h"

class ClientChannel : public ClientChannelRemoteObjectSimpleSource
{
    Q_OBJECT
public:
    ClientChannel(QObject* parent = nullptr);
};