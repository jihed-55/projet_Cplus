#ifndef TEACHER_H
#define TEACHER_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
class teacher
{

public :
    teacher();
    teacher(QString,QString,QString,QString);

    void setcin(QString);
    void setname(QString);
    void setage(QString);
    void setmail(QString);      //void fonction metraja3 chey taamel feha appel wela fonction aadin


    QString get_cin();           // fonction traja3lik text ()
    QString get_name();
    QString get_age();
    QString get_mail();




    bool ajouter();              //bool traja3 true or flase
    bool supprimer(int);
    QSqlQueryModel * afficher();  // interface fil qt bch tcommunique les donnees mil base de donnee
    bool modifier(int);
    QSqlQueryModel * triecin();
    QSqlQueryModel * triename();
    QSqlQueryModel * trieage();
    void recherche(QTableView *tableView, int cin);


    void telechargerPDF();

private:
    QString cin,name,age,mail; // variable de type text
};





#endif //
