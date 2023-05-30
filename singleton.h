#ifndef MyDB_H
#define MyDB_H
#include<QDebug>

class MyDB
{
    private:
        static MyDB * p_instance;
        static MyDBDestroyer destroyer;
    protected:
        MyDB(){qDebug()<<"MyDB()\n";}
        MyDB(const MyDB& ) = delete;
        MyDB& operator = (MyDB &) = delete;
        virtual ~MyDB() {}
        friend class MyDBDestroyer;
    public:
        static MyDB*Connect(){
            if (!p_instance)
            {
                p_instance = new MyDB();
                destroyer.initialize(p_instance);
            }
            return p_instance;
        }
};

MyDB* MyDB::p_instance;
MyDBDestroyer MyDB::destroyer;
#endif // MyDB_H
