#include "enseignants.h"

enseignants::enseignants()
{
    CIN=0;
    NOM=" ";
    PRENOM=" ";
    ADRESSE=" ";
    EMAIL=" ";
    GESTION=" ";
    GENDER=" ";
    DATE_DE_NAISSANCE=QDate();
    PASSWORD=" ";
}
enseignants::enseignants(int CIN,QString NOM,QString PRENOM,QString GENDER,QDate DATE_DE_NAISSANCE,QString EMAIL,QString ADRESSE,QString GESTION,QString PASSWORD){
    this->CIN=CIN;
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->ADRESSE=ADRESSE;
    this->EMAIL=EMAIL;
    this->DATE_DE_NAISSANCE=DATE_DE_NAISSANCE;
    this->PASSWORD=PASSWORD;
    this->GENDER=GENDER;
    this->GESTION=GESTION;
}
/**************************************/
int enseignants::getcin() {  return CIN; }
QString enseignants::getnom() { return NOM; }
QString enseignants::getprenom() { return PRENOM; }
QString enseignants::getgender() { return GENDER; }
QDate enseignants::getdate() { return DATE_DE_NAISSANCE; }
QString enseignants::getemail() { return EMAIL; }
QString enseignants::getadresse() { return ADRESSE; }
QString enseignants::getgestion() { return GESTION; }
/**************************************/
void enseignants::setcin(int CIN) { this->CIN=CIN; }
void enseignants::setnom(QString NOM) { this->NOM=NOM; }
void enseignants::setprenom(QString PRENOM) { this->PRENOM=PRENOM; }
void enseignants::setgender(QString GENDER) { this->GENDER=GENDER; }
void enseignants::setdate(QDate DATE_DE_NAISSANCE) { this->DATE_DE_NAISSANCE=DATE_DE_NAISSANCE; }
void enseignants::setemail(QString EMAIL) { this->EMAIL=EMAIL; }
void enseignants::setadresse(QString ADRESSE) { this->ADRESSE=ADRESSE; }
void enseignants::setgestion(QString GESTION) { this->GESTION=GESTION; }
/**************************************/
bool enseignants::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(CIN);
    query.prepare("INSERT INTO ENSEIGNANTS(CIN,NOM,PRENOM,GENDER,DATE_DE_NAISSANCE,EMAIL,ADRESSE,GESTION,PASSWORD)" "VALUES (:CIN,:NOM,:PRENOM,:GENDER,:DATE_DE_NAISSANCE,:EMAIL,:ADRESSE,:GESTION,:PASSWORD)");
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":GENDER", GENDER);
    query.bindValue(":DATE_DE_NAISSANCE", DATE_DE_NAISSANCE);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":GESTION", GESTION);;
    query.bindValue(":PASSWORD", PASSWORD);
    return query.exec();
}
bool enseignants::supprimer(int CIN)
{
    QSqlQuery query;
    query.prepare("DELETE FROM ENSEIGNANTS where CIN= :CIN");
    query.bindValue(0, CIN);
    return query.exec();
}
bool enseignants::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE ENSEIGNANTS SET NOM=:NOM, PRENOM=:PRENOM, GENDER=:GENDER, DATE_DE_NAISSANCE=:DATE_DE_NAISSANCE, EMAIL=:EMAIL, ADRESSE=:ADRESSE, GESTION=:GESTION, PASSWORD=:PASSWORD, WHERE CIN=:CIN ");
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":GENDER", GENDER);
    query.bindValue(":DATE_DE_NAISSANCE", DATE_DE_NAISSANCE);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":GESTION", GESTION);
    query.bindValue(":PASSWORD", PASSWORD);
    return query.exec();
}
QSqlQueryModel* enseignants::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT CIN,NOM,PRENOM,GENDER,DATE_DE_NAISSANCE,EMAIL,ADRESSE,GESTION FROM ENSEIGNANTS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENDER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("GESTION"));
    return  model;
}
QSqlQueryModel* enseignants ::afficher_cin()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT CIN from ENSEIGNANTS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    return model;
}

QSqlQueryModel * enseignants::tri_cin()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT CIN,NOM,PRENOM,GENDER,DATE_DE_NAISSANCE,EMAIL,ADRESSE,GESTION from ENSEIGNANTS order by CIN");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENDER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("GESTION"));
    return model;
}
QSqlQueryModel * enseignants::tri_nom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT CIN,NOM,PRENOM,GENDER,DATE_DE_NAISSANCE,EMAIL,ADRESSE,GESTION from ENSEIGNANTS order by NOM");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENDER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("GESTION"));
    return model;
}
QSqlQueryModel * enseignants::tri_prenom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT CIN,NOM,PRENOM,GENDER,DATE_DE_NAISSANCE,EMAIL,ADRESSE,GESTION from ENSEIGNANTS order by PRENOM");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENDER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("GESTION"));
    return model;
}
QString enseignants::read()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/EnsLogs.txt";
        QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());
    QTextStream in(&file);
    return  in.readAll();
}
void enseignants::write(QString time, QString txt)
{
    QString filePath = QCoreApplication::applicationDirPath() + "/EnsLogs.txt";
        QFile file(filePath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream<<time<<" "<<txt<<endl;
        file.close();
    }
}
QString enseignants::time()
{
    QDateTime time=time.currentDateTime();
    return  time.toString();
}
void enseignants::clearh()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/EnsLogs.txt";
        QFile file(filePath);
    file.open(QFile::WriteOnly|QFile::Truncate);
}
void enseignants::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}
void enseignants::chercheCIN(QTableView *table, QString x)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from ENSEIGNANTS where regexp_like(CIN,:CIN);");
    query->bindValue(":CIN",x);
    if(x==0)
    {
        query->prepare("select * from ENSEIGNANTS;");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}
void enseignants::chercheNom(QTableView *table, QString x)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from ENSEIGNANTS where regexp_like(NOM,:NOM);");
    query->bindValue(":NOM",x);
    if(x==0)
    {
        query->prepare("select * from ENSEIGNANTS;");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}
void enseignants::cherchePrenom(QTableView *table, QString x)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from ENSEIGNANTS where regexp_like(PRENOM,:PRENOM);");
    query->bindValue(":PRENOM",x);
    if(x==0)
    {
        query->prepare("select * from ENSEIGNANTS;");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}
