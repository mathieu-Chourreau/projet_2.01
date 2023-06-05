#include "database.h"
#include <QDebug>

Database::Database()
{

}

bool Database::openDataBase()
{
    qDebug() << "ouverture de la bd" << Qt::endl;
    mybd =  QSqlDatabase::addDatabase(CONNECT_TYPE);
    mybd.setDatabaseName(DATABASE_NAME);
    return (mybd.open());
}

void Database::closeDataBase()
{
    mybd.close();
    qDebug() << "fermeture bd" << Qt::endl;
}
