
#ifndef _HYDRO_MASTER_H
#define _HYDRO_MASTER_H

#include <qthread.h>
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qstring.h>

enum TcpServerType
{
    HydroASCII = 1,
    HydroBinary,
};

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(
        const unsigned short port,
        const TcpServerType type = HydroBinary,
        QObject *parent = nullptr);
    ~TcpServer();

public slots:
    void onStartServer();
    void onStopServer();
    void onNewConnection();
    void onReadyRead();
    void onDisconnect();
    void onErrorOccurr(QAbstractSocket::SocketError error);

signals:
    void getConnection(QTcpSocket *client);
    void delConnection();

private:
    QTcpServer *mServer;
    QThread mThread;
    TcpServerType mType;
    unsigned short mPort;
};

Q_DECLARE_METATYPE(QTcpSocket *)
Q_DECLARE_METATYPE(TcpServer *)

#endif // _HYDRO_MASTER_H
