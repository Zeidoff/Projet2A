#include "eleves.h"

eleves::eleves()
{
    ID=0;
    NOM=" ";
    PRENOM=" ";
    NUMTEL=0;
    EMAIL=" ";
    DATE_DE_NAISSANCE=QDate();
    GENDER=" ";
}
eleves::eleves(int ID,QString NOM,QString PRENOM,int NUMTEL,QString EMAIL,QDate DATE_DE_NAISSANCE,QString GENDER){
    this->ID=ID;
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->NUMTEL=NUMTEL;
    this->EMAIL=EMAIL;
    this->DATE_DE_NAISSANCE=DATE_DE_NAISSANCE;
    this->GENDER=GENDER;
}
/**************************************/
int eleves::getid() {  return ID; }
QString eleves::getnom() { return NOM; }
QString eleves::getprenom() { return PRENOM; }
int eleves::getnumtel() { return NUMTEL; }
QString eleves::getemail() { return EMAIL; }
QDate eleves::getdate() { return DATE_DE_NAISSANCE; }
QString eleves::getgender() { return GENDER; }
/**************************************/
void eleves::setid(int ID) { this->ID=ID; }
void eleves::setnom(QString NOM) { this->NOM=NOM; }
void eleves::setprenom(QString PRENOM) { this->PRENOM=PRENOM; }
void eleves::setnumtel(int NUMTEL) { this->NUMTEL=NUMTEL; }
void eleves::setemail(QString EMAIL) { this->EMAIL=EMAIL; }
void eleves::setdate(QDate DATE_DE_NAISSANCE) { this->DATE_DE_NAISSANCE=DATE_DE_NAISSANCE; }
void eleves::setgender(QString GENDER) { this->GENDER=GENDER; }
/**************************************/
bool eleves::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(ID);
    query.prepare("INSERT INTO ELEVES(ID,NOM,PRENOM,NUMTEL,EMAIL,DATE_DE_NAISSANCE,GENDER)" "VALUES (:ID,:NOM,:PRENOM,:NUMTEL,:EMAIL,:DATE_DE_NAISSANCE,:GENDER)");
    query.bindValue(":ID", ID);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":NUMTEL", NUMTEL);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":DATE_DE_NAISSANCE", DATE_DE_NAISSANCE);
    query.bindValue(":GENDER", GENDER);
    return query.exec();
}
bool eleves::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE ELEVES SET NOM=:NOM, PRENOM=:PRENOM, NUMTEL=:NUMTL, EMAIL=:EMAIL, DATE_DE_NAISSANCE=:DATE_DE_NAISSANCE, GENDER=:GENDER, WHERE ID=:ID ");
    query.bindValue(":ID", ID);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":NUMTEL", NUMTEL);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":DATE_DE_NAISSANCE", DATE_DE_NAISSANCE);
    query.bindValue(":GENDER", GENDER);
    return query.exec();
}
bool eleves::supprimer(int ID)
{
    QSqlQuery query;
    query.prepare("DELETE FROM ELEVES where ID= :ID");
    query.bindValue(0, ID);
    return query.exec();
}
QSqlQueryModel* eleves::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT ID,NOM,PRENOM,NUMTEL,EMAIL,DATE_DE_NAISSANCE,GENDER FROM ELEVES");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUTMTEL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("GENDER"));
    return  model;
}
QSqlQueryModel* eleves ::afficher_id()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT ID from ELEVES");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    return model;
}
QSqlQueryModel * eleves::tri_id()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * from ELEVES order by ID");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUTMTEL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("GENDER"));
    return model;
}
QSqlQueryModel * eleves::tri_nom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * from ELEVES order by NOM");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUTMTEL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("GENDER"));
    return model;
}
QSqlQueryModel * eleves::tri_prenom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUTMTEL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_DE_NAISSANCE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("GENDER"));
    return model;
}
QString eleves::read()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/ElevesLogs.txt";
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"info",file.errorString());
    QTextStream in(&file);
    return  in.readAll();
}
void eleves::write(QString time, QString txt)
{
    QString filePath = QCoreApplication::applicationDirPath() + "/ElevesLogs.txt";
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream<<time<<" "<<txt<<endl;
        file.close();
    }
}
QString eleves::time()
{
    QDateTime time=time.currentDateTime();
    return  time.toString();
}
void eleves::clearh()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/ElevesLogs.txt";
        QFile file(filePath);
    file.open(QFile::WriteOnly|QFile::Truncate);
}
void eleves::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}
void eleves::chercheID(QTableView *table, QString x)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from ELEVES where regexp_like(ID,:ID);");
    query->bindValue(":ID",x);
    if(x==0)
    {
        query->prepare("select * from ELEVES;");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}
void eleves::chercheNom(QTableView *table, QString x)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from ELEVES where regexp_like(NOM,:NOM);");
    query->bindValue(":NOM",x);
    if(x==0)
    {
        query->prepare("select * from ELEVES;");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}
void eleves::cherchePrenom(QTableView *table, QString x)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from ELEVES where regexp_like(PRENOM,:PRENOM);");
    query->bindValue(":PRENOM",x);
    if(x==0)
    {
        query->prepare("select * from ELEVES;");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}
