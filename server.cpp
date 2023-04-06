#include "server.h"
#include "parser.h"
#include "client.h"
#include <QDebug>
#include <QCoreApplication>

Server::Server(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &Server::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        server_status=1;
        qDebug() << "server is started";
    }
}

// функция подключения нового клиента
void Server::slotNewConnection(){
    if(server_status==1){
        QTcpSocket * soket = mTcpServer->nextPendingConnection();
        qDebug() << "new client connected: " << soket->peerAddress();
        client *clnt = new client(this, soket);
        connect(clnt, &client::send, this, &Server::slotMessage);
        connect(clnt, &client::close, this, &Server::slotRemove);
        clients << clnt;
        clnt->Socket->write("Welcome to the server!\r\n");
    }
}
// спам-рассылка всем подключённым пользователям
void Server::slotMessage(QString line){
    qDebug() << "Sending line: " << line;
    foreach(client * clnt, clients){
        clnt->Socket->write((line + "\r\n").toUtf8());
    }
}

// отключение пользователя
void Server::slotRemove(client* clnt){
    clnt->Socket->close();
    clients.remove(clients.indexOf(clnt));
    qDebug() << "-1 client :(";
}

Server::~Server(){
    foreach(client* clnt, clients){
        clnt->Socket->close();
    }
    server_status = 0;
}
