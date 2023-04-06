#include "client.h"
#include "parser.h"

client::client(QObject *parent, QTcpSocket *socket) : QObject{parent}
{
    Socket = socket;
    connect(Socket, &QTcpSocket::readyRead, this, &client::read);
    connect(Socket, &QTcpSocket::disconnected, this, &client::onclosing);
}

// чтение сокета клиентом
void client::read(){
    while(Socket->bytesAvailable() > 0){
        QString line = Socket->readAll();
        qDebug() << line;
        emit send(parser::parse(line) + "\r\n");
    }
}

void client::onclosing(){ emit close(this); }

client::~client(){ Socket->close(); }
