#pragma once

#include "rep_server_replica.h"

class ServerReplica : public ServerRemoteObjectReplica
{
    Q_OBJECT
public:
    using ServerRemoteObjectReplica::ServerRemoteObjectReplica;
};