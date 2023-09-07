#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "enseignants.h"
#include "eleves.h"
#include "qcustomplot.h"
#include "connexion.h"
#include "smtp.h"
#include "chatboxconnectiondialog.h"
#include <QMainWindow>
#include <QSqlError>
#include <QSqlQuery>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QRegExpValidator>
#include <QTcpSocket>
#include <QTextStream>
#include <QPixmap>
#include <QWidget>
#include <QVBoxLayout>
QT_CHARTS_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class QTcpSocket;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QString,QMainWindow *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Login_push_Login_clicked();
    void on_Login_check_PassShowHide_clicked();
    void on_Menu_Ens_clicked();
    void on_Menu_Elv_clicked();
    void on_Menu_Return_clicked();
    void on_Menu_Quit_clicked();

    void on_Ens_push_Ajouter_clicked();
    void on_Ens_push_Modifier_clicked();
    void on_Ens_push_Supprimer_clicked();
    void on_Ens_push_TriCIN_clicked();
    void on_Ens_push_TriNom_clicked();
    void on_Ens_push_TriPrenom_clicked();
    void on_Ens_combo_CIN_currentIndexChanged(int index);
    void on_Ens_line_Recherche_textChanged(const QString &arg1);
    void Ens_choix_pie();
    void on_Ens_push_ExportPDF_clicked();
    void on_Ens_push_UpdateStats_clicked();
    void on_Ens_push_Send_clicked();
    void on_Ens_push_Bind_clicked();
    void on_Ens_push_Return_clicked();
    void on_Ens_push_SupprimerTextBrowser_clicked();

    void on_Elv_push_Ajouter_clicked();
    void on_Elv_push_Modifier_clicked();
    void on_Elv_push_Supprimer_clicked();
    void on_Elv_push_TriID_clicked();
    void on_Elv_push_TriNom_clicked();
    void on_Elv_push_TriEPrenom_clicked();
    void on_Elv_combo_ID_currentIndexChanged(int index);
    void Elv_statistiques(QVector<double>* ticks,QVector<QString> *labels);
    void on_Elv_push_UpdateStats_clicked();
    void on_envoyer_dialog_2_clicked();
    void on_Elv_push_Return_clicked();
    void on_Elv_push_SupprimerTextBrowser_clicked();

    void on_Elv_push_ExportPDF_clicked();

private:
    Ui::MainWindow *ui;
    QCPBars *A;
    enseignants ENS;
    eleves ELV;
    connexion c;
    QTcpSocket *nSocket;
    QString ConnectedUser;
    int EleveAge;
};
#endif // MAINWINDOW_H
