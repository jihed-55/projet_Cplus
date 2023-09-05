#ifndef EMAILMESSAGES_H
#define EMAILMESSAGES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
class emailmessages
{

public :
    emailmessages();
    emailmessages(QString,QString,QString,QString);

    void setsender(QString);
    void setrecipent(QString);
    void setmessage(QString);
    void setdatee(QString);


    QString get_sender();
    QString get_recipent();
    QString get_message();
    QString get_datee();


    QSqlQueryModel * afficher();


private:
    QString sender,recipent,message,datee;

};



#endif //
