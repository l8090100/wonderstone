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
    QSqlDatabase db();
    QSqlDatabase my_db;
    void connClose();
    bool connOpen();

private slots:


};




#endif // DATABASE_H
