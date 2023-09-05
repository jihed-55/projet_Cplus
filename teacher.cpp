#include "teacher.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QPdfWriter>
#include<QPainter>
#include<QSqlTableModel>
teacher::teacher()
{
    cin="";
    name="";
    age="";
    mail="";
}

 QString teacher::get_cin(){return cin;}
 QString teacher::get_name(){return name;}
 QString teacher::get_age(){return age;} // get deja ta5ou il variable il mawjoud awtist3mlha
 QString teacher::get_mail(){return mail;}


 void teacher::setcin(QString cin){this->cin=cin;}
 void teacher::setname(QString name){this->name=name;}
 void teacher::setage(QString age){this->age=age;}
 void teacher::setmail(QString mail){this->mail=mail;}

 bool teacher::ajouter()
 {
     QSqlQuery query; // QSqlQuery tammel interrection maa basede donnee



           query.prepare("insert into TEACHER (CIN, NAME,AGE , MAIL) "
                         "values (:cin, :name, :age, :mail)");
           query.bindValue(":cin", cin);
           query.bindValue(":name", name);
           query.bindValue(":age", age);
           query.bindValue(":mail", mail);

           return query.exec();
 }
 bool teacher::supprimer(int cin)
 {
     QSqlQuery query;
     QString res=QString::number(cin);
     query.prepare("delete from TEACHER where CIN= :cin");
     query.bindValue(":cin",res);
     return query.exec();

 }
 QSqlQueryModel * teacher::afficher()
 {
     QSqlQueryModel * model=new QSqlQueryModel () ;
     model->setQuery("select * from TEACHER");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("NAME"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("AGE"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("MAIL"));

     return model;

 }
 bool teacher::modifier(int cin)
 {
     QSqlQuery query;
     QString res = QString::number(cin);

     query.prepare("update TEACHER set NAME=:name,MAIL=:mail, AGE=:age where CIN=:cin");
     query.bindValue(":cin", res);
     query.bindValue(":name", name);
     query.bindValue(":age", age);
     query.bindValue(":mail", mail);

     return query.exec();

 }
 QSqlQueryModel * teacher::triecin()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM TEACHER ORDER BY CIN");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("NAME"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("AGE"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("MAIL"));

     return model;
 }
 QSqlQueryModel * teacher::triename()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM TEACHER ORDER BY NAME");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("NAME"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("AGE"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("MAIL"));


     return model;
 }
 QSqlQueryModel * teacher::trieage()
 {
     QSqlQueryModel * model=new QSqlQueryModel();
     model->setQuery("SELECT * FROM TEACHER ORDER BY AGE");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("NAME"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("AGE"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("MAIL"));

     return model;
 }
 void teacher::recherche(QTableView *tableView, int cin)
 {
     // Assuming you have a QSqlTableModel named model
     QSqlTableModel *model = new QSqlTableModel;
     model->setTable("TEACHER");


     // Apply search filter based on ID
     QString filter = QString("CIN = %1").arg(cin);
     model->setFilter(filter);

     model->select();

     // Set the model to the table view
     tableView->setModel(model);
 }
 void  teacher::telechargerPDF(){

                      QPdfWriter pdf("C:/Users/User/OneDrive/Desktop/export pdf/PDF.pdf");



                      QPainter painter(&pdf);
                     int i = 4000;



                          painter.setPen(Qt::blue);
                           painter.setFont(QFont("Century Gothic",35,QFont::Bold));
                          painter.drawText(2000,1500,"LIST OF TEACHER");
                          painter.setPen(Qt::black);
                          painter.drawRect(0,2700,6500,500);
                          painter.setFont(QFont("Calibri",14,QFont::Bold));
                          painter.drawText(200,3000,"cin");
                          painter.drawText(1800,3000,"name");
                          painter.drawText(3100,3000,"age");
                          painter.drawText(4200,3000,"mail");



                          QSqlQuery query;

                          query.prepare("select * from TEACHER");
                          query.exec();
                          while (query.next())
                          {
                                 painter.setFont(QFont("Calibri",13));
                              painter.drawText(200,i,query.value(0).toString());
                              painter.drawText(1800,i,query.value(1).toString());
                              painter.drawText(3200,i,query.value(2).toString());
                              painter.drawText(4200,i,query.value(3).toString());



                             i = i + 500;
                          }}

