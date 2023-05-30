#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QMap>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();
public slots:
    void NewConnection();
    void ClientDisconnected();
    void ServerDataRead();
private:
    QTcpServer *TCPServer;
    QMap<QTcpSocket*, long long> Clients;
    int server_status;
};

#endif // SERVER_H
