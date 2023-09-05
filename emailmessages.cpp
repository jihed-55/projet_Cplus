#include "emailmessages.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QPdfWriter>
#include<QPainter>
#include <QVariant>
emailmessages::emailmessages()
{
    sender="";
    recipent="";
    message="";
    datee="";

}

 QString emailmessages::get_sender(){return sender;}
 QString emailmessages::get_recipent(){return recipent;}
 QString emailmessages::get_message(){return message;}
 QString emailmessages::get_datee(){return datee;}


 void emailmessages::setsender(QString sender){this->sender=sender;}
 void emailmessages::setrecipent(QString recipent){this->recipent=recipent;}
 void emailmessages::setmessage(QString message){this->message=message;}
 void emailmessages::setdatee(QString datee){this->datee=datee;}




 QSqlQueryModel * emailmessages::afficher()
 {
     QSqlQueryModel * model=new QSqlQueryModel () ;
     model->setQuery("select * from EMAILMESSAGES");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("SENDER"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("RECIPENT")); // setHeaderData taamel fi tableau
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("MESSAGE"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATEE"));

     return model;

 }




