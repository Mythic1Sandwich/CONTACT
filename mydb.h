#ifndef Mydb
#define Mydb

#include <QCoreApplication>
#include <vector>
#include <QString>
#include <QVariant>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include "Singleton.h"

class MyDB : public Singleton
{
private:
    MyDB() = delete;
    MyDB(const MyDB &Db) = delete;
    static QSqlDatabase db;

    static void openDB(){
        qDebug()<<"MyDB()\n";
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("C:\\sqlite\\db.db");
        if(!db.open())
            qDebug()<<db.lastError().text();
    }
public:
   static QString query (QString q){
                QSqlQuery query_obj(db);
                query_obj.exec(q);
                QString res="";
                while (query_obj.next()){
                    std::vector<QString> qwert;
                    QString login = query_obj.value("login").toString();
                    QString password = query_obj.value("password").toString();
                    qwert.push_back(login);
                    qwert.push_back(password);
                    qDebug()<<login <<" " << password<<"\n";

                }
                return res;
            }


    static void createDB(){
        Singleton::getInstance();
        if (!db.isOpen())
        {
            openDB();
        }

    }
    static void close(){
        if(db.isOpen())
            db.close();
    }
};
QSqlDatabase MyDB::db;

#endif
