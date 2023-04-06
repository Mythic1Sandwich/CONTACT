#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QString>

class client : public QObject
{
    Q_OBJECT
public:
    explicit client(QObject * parent = nullptr, QTcpSocket *socket = nullptr);
    ~client();
    QTcpSocket *Socket;
public slots:
    void read();
    void onclosing();
signals:
    void send(QString);
    void close(client*);
};

#endif // CLIENT_H
