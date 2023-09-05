#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "teacher.h"
#include "student.h"
#include "emailmessages.h"

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QStandardItemModel>
#include <QTableView>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_sendEmailButton_clicked();

    void on_ajouter_clicked();

    void on_suprimer_clicked();

    void on_modifier_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();


    void on_export_pdf_clicked();






    void on_ajouter_3_clicked();

    void on_suprimer_3_clicked();

    void on_export_pdf_3_clicked();

    void on_modifier_3_clicked();

    void on_radioButton_12_clicked();

    void on_radioButton_10_clicked();

    void on_radioButton_11_clicked();




    void on_showStudentList_clicked();


    void on_stat_clicked();

    void on_recherche_cursorPositionChanged(int arg1, int arg2);

    void on_comboBox_activated(const QString &arg1);

    void on_ajouter_4_clicked();

    void on_showmails_clicked();

    void on_certificat_clicked();

private:
    Ui::MainWindow *ui;
    teacher etmp;
    emailmessages emailMessages;
    student stmp;
     QTableView *tableView;
};
#endif // MAINWINDOW_H
