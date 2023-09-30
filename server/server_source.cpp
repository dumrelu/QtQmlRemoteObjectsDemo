#include "server_source.h"

ServerSource::ServerSource(QObject* parent)
    : ServerRemoteObjectSimpleSource{ parent }
{
}

QString ServerSource::createClientChannel(QString clientName)
{
    //TODO: also need to implement a reverse heartbeat mechanism to remove dead clients
    //TODO: We could call this mechanism only when a client with the same name is requested
    Q_UNUSED(clientName);
    qCritical() << __PRETTY_FUNCTION__ << "not yet implemented";
    return tr("Method not yet implemented");
}
