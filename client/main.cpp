#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <QSharedPointer>

#include "server_replica.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QRemoteObjectNode repNode;
    if(!repNode.connectToNode(QUrl{ QStringLiteral("local:server") }))
    {
        qFatal("Cannot connect to the server");
    }

    QSharedPointer<ServerReplica> server;
    server.reset(repNode.acquire<ServerReplica>());

    if(!server->waitForSource(1000))
    {
        qFatal("Cannot connect to the server");
    }
    qDebug() << "Message from server: " << server->message();

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url,&engine](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
