#ifndef ENSEIGNANTS_H
#define ENSEIGNANTS_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QFile>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTextStream>
class enseignants
{
public:
    enseignants();
    enseignants(int,QString,QString,QString,QDate,QString,QString,QString,QString);
    int getcin();
    QString getnom();
    QString getprenom();
    QString getgender();
    QDate getdate();
    QString getemail();
    QString getadresse();
    QString getgestion();

    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    void setgender(QString);
    void setdate(QDate);
    void setemail(QString);
    void setadresse(QString);
    void setgestion(QString);

    bool ajouter();
    bool modifier();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_cin();
    QSqlQueryModel* tri_cin();
    QSqlQueryModel* tri_nom();
    QSqlQueryModel* tri_prenom();

    QString read();
    void write(QString,QString);
    QString time();
    void clearh();

    void clearTable(QTableView * table);
    void chercheCIN(QTableView *table, QString x);
    void chercheNom(QTableView *table, QString x);
    void cherchePrenom(QTableView *table, QString x);
    QString PASSWORD;
private:
    int CIN;
    QString NOM;
    QString PRENOM;
    QString GENDER;
    QDate DATE_DE_NAISSANCE;
    QString EMAIL;
    QString ADRESSE;
    QString GESTION;
};

#endif // ENSEIGNANTS_H
