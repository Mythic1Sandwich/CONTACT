#include "Server.h"
#include "functions.h"
#include <QDebug>

Server::~Server()
{
    TCPServer->close();
    server_status = 0;
}

Server::Server(QObject *parent) : QObject(parent)
{
    TCPServer = new QTcpServer(this);
    connect(TCPServer, &QTcpServer::newConnection,
            this, &Server::NewConnection);

    if(!TCPServer->listen(QHostAddress::Any, 33333))
    {
        qDebug() << "Error. Server is not started";
    } else {
        server_status = 1;
        qDebug() << "Server is started";
    }
}

void Server::NewConnection()
{
    if(server_status == 1)
    {
        qDebug() << "New client connected";
        QTcpSocket *Current_TCPSocket;
        Current_TCPSocket = TCPServer->nextPendingConnection();

        long long id = Current_TCPSocket->socketDescriptor();
        Current_TCPSocket->write("Your ID: ");
        Current_TCPSocket->write(QString::number(id).toUtf8());
        Current_TCPSocket->write("\r\n");
        Clients.insert(Current_TCPSocket,id);
        connect(Current_TCPSocket, &QTcpSocket::readyRead,
                this,&Server::ServerDataRead);
        connect(Current_TCPSocket,&QTcpSocket::disconnected,
                this,&Server::ClientDisconnected);
    }
}


void Server::ServerDataRead()
{
    QTcpSocket *Current_TCPSocket = (QTcpSocket*)sender();
    QByteArray data_output;
    QString data_input;
    while(Current_TCPSocket->bytesAvailable()>0)
    {
        data_input += Current_TCPSocket->readAll();
    }
    QString id = QString::number(Current_TCPSocket->socketDescriptor());
    data_output = parsing(data_input, id).toUtf8();
    Current_TCPSocket->write(data_output);
}

void Server::ClientDisconnected()
{
    QTcpSocket *Current_TCPSocket = (QTcpSocket*)sender();
    qDebug() << "Client disconnected";
    QString id = QString::number(Clients.value(Current_TCPSocket));
    close_session(id);
    Clients.remove(Current_TCPSocket);
    Current_TCPSocket->close();
}
