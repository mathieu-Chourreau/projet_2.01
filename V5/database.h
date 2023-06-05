#include <QSqlDatabase>
#include <QDebug>


#ifndef DATABASE_H
#define DATABASE_H

#define DATABASE_NAME "SAE1"
#define CONNECT_TYPE "QODBC"

class Database
{
public:
    Database();
    bool openDataBase();
    void closeDataBase();

private:
    QSqlDatabase mybd;
    Database *db;
};



#endif // DATABASE_H
