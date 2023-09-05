#include "student.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QPdfWriter>
#include<QPainter>
#include <QVariant>
student::student()
{
    id="";
    nom="";
    prenom="";
    mail="";
    origine="";

}

 QString student::get_id(){return id;}
 QString student::get_nom(){return nom;}
 QString student::get_prenom(){return prenom;}
 QString student::get_mail(){return mail;}
 QString student::get_origine(){return origine;}


 void student::setid(QString id){this->id=id;}
 void student::setnom(QString nom){this->nom=nom;}
 void student::setprenom(QString prenom){this->prenom=prenom;}
 void student::setmail(QString mail){this->mail=mail;}
 void student::setorigine(QString origine){this->origine=origine;}


 bool student::ajouter()
 {
     QSqlQuery query;



           query.prepare("insert into STUDENT (ID, NOM, PRENOM, MAIL , ORIGINE) "
                         "values (:id, :nom, :prenom, :mail , :origine)");
           query.bindValue(":id", id);
           query.bindValue(":nom", nom);
           query.bindValue(":prenom", prenom);
           query.bindValue(":mail", mail);
           query.bindValue(":origine", origine);

           return query.exec();
 }
 bool student::supprimer(int id)
 {
     QSqlQuery query;
     QString res=QString::number(id);
     query.prepare("delete from STUDENT where ID= :id");
     query.bindValue(":id",res);
     return query.exec();
 }
 QSqlQueryModel * student::afficher()
 {
     QSqlQueryModel * model=new QSqlQueryModel () ;
     model->setQuery("select * from STUDENT");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("MAIL"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("ORIGINE"));

     return model;

 }
 bool student::modifier(int id)
 {
     QSqlQuery query;
     QString res = QString::number(id);

     query.prepare("update STUDENT set ORIGINE=:origine, NOM=:nom, MAIL=:mail , PRENOM=:prenom where ID=:id");
     query.bindValue(":id", res);
     query.bindValue(":nom", nom);
     query.bindValue(":prenom", prenom);
     query.bindValue(":mail", mail);
     query.bindValue(":origine", origine);

     return query.exec();

 }
 QSqlQueryModel *student::trieid()
 {
     QSqlQueryModel *model = new QSqlQueryModel();
     model->setQuery("SELECT * FROM STUDENT ORDER BY CAST(ID AS INTEGER)");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("ORIGINE"));

     return model;
 }

 QSqlQueryModel * student::trienom()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM STUDENT ORDER BY NOM");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("MAIL"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("ORIGINE"));



     return model;
 }
 QSqlQueryModel * student::trieprenom()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM STUDENT ORDER BY PRENOM");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("MAIL"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("ORIGINE"));


     return model;
 }

 void  student::telechargerPDF(){

                      QPdfWriter pdf("C:/Users/User/OneDrive/Desktop/export pdf/PDF.pdf");



                      QPainter painter(&pdf);
                     int i = 4000;



                          painter.setPen(Qt::blue);
                           painter.setFont(QFont("Century Gothic",35,QFont::Bold));
                          painter.drawText(2000,1500,"LIST OF STUDENTS");
                          painter.setPen(Qt::black);
                          painter.drawRect(0,2700,6500,500);
                          painter.setFont(QFont("Calibri",14,QFont::Bold));
                          painter.drawText(200,3000,"id");
                          painter.drawText(1800,3000,"nom");
                          painter.drawText(3100,3000,"prenom");
                          painter.drawText(4200,3000,"mail");
                          painter.drawText(5500,3000,"origine");

                          QSqlQuery query;

                          query.prepare("select * from STUDENT");
                          query.exec();
                          while (query.next())
                          {
                                 painter.setFont(QFont("Calibri",13));
                              painter.drawText(200,i,query.value(0).toString());
                              painter.drawText(1800,i,query.value(1).toString());
                              painter.drawText(3200,i,query.value(2).toString());
                              painter.drawText(4200,i,query.value(3).toString());
                              painter.drawText(5500,i,query.value(4).toString());



                             i = i + 500;
                          }}

