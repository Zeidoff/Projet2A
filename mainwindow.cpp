#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bool test=c.CreateConnexion();
    if(test)
        ui->Login_label_Connection->setText("Datebase: Open.\nConnection: Successful.");
    else
        ui->Login_label_Connection->setText("Datebase: Closed.\nConnection: Failed.");
    nSocket=new QTcpSocket(this);
    connect(nSocket,&QTcpSocket::readyRead,[&](){
        QTextStream T(nSocket);
        auto text=T.readAll();
        ui->Ens_text_Chatbox->append(text);
    });
    ui->stackedWidget->setCurrentIndex(0);
    ui->Menu_Ens->setEnabled(false);
    ui->Menu_Elv->setEnabled(false);
    ui->Menu_Act->setEnabled(false);
    ui->Menu_Etab->setEnabled(false);

    QRegularExpression EmailVal("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    QRegularExpression Name("^[A-Za-z]+$");
    ui->Login_line_CIN->setValidator( new QIntValidator(0, 99999999, this));
    ui->Ens_line_CIN->setValidator( new QIntValidator(0, 99999999, this));
    ui->Elv_line_ID->setValidator( new QIntValidator(0, 99999999, this));
    ui->Elv_line_Numtel->setValidator( new QIntValidator(0, 99999999, this));
    ui->Ens_line_Email->setValidator(new QRegularExpressionValidator(EmailVal, this));
    ui->Ens_line_Nom->setValidator(new QRegularExpressionValidator(Name, this));
    ui->Elv_line_Nom->setValidator(new QRegularExpressionValidator(Name, this));
    ui->Ens_line_Prenom->setValidator(new QRegularExpressionValidator(Name, this));
    ui->Elv_line_Prenom->setValidator(new QRegularExpressionValidator(Name, this));

    MainWindow::connect(ui->envoyer_dialog_2, SIGNAL(clicked()),this, SLOT(sendMail()));
    MainWindow::connect(ui->annuler_mail_2, SIGNAL(clicked()),this, SLOT(close()));

    A = new QCPBars(ui->Elv_Plot->xAxis, ui->Elv_Plot->yAxis);
    A->setAntialiased(false);
    A->setStackingGap(1);
    A->setName("Nombre des Eleves par Âge");
    A->setPen(QPen(QColor(120, 120, 120).lighter(120)));
    A->setBrush(QColor(177, 177, 177));
}
MainWindow::MainWindow(QString e,QMainWindow *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    QString contenu="Contenu";
    ui->setupUi(this);
    ui->recipient_2->setText(e);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_Login_push_Login_clicked()
{
    QString CIN = ui->Login_line_CIN->text();
    QString PASSWORD = ui->Login_line_Password->text();
    QSqlQuery query;
    QString gestion;
    if(query.exec("SELECT * from ENSEIGNANTS where CIN='"+CIN+"' and PASSWORD='"+PASSWORD+"'" ))
    {
        if (query.next())
        {
            ui->stackedWidget->setCurrentIndex(1);
            gestion=query.value(7).toString();
            if (gestion.compare("Administrateur")==0){
                ui->Menu_Ens->setEnabled(true);
                ui->Menu_Elv->setEnabled(true);
                ui->Menu_Act->setEnabled(true);
                ui->Menu_Etab->setEnabled(true);
            }
            if (gestion.compare("Enseignants")==0){
                ui->Menu_Ens->setEnabled(true);
                ui->Menu_Elv->setEnabled(false);
                ui->Menu_Act->setEnabled(false);
                ui->Menu_Etab->setEnabled(false);
            }
            if (gestion.compare("Elèves")==0){
                ui->Menu_Ens->setEnabled(false);
                ui->Menu_Elv->setEnabled(true);
                ui->Menu_Act->setEnabled(false);
                ui->Menu_Etab->setEnabled(false);
            }
            if (gestion.compare("Etablissements")==0){
                ui->Menu_Ens->setEnabled(false);
                ui->Menu_Elv->setEnabled(false);
                ui->Menu_Act->setEnabled(false);
                ui->Menu_Etab->setEnabled(true);
            }
            if (gestion.compare("Activités")==0){
                ui->Menu_Ens->setEnabled(false);
                ui->Menu_Elv->setEnabled(false);
                ui->Menu_Act->setEnabled(true);
                ui->Menu_Etab->setEnabled(false);
            }
            QString NOM=query.value(1).toString();
            QString PRENOM=query.value(2).toString();
            ConnectedUser=NOM+" "+PRENOM;
            ui->Login_label_LoginInfo->setText("Connecté: "+ConnectedUser+"");
            ui->Menu_label_LoggedAs->setText("Logged in as: "+ConnectedUser+"\nGestion: "+gestion+"");
        }
        else
        {
            ui->Login_label_LoginInfo->setText("CIN ou Password est incorrect");
        }
    }
}
int modes=1;
void MainWindow::on_Login_check_PassShowHide_clicked()
{
    if(modes==1){
        ui->Login_line_Password->setEchoMode(QLineEdit::Normal);modes=0;}
    else{ui->Login_line_Password->setEchoMode(QLineEdit::Password);modes=1;}
}
void MainWindow::on_Menu_Ens_clicked(){
    ui->stackedWidget->setCurrentIndex(2);
    ui->Ens_TableView->setModel(ENS.afficher());
    ui->Ens_combo_CIN->setModel (ENS.afficher_cin());
}
void MainWindow::on_Menu_Elv_clicked(){
    ui->stackedWidget->setCurrentIndex(3);
    ui->Elv_TableView->setModel(ELV.afficher());
    ui->Elv_combo_ID->setModel (ELV.afficher_id());
}
void MainWindow::on_Menu_Return_clicked(){ui->stackedWidget->setCurrentIndex(0);}
void MainWindow::on_Menu_Quit_clicked(){close();}
/***********    GESTION ENSEIGNANTS     ***********/
void MainWindow::on_Ens_push_Ajouter_clicked()
{
    int CIN=ui->Ens_line_CIN->text().toInt();
    QString NOM=ui->Ens_line_Nom->text();
    QString PRENOM=ui->Ens_line_Prenom->text();
    QString GENDER=ui->Ens_combo_Gender->currentText();
    QDate DATE_DE_NAISSANCE=ui->Ens_date_DDN->date();
    QString EMAIL=ui->Ens_line_Email->text();
    QString ADRESSE=ui->Ens_line_Adresse->text();
    QString GESTION=ui->Ens_combo_Gestion->currentText();
    QString PASSWORD=ui->Ens_line_Password->text();
    enseignants ENS(CIN,NOM,PRENOM,GENDER,DATE_DE_NAISSANCE,EMAIL,ADRESSE,GESTION,PASSWORD);
    bool test=ENS.ajouter();
    if(test)
    {
        ui->Ens_Label_GestionInfo->setText("Ajout Effectué");
        ui->Ens_TableView->setModel(ENS.afficher());
        ui->Ens_combo_CIN->setModel (ENS.afficher_cin());
        ENS.write(ENS.time(),"ENSEIGNANTS: ajout effectué");
        ui->Ens_textbrowser->setText(ENS.read());
    }
    else
    {
        ui->Ens_Label_GestionInfo->setText("Ajout: ERROR");
    }
}
void MainWindow::on_Ens_push_Modifier_clicked()
{
    int CIN=ui->Ens_line_CIN->text().toInt();
    QString NOM=ui->Ens_line_Nom->text();
    QString PRENOM=ui->Ens_line_Prenom->text();
    QString GENDER=ui->Ens_combo_Gender->currentText();
    QDate DATE_DE_NAISSANCE=ui->Ens_date_DDN->date();
    QString EMAIL=ui->Ens_line_Email->text();
    QString ADRESSE=ui->Ens_line_Adresse->text();
    QString GESTION=ui->Ens_combo_Gestion->currentText();
    QString PASSWORD=ui->Ens_line_Password->text();
    enseignants ENS(CIN,NOM,PRENOM,GENDER,DATE_DE_NAISSANCE,EMAIL,ADRESSE,GESTION,PASSWORD);
    bool test=ENS.modifier();
    if(test)
    {
        ui->Ens_Label_GestionInfo->setText("Modification Effectué");
        ui->Ens_TableView->setModel(ENS.afficher());
        ui->Ens_combo_CIN->setModel (ENS.afficher_cin());
        ENS.write(ENS.time(),"ENSEIGNANTS: Modification effectué");
        ui->Ens_textbrowser->setText(ENS.read());
    }
    else
    {
        ui->Ens_Label_GestionInfo->setText("Modification: ERROR");
    }
}
void MainWindow::on_Ens_push_Supprimer_clicked()
{
    enseignants ENS;
    ENS.setcin(ui->Ens_combo_CIN->currentText().toInt());
    bool test=ENS.supprimer(ENS.getcin());
    if(test)
    {
        ui->Ens_Label_GestionInfo->setText("Suppression effectué");
        ui->Ens_TableView->setModel(ENS.afficher());
        ui->Ens_combo_CIN->setModel(ENS.afficher_cin());
        ENS.write(ENS.time(),"ENSEIGNANTS: Supression effectuée");
        ui->Ens_textbrowser->setText(ENS.read());
    }
    else
    {
        ui->Ens_Label_GestionInfo->setText("Suppression: ERROR");
    }
}
void MainWindow::on_Ens_push_TriCIN_clicked()
{
    ui->Ens_Label_ListeInfo->setText("Tri par CIN effectué");
    ui->Ens_TableView->setModel(ENS.tri_cin());
}
void MainWindow::on_Ens_push_TriNom_clicked()
{
    ui->Ens_Label_ListeInfo->setText("Tri par NOM effectué");
    ui->Ens_TableView->setModel(ENS.tri_nom());
}
void MainWindow::on_Ens_push_TriPrenom_clicked()
{
    ui->Ens_Label_ListeInfo->setText("Tri par PRENOM effectué");
    ui->Ens_TableView->setModel(ENS.tri_prenom());
}
void MainWindow::on_Ens_combo_CIN_currentIndexChanged(int)
{
    int cin=ui->Ens_combo_CIN->currentText().toInt();
    QString cin_1=QString::number(cin);
    QSqlQuery query;
    query.prepare("SELECT * FROM ENSEIGNANTS where CIN='"+cin_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->Ens_line_CIN->setText(query.value(0).toString()) ;
            ui->Ens_line_Nom->setText(query.value(1).toString()) ;
            ui->Ens_line_Prenom->setText(query.value(2).toString()) ;
            ui->Ens_combo_Gender->setCurrentText(query.value(3).toString()) ;
            ui->Ens_date_DDN->setDate(query.value(4).toDate()) ;
            ui->Ens_line_Email->setText(query.value(5).toString()) ;
            ui->Ens_line_Adresse->setText(query.value(6).toString()) ;
            ui->Ens_combo_Gestion->setCurrentText(query.value(7).toString()) ;
            ui->Ens_line_Password->setText(query.value(8).toString()) ;
        }
    }
    else
    {
        ui->Ens_Label_GestionInfo->setText("Chargement: ERROR");
    }
}
void MainWindow::on_Ens_line_Recherche_textChanged(const QString &arg1)
{
    if (ui->Ens_radio_CIN->isChecked()==true)
    {
        ENS.clearTable(ui->Ens_TableView);
        ENS.chercheCIN(ui->Ens_TableView,arg1);
    }
    if (ui->Ens_radio_Nom->isChecked()==true)
    {
        ENS.clearTable(ui->Ens_TableView);
        ENS.chercheNom(ui->Ens_TableView,arg1);
    }
    if (ui->Ens_radio_Prenom->isChecked()==true)
    {
        ENS.clearTable(ui->Ens_TableView);
        ENS.chercheNom(ui->Ens_TableView,arg1);
    }
}
void MainWindow::Ens_choix_pie(){
    QChartView *chartView ;
    QSqlQuery q1,q2,q3,q4;
    qreal tot=0,c1=0,c2=0,c3=0;
    q1.prepare("SELECT * FROM ENSEIGNANTS");
    q1.exec(); q2.prepare("SELECT * FROM ENSEIGNANTS WHERE GENDER='Homme'");
    q2.exec(); q3.prepare("SELECT * FROM ENSEIGNANTS WHERE GENDER='Femme'");
    q3.exec(); q4.prepare("SELECT * FROM ENSEIGNANTS WHERE GENDER='Autre'");
    q4.exec();
    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}
    c1=c1/tot; c2=c2/tot; c3=c3/tot;
    QPieSeries *series = new QPieSeries();
    series->append("Homme",c1);
    series->append("Femme",c2);
    series->append("Autre",c3);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->show();
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeQt);
    chartView = new QChartView(chart,ui->Ens_label_Stats);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(570,570);
    chartView->show();
}
void MainWindow::on_Ens_push_ExportPDF_clicked()
{
    QPdfWriter pdf("C:/Users/zeidc/Desktop/ProjetCPP/ListeENS.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));
    QPixmap pixmap(":/png/resources/ens.png");
    painter.drawPixmap(QRect(100, 400, 2000, 2000), pixmap);
    painter.drawText(3000,1500,"LISTE DES ENSEIGNANTS");
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 50));
    //painter.drawRect(2700,200,6300,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"CIN");
    painter.drawText(1800,3300,"NOM");
    painter.drawText(2800,3300,"PRENOM");
    painter.drawText(3800,3300,"GENDER");
    painter.drawText(4800,3300,"DATE DE NAISSANCE");
    painter.drawText(6700,3300,"ADRESSE");
    painter.drawText(7700,3300,"GESTION");
    QSqlQuery query;
    query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti=localtime(&tt);
    asctime(ti);
    painter.drawText(500,300, asctime(ti));
    query.prepare("select CIN,NOM,PRENOM,GENDER,DATE_DE_NAISSANCE,ADRESSE,GESTION from ENSEIGNANTS");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(1800,i,query.value(1).toString());
        painter.drawText(2800,i,query.value(2).toString());
        painter.drawText(3800,i,query.value(3).toString());
        painter.drawText(4800,i,query.value(4).toString());
        painter.drawText(6700,i,query.value(5).toString());
        painter.drawText(7700,i,query.value(6).toString());
        i = i +500;
    }
    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/zeidc/Desktop/ProjetCPP/ListeENS.pdf"));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}
void MainWindow::on_Ens_push_SupprimerTextBrowser_clicked()
{
    ENS.clearh();
    ui->Ens_textbrowser->setText(ENS.read());
}
void MainWindow::on_Ens_push_UpdateStats_clicked()
{
    Ens_choix_pie();
    show();
}
void MainWindow::on_Ens_push_Send_clicked()
{
    QTextStream T(nSocket);
    QSqlQuery query;
    QString NOM=query.value(1).toString();
    QString PRENOM=query.value(2).toString();
    T << ConnectedUser << ": " << ui->Ens_line_Message->text();
    nSocket->flush();
    ui->Ens_line_Message->clear();
}
void MainWindow::on_Ens_push_Bind_clicked()
{
    chatboxconnectiondialog D(this);
    if(D.exec()==QDialog::Rejected)
    {return;}
    nSocket->connectToHost(D.hostname(),D.port());
}
void MainWindow::on_Ens_push_Return_clicked(){ui->stackedWidget->setCurrentIndex(1);}
/***********    GESTION ELEVES     ***********/
void MainWindow::on_Elv_push_Ajouter_clicked()
{
    int ID=ui->Elv_line_ID->text().toInt();
    QString NOM=ui->Elv_line_Nom->text();
    QString PRENOM=ui->Elv_line_Prenom->text();
    int NUMTEL=ui->Elv_line_Numtel->text().toInt();
    QString EMAIL=ui->Elv_line_Email->text();
    QDate DATE_DE_NAISSANCE=ui->Elv_date_DDN->date();
    QString GENDER=ui->Elv_combo_Gender->currentText();
    eleves ELV(ID,NOM,PRENOM,NUMTEL,EMAIL,DATE_DE_NAISSANCE,GENDER);
    bool test=ELV.ajouter();
    if(test)
    {
        ui->Elv_Label_GestionInfo->setText("Ajout Effectué");
        ui->Elv_TableView->setModel(ELV.afficher());
        ui->Elv_combo_ID->setModel (ELV.afficher_id());
        ELV.write(ELV.time(),"ELEVES: ajout effectué");
        ui->Elv_textbrowser->setText(ELV.read());
    }
    else
    {
        ui->Elv_Label_GestionInfo->setText("Ajout: ERROR");
    }
}
void MainWindow::on_Elv_push_Modifier_clicked()
{
    int ID=ui->Elv_line_ID->text().toInt();
    QString NOM=ui->Elv_line_Nom->text();
    QString PRENOM=ui->Elv_line_Prenom->text();
    int NUMTEL=ui->Elv_line_Numtel->text().toInt();
    QString EMAIL=ui->Elv_line_Email->text();
    QDate DATE_DE_NAISSANCE=ui->Elv_date_DDN->date();
    QString GENDER=ui->Elv_combo_Gender->currentText();
    eleves ELV(ID,NOM,PRENOM,NUMTEL,EMAIL,DATE_DE_NAISSANCE,GENDER);
    bool test=ENS.modifier();
    if(test)
    {
        ui->Elv_Label_GestionInfo->setText("Modification Effectué");
        ui->Elv_TableView->setModel(ELV.afficher());
        ui->Elv_combo_ID->setModel (ELV.afficher_id());
        ELV.write(ELV.time(),"ELEVES: Modification effectué");
        ui->Elv_textbrowser->setText(ELV.read());
    }
    else
    {
        ui->Elv_Label_GestionInfo->setText("Modification: ERROR");
    }
}
void MainWindow::on_Elv_push_Supprimer_clicked()
{
    eleves ELV;
    ELV.setid(ui->Elv_combo_ID->currentText().toInt());
    bool test=ELV.supprimer(ELV.getid());
    if(test)
    {
        ui->Elv_Label_GestionInfo->setText("Suppression effectué");
        ui->Elv_TableView->setModel(ELV.afficher());
        ui->Elv_combo_ID->setModel(ELV.afficher_id());
        ELV.write(ELV.time(),"ELEVES: Supression effectuée");
        ui->Elv_textbrowser->setText(ELV.read());
    }
    else
    {
        ui->Elv_Label_GestionInfo->setText("Suppression: ERROR");
    }
}
void MainWindow::on_Elv_push_TriID_clicked()
{
    ui->Elv_Label_ListeInfo->setText("Tri par ID effectué");
    ui->Elv_TableView->setModel(ELV.tri_id());
}
void MainWindow::on_Elv_push_TriNom_clicked()
{
    ui->Elv_Label_ListeInfo->setText("Tri par NOM effectué");
    ui->Elv_TableView->setModel(ELV.tri_nom());
}
void MainWindow::on_Elv_push_TriEPrenom_clicked()
{
    ui->Elv_Label_ListeInfo->setText("Tri par PRENOM effectué");
    ui->Elv_TableView->setModel(ELV.tri_prenom());
}
void MainWindow::on_Elv_combo_ID_currentIndexChanged(int )
{
    int id=ui->Elv_combo_ID->currentText().toInt();
    QString id_1=QString::number(id);
    QSqlQuery query;
    query.prepare("SELECT * FROM ELEVES where ID='"+id_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->Elv_line_ID->setText(query.value(0).toString()) ;
            ui->Elv_line_Nom->setText(query.value(1).toString()) ;
            ui->Elv_line_Prenom->setText(query.value(2).toString()) ;
            ui->Elv_line_Numtel->setText(query.value(3).toString()) ;
            ui->Elv_line_Email->setText(query.value(4).toString()) ;
            ui->Elv_date_DDN->setDate(query.value(5).toDate()) ;
            ui->Elv_combo_Gender->setCurrentText(query.value(6).toString()) ;
        }
    }
    else
    {
        ui->Elv_Label_GestionInfo->setText("Chargement: ERROR");
    }
}
void MainWindow::Elv_statistiques(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery qry;
    qry.exec("SELECT DATE_DE_NAISSANCE FROM ELEVES");
    while (qry.next())
    {
        QDate birthDate = qry.value(0).toDate();
        QDate currentDate = QDate::currentDate();
        int age = birthDate.daysTo(currentDate) / 365;
        QString ageLabel = QString::number(age);
        if (!labels->contains(ageLabel)) {
            labels->append(ageLabel);
            ticks->append(labels->size());
        }
    }
}
void MainWindow::on_Elv_push_UpdateStats_clicked()
{
    /***** Background *****/
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(255, 255, 255));
    ui->Elv_Plot->setBackground(QBrush(gradient));
    /***** Axe des abscisses *****/
    QVector<double> ageTicks;
    QVector<QString> ageLabels;
    Elv_statistiques(&ageTicks, &ageLabels);
    QSharedPointer<QCPAxisTickerText> ageTicker(new QCPAxisTickerText);
    ageTicker->addTicks(ageTicks, ageLabels);
    ui->Elv_Plot->xAxis->setTicker(ageTicker);
    ui->Elv_Plot->xAxis->setTickLabelRotation(60);
    ui->Elv_Plot->xAxis->setSubTicks(false);
    ui->Elv_Plot->xAxis->setLabel("Âge");
    ui->Elv_Plot->xAxis->setTickLength(0, 4);
    ui->Elv_Plot->xAxis->setRange(0, ageLabels.size() + 1);
    ui->Elv_Plot->xAxis->setBasePen(QPen(Qt::black));
    ui->Elv_Plot->xAxis->setTickPen(QPen(Qt::black));
    ui->Elv_Plot->xAxis->grid()->setVisible(true);
    ui->Elv_Plot->xAxis->grid()->setPen(QPen(QColor(177,177,177), 0, Qt::DotLine));
    ui->Elv_Plot->xAxis->setTickLabelColor(Qt::black);
    ui->Elv_Plot->xAxis->setLabelColor(Qt::black);
    /***** Axe des ordonnées *****/
    ui->Elv_Plot->yAxis->setRange(0, 20);
    ui->Elv_Plot->yAxis->setPadding(1);
    ui->Elv_Plot->yAxis->setLabel(" Nbr. Eleves");
    ui->Elv_Plot->yAxis->setBasePen(QPen(Qt::black));
    ui->Elv_Plot->yAxis->setTickPen(QPen(Qt::black));
    QSharedPointer<QCPAxisTicker> customTicker(new QCPAxisTicker);
    customTicker->setTickCount(15);
    ui->Elv_Plot->yAxis->setTicker(customTicker);
    ui->Elv_Plot->yAxis->setTickLabelColor(Qt::black);
    ui->Elv_Plot->yAxis->setLabelColor(Qt::black);
    ui->Elv_Plot->yAxis->grid()->setPen(QPen(QColor(177, 177, 177), 0, Qt::SolidLine));
    ui->Elv_Plot->yAxis->grid()->setSubGridPen(QPen(QColor(177, 177, 177), 0, Qt::DotLine));
    QVector<double> ageData(ageLabels.size(), 0);
    QSqlQuery q2("SELECT DATE_DE_NAISSANCE FROM ELEVES");
    while (q2.next())
    {
        QDate birthDate = q2.value(0).toDate();
        QDate currentDate = QDate::currentDate();
        int age = birthDate.daysTo(currentDate) / 365; // Approximate age calculation
        QString ageLabel = QString::number(age);
        int ageIndex = ageLabels.indexOf(ageLabel);
        if (ageIndex != -1) {
            ageData[ageIndex]++;
        }
    }
    A->setData(ageTicks, ageData);
    ui->Elv_Plot->legend->setVisible(true);
    ui->Elv_Plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->Elv_Plot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->Elv_Plot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(8);
    ui->Elv_Plot->legend->setFont(legendFont);
    ui->Elv_Plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
void MainWindow::on_envoyer_dialog_2_clicked()
{
    QString status;
    Smtp* smtp = new Smtp("automaillingqt@gmail.com", "xkrseghkxzkxclvr", "smtp.gmail.com", 465); //smtp.gmail.com
    smtp->sendMail("automaillingqt@gmail.com", ui->recipient_2->text() , ui->subjectLineEdit_2->text() ,ui->message_2->toPlainText());
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}
void MainWindow::on_Elv_push_Return_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Elv_push_SupprimerTextBrowser_clicked()
{
    ELV.clearh();
    ui->Elv_textbrowser->setText(ELV.read());
}

void MainWindow::on_Elv_push_ExportPDF_clicked()
{
    QPdfWriter pdf("C:/Users/zeidc/Desktop/ProjetCPP/ListeElv.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));
    QPixmap pixmap(":/png/resources/elv.png");
    painter.drawPixmap(QRect(100, 400, 2000, 2000), pixmap);
    painter.drawText(3000,1500,"LISTE DES ELEVES");
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 50));
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"ID");
    painter.drawText(1800,3300,"NOM");
    painter.drawText(2800,3300,"PRENOM");
    painter.drawText(3800,3300,"NUMTEL");
    painter.drawText(4800,3300,"DATE DE NAISSANCE");
    painter.drawText(6700,3300,"EMAIL");
    painter.drawText(7700,3300,"GENDER");
    QSqlQuery query;
    query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti=localtime(&tt);
    asctime(ti);
    painter.drawText(500,300, asctime(ti));
    query.prepare("select ID,NOM,PRENOM,NUMTEL,DATE_DE_NAISSANCE,EMAIL,GENDER from ELEVES");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(1800,i,query.value(1).toString());
        painter.drawText(2800,i,query.value(2).toString());
        painter.drawText(3800,i,query.value(3).toString());
        painter.drawText(4800,i,query.value(4).toString());
        painter.drawText(6700,i,query.value(5).toString());
        painter.drawText(7700,i,query.value(6).toString());
        i = i +500;
    }
    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/zeidc/Desktop/ProjetCPP/ListeELV.pdf"));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}
