#include <QCoreApplication>
#include <QDebug>

#include "server_source.h"

int main(int argc, char *argv[])
{
    qDebug() << "Starting server...";

    QCoreApplication a(argc, argv);

    QRemoteObjectRegistryHost regNode(QUrl(QStringLiteral("local:registry")));
    QRemoteObjectHost hostNode(QUrl(QStringLiteral("local:replica")), QUrl(QStringLiteral("local:registry")));

    ServerSource server;
    hostNode.enableRemoting(&server);

    qDebug() << "Server started.";

    return a.exec();
}
