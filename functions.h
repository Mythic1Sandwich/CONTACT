#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "database.h"
#include "qrandom.h"

QString login(QString login, QString pass,QString id) //ВХОД
{
    QList<QString> query_list = {"SELECT * FROM signin WHERE login = :login and password = :password;",
                              ":login", login,
                              ":password", pass
                             };
    QString response = DataBase::Connect()->query_execute(query_list);

    if (response == "")
    {
        return "User not found\r\n";
    }
    else
    {
        query_list = {"UPDATE signin SET id = :id WHERE login = :login;",
                             ":login", login,
                             ":id", id
                            };

        DataBase::Connect()->query_execute(query_list);
        query_list = {"UPDATE stat SET id = :id WHERE login = :login;",
                             ":login", login,
                             ":id", id
                            };

        DataBase::Connect()->query_execute(query_list);

        return "auth+ok\r\n";
    }
}

QString registration(QString login, QString pass,QString surn, QString role,QString id) //РЕГИСТРАЦИЯ
{

    QList<QString> query_list = {"SELECT * FROM signin WHERE login = :login;",
                              ":login", login
                             };
    QString response = DataBase::Connect()->query_execute(query_list);


    if (response != "")
    {
        return "user is already exists\r\n";
    }

    if (role == "student")
    {
        query_list = {"INSERT INTO signin "
                      "(login, password,role,surname,id,task,stats)"
                      " VALUES (:login, :pass,:surn,'student',:id,0,0);",
                      ":login", login,
                      ":pass", pass,
                      ":surn", surn,
                      ":id",id
                     };
        DataBase::Connect()->query_execute(query_list);
      QList<QString> query_list1 = {"INSERT INTO stat VALUES (:surn,0,:id,0,:login);",":surn",surn,":id",id,":login",login

                             };
      QString response1 = DataBase::Connect()->query_execute(query_list1);
//
    }
    else if (role == "admin")
    {

        query_list = {"INSERT INTO signin "
                      "(login, password,role,surname)"
                      " VALUES (:login, :pass,:surn,'admin',:id,0,0);",
                      ":login", login,
                      ":pass", pass,
                      ":surn", surn,
                        ":id",id

                     };
        DataBase::Connect()->query_execute(query_list);

    }
    query_list = {"SELECT * FROM signin WHERE login = :login;",
                  ":login", login
                 };
    response = DataBase::Connect()->query_execute(query_list);

    if (response == "")
    {
        return "Attempt failed\r\n";
    }
    return "Attempt successful\r\n";
}
//}
bool check_answer(QString ans, int num)
{
    return true;
}
QString give_task(QString task_it,QString id){ //ФУНКЦИЯ  ВЫДАЕТ ЗАДАНИЯ

    QList<QString> query_list = {"SELECT * FROM signin WHERE id =:id;", ":id", id};
    QString response = DataBase::Connect()->query_execute(query_list);
    if (response == ""){
        return "NO FOUND";
    }
    else
    {
        QList<QString> query_list = {"SELECT * from signin WHERE (task = 0) and id= :id;", ":id", id
        };
        QString response = DataBase::Connect()->query_execute(query_list);
        if (response=="")
            qDebug()<<"YOU ALREADY HAVE 1 TASK";
        else {


            QList<QString> query_list1 = {"UPDATE signin SET task=:task_it WHERE id=:id;", ":id", id, ":task_it",task_it};
            response=DataBase::Connect()->query_execute(query_list1);
            QList<QString> query_list2 = {"UPDATE stat SET count=count+1 WHERE id=:id;", ":id", id};
            response=DataBase::Connect()->query_execute(query_list2);

        }

        return "GIVE "+response;
    }
}
bool check_task1(QString answer, QString ans)
{
    return (answer == ans);
}
QString check_task(QString id,QString answer)
{
    QString delta="";
    /*if(check_task1(variant,ans))
        delta = 1;
    else {

        delta = -1;
    }
*/
    QList<QString> query_list1 = {"SELECT task FROM signin WHERE id =:id;", ":id", id};
    QString task_id = DataBase::Connect()->query_execute(query_list1);
    qDebug()<<task_id;
   // check_task1(answer,ans) ? delta = "1": delta = "-1";
    int var= QRandomGenerator::global()->bounded(30);
    switch (task_id.toInt()){
    case 1:{

    }
    }

    if (task_id=="1;"){

    if (check_task1(answer,"2")){
        delta="1";
    }
    else
        delta="-1";
    }
    if (task_id=="2;"){

    if (check_task1(answer,"98")){
        delta="1";
    }
    else
        delta="-1";
    }
    if (task_id=="3;"){

    if (check_task1(answer,"4")){
        delta="1";
    }
    else
        delta="-1";
    }
    if (task_id=="4;"){

    if (check_task1(answer,"328")){
        delta="1";
    }
    else
        delta="-1";
    }
    /////////////////////////////////////////////////////
    QList<QString> query_list = {"UPDATE signin set stats=stats+:delta where id=:id;", ":id",id,":delta",delta};
    QString response = DataBase::Connect()->query_execute(query_list);

    QList<QString> query_list2 = {"UPDATE signin set task=0 where id=:id;", ":id",id};
    QString response2 = DataBase::Connect()->query_execute(query_list2);
    if (delta=="1"){
        QList<QString> query_list3 = {"UPDATE stat set stats=stats+:delta where id=:id;", ":id",id,":delta",delta};
        QString response3 = DataBase::Connect()->query_execute(query_list3);
        return "check +";

    }
    else{
        return "check -";
    }
}


void close_session(QString id)
{
    QList<QString> query_list = {"UPDATE signin SET id = NULL WHERE id = :id;",
                              ":id", id
                             };
    DataBase::Connect()->query_execute(query_list);
    QList<QString> query_list1 = {"UPDATE stat SET id = NULL WHERE id = :id;",
                              ":id", id
                             };
    DataBase::Connect()->query_execute(query_list1);
}

QString parsing(QString data, QString id)
{
    QString clear_data = data.left(data.lastIndexOf("\xd"));
    QList<QString> parametrs = clear_data.split("+");

    if(parametrs[0] == "auth" and parametrs.count() == 3)
    {
       return login(parametrs[1], parametrs[2],id);

    }
    else if(parametrs[0] == "reg" and parametrs.count() == 5)
    {
       return registration(parametrs[1], parametrs[2], parametrs[3],parametrs[4],id);
    }
    else if(parametrs[0] == "check" and parametrs.count() == 2)
    {
       return check_task(id,parametrs[1]);
    }

    else if(parametrs[0] == "give" and parametrs.count() == 2)
    {
       return give_task(parametrs[1],id);
    }
    else if(parametrs[0] == "logout" and parametrs.count() == 1)
    {
       close_session(id);
       return "logout+ok\r\n";
    }
    return "Error data parsing\r\n";
}

#endif // FUNCTIONS_H
