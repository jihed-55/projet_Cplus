#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "teacher.h"
#include <QIntValidator>
#include <QTableView>
#include <QMessageBox>
#include <QPixmap>
#include<QPainter>
#include <QPdfWriter>
#include <QtCharts>
#include <QDesktopServices>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QPieSlice>
#include <QPieSeries>
#include <QChartView>
#include  <QDesktopServices>
#include <QVBoxLayout>
#include <QtUiTools/QUiLoader>
#include "emailmessages.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     emailMessages = emailmessages();
    ui->comboBox->addItem("local");
       ui->comboBox->addItem("emigrant");
    connect(ui->showStudentList, &QPushButton::clicked, this, &MainWindow::on_showStudentList_clicked);
    connect(ui->sendEmailButton, &QPushButton::clicked, this, &MainWindow::on_sendEmailButton_clicked);
    connect(ui->comboBox, QOverload<const QString&>::of(&QComboBox::currentIndexChanged),
                this, &MainWindow::on_comboBox_activated);
    ui->tableView->setModel(etmp.afficher());

    // Controle de saisie
    ui->cin_add->setValidator(new QIntValidator(0, 99999999, this));
    ui->age_add->setValidator(new QIntValidator(1111111, 9999999, this));
    ui->name_add->setValidator(new QRegExpValidator(QRegExp("[A-z]*")));
    QRegExpValidator *emailValidator = new QRegExpValidator(
        QRegExp("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}"), this);
    ui->mail_add2->setValidator(emailValidator);

    ui->tableView_2->setModel(stmp.afficher());


    ui->id_add->setValidator(new QIntValidator(0, 99999999, this));
    ui->nom_add->setValidator(new QRegExpValidator(QRegExp("[A-z]*")));
    ui->prenom_add->setValidator(new QRegExpValidator(QRegExp("[A-z]*")));
    QRegExpValidator *emailValidatorr= new QRegExpValidator(
        QRegExp("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}"), this);
    ui->mail_add->setValidator(emailValidatorr)
;

}




MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::on_sendEmailButton_clicked()
{
    QString recipientEmail = QInputDialog::getText(this, "Student", "Enter student's email address:");
    if (recipientEmail.isEmpty()) {
        QMessageBox::warning(this, "Error", "Student's email address cannot be empty.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM STUDENT WHERE MAIL = :mail");
    query.bindValue(":mail", recipientEmail);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Error checking email in the database.");
        return;
    }

    query.next();
    int emailCount = query.value(0).toInt();
    if (emailCount == 0) {
        QMessageBox::warning(this, "Error", "Student's email address does not exist in the database.");
        return;
    }

    QString message = QInputDialog::getText(this, "Send Email", "Enter your message:");
    if (message.isEmpty()) {
        QMessageBox::warning(this, "Error", "Message cannot be empty.");
        return;
    }

        // Insert the email and message into the EMAILMESSAGES table
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO EMAILMESSAGES (SENDER, RECIPIENT, MESSAGE, DATEE) VALUES (:sender, :recipient, :message, :datee)");
    insertQuery.bindValue(":sender", "esprit@esprit.tn");      // You need to set the sender's email here
    insertQuery.bindValue(":recipient", recipientEmail);
    insertQuery.bindValue(":message", message);
    insertQuery.bindValue(":datee", QDateTime::currentDateTime());

    if (!insertQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Error inserting email message into the database.");
        return;
    }

    QMessageBox::information(this, "Email Sent", "Email sent successfully and added to the database.");
}


void MainWindow::on_ajouter_clicked()
{
    teacher res;


    res.setcin(ui->cin_add->text());
    res.setname(ui->name_add->text());
    res.setage(ui->age_add->text());
    res.setmail(ui->mail_add2->text());

    bool test=res.ajouter();
   if(test)
   {
         ui->tableView->setModel(etmp.afficher());
       QMessageBox ::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
   }
else
       QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                             QObject::tr("Ajout non effectué.\n"
                                         "Click Cancel to exit."), QMessageBox:: Cancel);
}
void MainWindow::on_suprimer_clicked()
{
    int cin=ui->cin_add->text().toInt();
    bool test=etmp.supprimer(cin);
    if(test)
    {
        ui->tableView->setModel(etmp.afficher());
        QMessageBox ::information(nullptr, QObject::tr("OK"),
                                  QObject::tr("Suppression effectué\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
    }
 else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                              QObject::tr("Suppression non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox:: Cancel);
}
void MainWindow::on_modifier_clicked()
{
    bool ok = false;
    int cin = ui->name_modif->text().toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Error", "Invalid CIN input");
        return;
    }

    teacher res;

    res.setname(ui->name_add->text());
    res.setage(ui->age_add->text());
    res.setmail(ui->mail_add2->text());

    bool modificationSuccess = res.modifier(cin);

    if (modificationSuccess) {
        QMessageBox::information(this, "Success", "Teacher data modified successfully");

        ui->name_modif->clear();
        ui->name_add->clear();
        ui->age_add->clear();
        ui->mail_add2->clear();

        // Set the visibility of input fields
        ui->name_add->setVisible(true);
        ui->age_add->setVisible(true);
        ui->mail_add2->setVisible(true);

    } else {
        QMessageBox::warning(this, "Error", "Failed to modify teacher data");
    }

}


void MainWindow::on_radioButton_clicked()

{
    ui->tableView->setModel(etmp.triecin());
}

void MainWindow::on_radioButton_2_clicked()

{
    ui->tableView->setModel(etmp.triename());
}
void MainWindow::on_radioButton_3_clicked()

{
    ui->tableView->setModel(etmp.trieage());
}





void MainWindow::on_export_pdf_clicked()
{
    etmp.telechargerPDF();



            QMessageBox::information(nullptr,QObject::tr("OK"),

                       QObject::tr("Téléchargement terminé"), QMessageBox::Cancel);

}





void MainWindow::on_ajouter_3_clicked()
{
    student res;


    res.setid(ui->id_add->text());
    res.setnom(ui->nom_add->text());
    res.setprenom(ui->prenom_add->text());
    res.setmail(ui->mail_add->text());
    res.setorigine(ui->comboBox->currentText());

    bool test=res.ajouter();
   if(test)
   {
         ui->tableView_2->setModel(stmp.afficher());
       QMessageBox ::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
   }
else
       QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                             QObject::tr("Ajout non effectué.\n"
                                         "Click Cancel to exit."), QMessageBox:: Cancel);
}

void MainWindow::on_suprimer_3_clicked()
{
    int id=ui->id_add->text().toInt();
    bool test=stmp.supprimer(id);
    if(test)
    {
        ui->tableView_2->setModel(stmp.afficher());
        QMessageBox ::information(nullptr, QObject::tr("OK"),
                                  QObject::tr("Suppression effectué\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
    }
 else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                              QObject::tr("Suppression non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox:: Cancel);
}

void MainWindow::on_export_pdf_3_clicked()
{
    stmp.telechargerPDF();



            QMessageBox::information(nullptr,QObject::tr("OK"),

                       QObject::tr("Téléchargement terminé"), QMessageBox::Cancel);

}
void MainWindow::on_modifier_3_clicked()
{
    bool ok = false;
    int id = ui->name_modif_3->text().toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Error", "Invalid ID input");
        return;
    }

    student res;

    res.setnom(ui->nom_add->text());
    res.setprenom(ui->prenom_add->text());
    res.setmail(ui->mail_add->text());
    res.setorigine(ui->comboBox->currentText());

    bool modificationSuccess = res.modifier(id);

    if (modificationSuccess) {
        ui->tableView_2->setModel(stmp.afficher());

        QMessageBox::information(this, "Success", "Teacher data modified successfully");

        ui->name_modif_3->clear();
        ui->nom_add->clear();
        ui->prenom_add->clear();
        ui->mail_add->clear();
        ui->comboBox->clear();

        // Set the visibility of input fields
        ui->nom_add->setVisible(true);
        ui->prenom_add->setVisible(true);
        ui->mail_add->setVisible(true);
        ui->mail_add->setVisible(true);
        ui->comboBox->setVisible(true);

    } else {
        QMessageBox::warning(this, "Error", "Failed to modify student data");
    }
}

void MainWindow::on_radioButton_12_clicked()
{
    ui->tableView_2->setModel(stmp.trieid());

}

void MainWindow::on_radioButton_10_clicked()
{
    ui->tableView_2->setModel(stmp.trienom());

}

void MainWindow::on_radioButton_11_clicked()
{
    ui->tableView_2->setModel(stmp.trieprenom());

}

void MainWindow::on_showStudentList_clicked()
{
    student stmp;  // Create an instance of the student class

    ui->tableView->setModel(stmp.afficher());
}


void MainWindow::on_stat_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    // Query for teachers aged between 20 and 30
    model->setQuery("SELECT * FROM TEACHER WHERE AGE >= 20 AND AGE < 30");
    float dispo1 = model->rowCount();

    // Query for teachers aged between 30 and 40
    model->setQuery("SELECT * FROM TEACHER WHERE AGE >= 30 AND AGE < 40");
    float dispo2 = model->rowCount();

    // Query for teachers aged between 40 and 50
    model->setQuery("SELECT * FROM TEACHER WHERE AGE >= 40 AND AGE < 50");
    float dispo3 = model->rowCount();

    float total = dispo1 + dispo2 + dispo3;

    QString a = QString("20-30 " + QString::number((dispo1 * 100) / total, 'f', 2) + "%");
    QString b = QString("30-40 " + QString::number((dispo2 * 100) / total, 'f', 2) + "%");
    QString c = QString("40-50 " + QString::number((dispo3 * 100) / total, 'f', 2) + "%");

    QPieSeries *series = new QPieSeries();
    series->append(a, dispo1);
    series->append(b, dispo2);
    series->append(c, dispo3);

    if (dispo1 != 0)
    {
        QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }
    if (dispo2 != 0)
    {
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();
        slice1->setPen(QPen());
    }
    if (dispo3 != 0)
    {
        QPieSlice *slice = series->slices().at(2);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Teacher Age Distribution");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1300, 800);
    chartView->show();
}


void MainWindow::on_recherche_cursorPositionChanged(int arg1, int arg2)
{
    QString rech = ui->recherche->text();
    bool isIdValid;
    int teacherId = rech.toInt(&isIdValid); // Convert the input to an integer

    if (isIdValid)
    {

        etmp.recherche(ui->tableView, teacherId); // Call the recherche function
    }
    else
    {
        ui->tableView->setModel(nullptr);
    }
}

void MainWindow::on_comboBox_activated(const QString &text)
{

    QSqlTableModel *model = new QSqlTableModel(this);
    if (text == "local")
    {
        model->setTable("STUDENT");
        model->setFilter("LOCATION = 'local'");
    }
    else if (text == "emigrant")
    {
        model->setTable("STUDENT");
        model->setFilter("LOCATION = 'emigrant'");
    }
    model->select();

    ui->tableView->setModel(model);
}

void MainWindow::on_ajouter_4_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM STUDENT WHERE ORIGINE = 'local'");
    float dispo1 = model->rowCount();

    model->setQuery("SELECT * FROM STUDENT WHERE ORIGINE = 'emigrant'");
    float dispo2 = model->rowCount();

    float total = dispo1 + dispo2;

    QString a = QString("local " + QString::number((dispo1 * 100) / total, 'f', 2) + "%");
    QString b = QString("emigrant " + QString::number((dispo2 * 100) / total, 'f', 2) + "%");

    QPieSeries *series = new QPieSeries();
    series->append(a, dispo1);
    series->append(b, dispo2);

    if (dispo1 != 0)
    {
        QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }
    if (dispo2 != 0)
    {
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();
        slice1->setPen(QPen());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Student Origin Distribution"); // Update title

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1300, 800);
    chartView->show();
}
void MainWindow::on_showmails_clicked()
{
    QSqlQueryModel *model = emailMessages.afficher();
    ui->tableView->setModel(model);
    ui->tableView_2->setModel(model);

    // Adjust column widths
    ui->tableView->resizeColumnsToContents();
    ui->tableView_2->resizeColumnsToContents();

    // Enable word wrap for the message column
    ui->tableView->setWordWrap(true);
    ui->tableView_2->setWordWrap(true);

}


void MainWindow::on_certificat_clicked()
{
    // Step 2: Prompt the user to enter a student email
    QString studentEmail = QInputDialog::getText(this, "Generate Certificate", "Enter student's email:");
    if (studentEmail.isEmpty()) {
        QMessageBox::warning(this, "Error", "Student's email cannot be empty.");
        return;
    }

    // Step 3: Check if the email exists in the database
    QSqlQuery query;
    query.prepare("SELECT * FROM STUDENT WHERE MAIL = :email");
    query.bindValue(":email", studentEmail);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Error checking email in the database.");
        return;
    }

    if (!query.next()) {
        QMessageBox::warning(this, "Error", "Student's email does not exist in the database.");
        return;
    }

    QString studentName = query.value("NOM").toString();
       QString studentPrenom = query.value("PRENOM").toString();
       QString pdfFilePath = "C:/Users/User/OneDrive/Desktop/export pdf/PDF.pdf"; // Change this to your desired path

       QPdfWriter pdfWriter(pdfFilePath);
       QPainter painter(&pdfWriter);

       int yPos = 100; // Initial Y-coordinate
       int lineHeight = 300; // Adjust this value for desired line spacing

       QStringList messageLines = {
           "This is to certify that " + studentName + " " + studentPrenom + " has attended the session.",
           "Session details",
           "sessionvsessionef geg dg",
           " egfdgdgerge gegeg  fesession",
           " sessi azea zaeazea on",
           " azeaze kp,zg kz,ro pz,arog",
           "ez godnojdns hrzomlshedq hzth",
           "rth nziogijeanf poazjf npoeh",
           "ze rzgoiezngaozk fpztenhoje pg."
       };
       QString certificateText = "Certificate of Presence";
        int textWidth = painter.fontMetrics().width(certificateText); // Get width of the text

        int xCenter = (pdfWriter.width() - textWidth) / 2; // Calculate X-coordinate for centering

        painter.drawText(xCenter, yPos, certificateText);
        yPos += lineHeight;

       painter.drawText(100, yPos, "Student Name: " + studentName);
       yPos += lineHeight;

       painter.drawText(100, yPos, "Student Prenom: " + studentPrenom);
       yPos += lineHeight;

       painter.drawText(100, yPos, "Email: " + studentEmail);
       yPos += lineHeight * 2; // Adding extra spacing between details and message

       foreach (const QString& line, messageLines) {
           painter.drawText(100, yPos, line);
           yPos += lineHeight;
       }

       painter.end(); // Close the painter

       QMessageBox::information(this, "Certificate Generated", "Certificate has been generated and saved.");

}

