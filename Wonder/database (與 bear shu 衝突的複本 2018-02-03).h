#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlTableModel>
#include <QtSql>


namespace Ui {
class DataBase;
}



class DataBase
{
public:
    QSqlDatabase mydb;
    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen()
    {
        mydb=QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("D:/Users/l8090100/Documents/test.db");

        if(!mydb.open())
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

public:


private slots:


private:

};




#endif // DATABASE_H
