#include <QCoreApplication>
#include "singletonclient.h"
#include "server.h"
#include "parser.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
  Server server;
  SingletonClient::getInstance();
  SingletonClient::getInstance()->send_msg_to_server("hello");
   return a.exec();
}
