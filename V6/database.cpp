#include "database.h"
#include <QDebug>

Database::Database()
{

}

bool Database::openDataBase()
{
    mybd =  QSqlDatabase::addDatabase(CONNECT_TYPE);
    mybd.setDatabaseName(DATABASE_NAME);
    return (mybd.open());
}

void Database::closeDataBase()
{
    mybd.close();
}
