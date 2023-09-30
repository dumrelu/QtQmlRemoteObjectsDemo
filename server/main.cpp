#include <QCoreApplication>
#include <QDebug>

#include "server_source.h"

int main(int argc, char *argv[])
{
    qDebug() << "Starting server...";

    QCoreApplication a(argc, argv);

    QRemoteObjectHost hostNode{ QUrl{ QStringLiteral("local:server") } };

    ServerSource server;
    hostNode.enableRemoting(&server);
    server.setMessage("Hello World!");

    qDebug() << "Server started.";

    return a.exec();
}
