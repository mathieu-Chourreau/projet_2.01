#include <QSqlDatabase>
#include <QDebug>


#ifndef DATABASE_H
#define DATABASE_H

#define DATABASE_NAME "BD_Nodenot_SAE2_01"
#define CONNECT_TYPE "QODBC"

class Database
{
public:
    Database();
    bool openDataBase();
    void closeDataBase();
    void changerLesDiapos(unsigned int pRang, std::string pCategorie, std::string pTitre, std::string pChemin);



private:
    QSqlDatabase mybd;
    Database *db;
};



#endif // DATABASE_H
