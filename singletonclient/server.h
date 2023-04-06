#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "parser.h"
#include "client.h"
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();
public slots:
    void slotNewConnection();
    void slotMessage(QString);
    void slotRemove(client*);
private:
    QTcpServer * mTcpServer;
    QList<client*> clients;
    int server_status;
};
#endif // MYTCPSERVER_H







