#include "connection.h"
#include "teacher.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("4735");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
