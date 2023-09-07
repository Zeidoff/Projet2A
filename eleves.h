#ifndef ELEVES_H
#define ELEVES_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QFile>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTextStream>
class eleves
{
public:
    eleves();
    eleves(int,QString,QString,int,QString,QDate,QString);

    int getid();
    QString getnom();
    QString getprenom();
    int getnumtel();
    QString getemail();
    QDate getdate();
    QString getgender();

    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setnumtel(int);
    void setemail(QString);
    void setdate(QDate);
    void setgender(QString);

    bool ajouter();
    bool modifier();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_id();
    QSqlQueryModel* tri_id();
    QSqlQueryModel* tri_nom();
    QSqlQueryModel* tri_prenom();

    QString read();
    void write(QString,QString);
    QString time();
    void clearh();
    void clearTable(QTableView * table);
    void chercheID(QTableView *table, QString x);
    void chercheNom(QTableView *table, QString x);
    void cherchePrenom(QTableView *table, QString x);
private:
    int ID;
    QString NOM;
    QString PRENOM;
    int NUMTEL;
    QString EMAIL;
    QDate DATE_DE_NAISSANCE;
    QString GENDER;
};

#endif // ELEVES_H
