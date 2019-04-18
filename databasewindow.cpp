/**
 * @package QTWhiteSpaceManager
 * @module DatabaseWindow.cpp
 * The source file of the class detemining the operations of the Database GUI.
 * ----------------------------
 * Updates
 * @date: 18/04/2019
 * @abstract: Added comments, indented code
 * @author:
 */

#include "databasewindow.h"
#include "ui_databasewindow.h"
#include "helpdialog.h"
#include <QtSql>
#include <iostream>
using namespace std;


/**
  * Constructor for a DatabaseWindow object.
  * @param parent: the parent of the DatabaseWindow
  */
DatabaseWindow::DatabaseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DatabaseWindow)
{
    ui->setupUi(this);
    ui->closeDbBtn->setDisabled(true);
    ui->refreshBtn->setDisabled(true);
    setWindowTitle("White space database for frequency band 600MHz");

    //uniform look across all GUIs
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    //for convenience we can prefill the fields, but they are editable:
//    ui->unameLineEdit->setText("root");
//    ui->pwLineEdit->setText("root");
//    ui->addrLineEdit->setText("127.0.0.1");
//    ui->portLineEdit->setText("3306");
//    ui->dbLineEdit->setText("whitespacedb");

    cout<<"DatabaseWindow object created."<<endl;
}

/**
 * Destructor of the DatabaseWindow object.
 */
DatabaseWindow::~DatabaseWindow()
{
    cout<<"DatabaseWindow object removed."<<endl;
    delete ui;
}

Database *dbase;
QString helpDbText = ("This is the database administrator window.\n To connect to a database, input values to be used to set up the connection.\n Wrong values will produce errors.\nClose the connection at any time using the Close Connection button.\n Refresh the database with the refresh button.\n");

/**
 * A function to set up the connection to the MySql database.
 */
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

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(dbase.setupModel());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
    ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
}

/**
 *  A function to break down the connection to the database.
 */
void DatabaseWindow::on_closeDbBtn_clicked(){
    ui->tableView->setModel(nullptr);

    dbase.closeConnection(this);
    ui->statusLbl->setText("Connection closed");

    ui->connectDbBtn->setEnabled(true);
    ui->closeDbBtn->setDisabled(true);
    ui->refreshBtn->setDisabled(true);

    emit connEstablished(false);
}

/**
 * Function to refresh the table containing the database table.
 */
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

/**
 * The function to call the Help button popup window.
 */
void DatabaseWindow::on_helpBtn_clicked()
{
    HelpDialog helpPopUp;
    helpPopUp.setHelpText(helpDbText);
    helpPopUp.setModal(true);
    helpPopUp.exec();
}
