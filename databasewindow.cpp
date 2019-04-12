#include "databasewindow.h"
#include "ui_databasewindow.h"
#include "helpdialog.h"
#include <QtSql>
#include <iostream>
using namespace std;

DatabaseWindow::DatabaseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DatabaseWindow)
{
    ui->setupUi(this);
    ui->closeDbBtn->setDisabled(true);
    ui->refreshBtn->setDisabled(true);
    setWindowTitle("White space database for frequency band 600MHz");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    //for convenience:
    ui->unameLineEdit->setText("root");
    ui->pwLineEdit->setText("root");
    ui->addrLineEdit->setText("127.0.0.1");
    ui->portLineEdit->setText("3306");
    ui->dbLineEdit->setText("whitespacedb");

    cout<<"DatabaseWindow object created."<<endl;
}

DatabaseWindow::~DatabaseWindow()
{
    cout<<"DatabaseWindow object removed."<<endl;
    delete ui;
}

Database *dbase;

void DatabaseWindow::on_connectDbBtn_clicked()
{
    host = ui->addrLineEdit->text();
    dbname = ui->dbLineEdit->text();
    uname = ui->unameLineEdit->text();
    port = ui->portLineEdit->text().toInt();
    pw = ui->pwLineEdit->text();

    QSqlError cerror = dbase.setupConnection(host, dbname, uname, port, pw, this);

    if (cerror.type() != QSqlError::NoError) {
        QMessageBox::critical(this,"Error","Unable to connect to the database: "+cerror.text());
        ui->statusLbl->setText("Connection failed");
    }
    else {
        QMessageBox::information(this,"Connected","Successfully connected to the database");
        ui->statusLbl->setText("Connection established");
        ui->closeDbBtn->setEnabled(true);
        ui->refreshBtn->setEnabled(true);
        ui->connectDbBtn->setDisabled(true);
    }

    //thank mary, joseph and baby jesus, this finally works https://stackoverflow.com/questions/24221466/qmysql-driver-not-loaded-on-windows

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(dbase.setupModel());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);

    emit connEstablished(true);
}

void DatabaseWindow::on_closeDbBtn_clicked(){
    ui->tableView->setModel(nullptr);

    dbase.closeConnection(this);
    ui->statusLbl->setText("Connection closed");

    ui->connectDbBtn->setEnabled(true);
    ui->closeDbBtn->setDisabled(true);
    ui->refreshBtn->setDisabled(true);

    emit connEstablished(false);
}

void DatabaseWindow::on_refreshBtn_clicked()
{
    QSqlError cerror = dbase.setupConnection(host, dbname, uname, port, pw, this);

    if (cerror.type() != QSqlError::NoError) {
        QMessageBox::critical(this,"Error","Unable to connect to the database: "+cerror.text());
        ui->statusLbl->setText("Refresh failed");
    }
    else {
        ui->statusLbl->setText("Database reloaded");
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(dbase.setupModel());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
}


void DatabaseWindow::on_helpBtn_clicked()
{
    QString helpText = "Write this, Aidan, I'm running out of insults.";
    HelpDialog helpPopUp;
    helpPopUp.setHelpText(helpText);
    helpPopUp.setModal(true);
    helpPopUp.exec();
}
