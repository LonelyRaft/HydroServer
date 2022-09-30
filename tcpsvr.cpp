
#include "tcpsvr.h"
#include <qhostaddress.h>

TcpServer::TcpServer(
    const unsigned short port,
    const TcpServerType type,
    QObject *parent) : QObject(parent)
{
    mPort = port;
    mType = type;
    mServer = nullptr;
    mThread.start();
    moveToThread(&mThread);
}

TcpServer::~TcpServer()
{
    if (mServer)
        mServer->deleteLater();
    mThread.quit();
    mThread.wait();
}

void TcpServer::onStartServer()
{
    if (nullptr == mServer)
    {
        mServer = new QTcpServer;
        connect(mServer, &QTcpServer::newConnection,
                this, &TcpServer::onNewConnection);
    }
    if (!mServer->isListening() &&
        !mServer->listen(QHostAddress::AnyIPv4, mPort))
    {
        qDebug() << "listen failed";
    }
}

void TcpServer::onStopServer()
{
    if (nullptr == mServer)
        return;
    if (mServer->isListening())
    {
        mServer->close();
        emit delConnection();
    }
}

void TcpServer::onNewConnection()
{
    while (mServer->hasPendingConnections())
    {
        QTcpSocket *client = mServer->nextPendingConnection();
        connect(client, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
        connect(client, &QTcpSocket::disconnected, this, &TcpServer::onDisconnect);
        connect(client, &QTcpSocket::errorOccurred, this, &TcpServer::onErrorOccurr);
        connect(this, &TcpServer::delConnection, client, &QTcpSocket::disconnectFromHost);
        emit getConnection(client);
    }
}

void TcpServer::onReadyRead()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    QByteArray array = client->readAll();
    client->write(array);
}

void TcpServer::onDisconnect()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    if (nullptr == client)
        return;
    if (QAbstractSocket::UnconnectedState != client->state())
        client->abort();
}

void TcpServer::onErrorOccurr(QAbstractSocket::SocketError error)
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    qDebug() << error;
    if (nullptr == client)
        return;
}
