#include <QCoreApplication>
#include "Singleton.h"
#include "mydb.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyDB::createDB();
     //qDebug()<<MyDB::query_select();
      qDebug()<< MyDB::query("SELECT * FROM signin");


    return a.exec();
}
