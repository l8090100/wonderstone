#include "database.h"
#include <QDebug>


QSqlDatabase DataBase::db()
{
    return my_db;
}

void DataBase::connClose()
{
    QString name;
       {
           name = QSqlDatabase::database().connectionName();
       }//超出作用域，隐含对象QSqlDatabase::database()被删除。
       QSqlDatabase::removeDatabase(name);

}

bool DataBase::connOpen()
{
    if(QSqlDatabase::database().open()){
        QSqlDatabase::database().close();
    }
    my_db=QSqlDatabase::addDatabase("QSQLITE");
    my_db.setDatabaseName("D:/Users/l8090100/Documents/test.db");

    if(!my_db.open())
    {
        qDebug() << "faild open!!";
        return  false;
    }
    else
    {
        qDebug() << "success";
        return true;
    }
}
