#ifndef STUDENT_H
#define STUDENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
class student
{

public :
    student();
    student(QString,QString,QString,QString,QString);

    void setid(QString);
    void setnom(QString);
    void setprenom(QString);
    void setmail(QString);
    void setorigine(QString);


    QString get_id();
    QString get_nom();
    QString get_prenom();
    QString get_mail();
    QString get_origine();



bool emailExists(const QString &email);
    bool ajouter();
    bool supprimer(int);
    QSqlQueryModel * afficher();
    bool modifier(int);
    QSqlQueryModel * trieid();
    QSqlQueryModel * trienom();
    QSqlQueryModel * trieprenom();


    void telechargerPDF();

private:
    QString id,nom,prenom,mail,origine;
};





#endif //
