#include "databasedialog.h"
#include "ui_databasedialog.h"

DatabaseDialog::DatabaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseDialog)
{
    ui->setupUi(this);
    setWindowTitle("Database Admin");
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint);
    ui->dropDbBtn->setDisabled(true);
}

DatabaseDialog::~DatabaseDialog()
{
    delete ui;
}

void DatabaseDialog::on_createDbBtn_clicked()
{
    Database *dbase = nullptr;
    dbase = new Database();
    if (!dbase){
        ui->dbLabel->setText("Database setup failed");
        return;
    }
    else {
        ui->dbLabel->setText("Database setup successful");
        ui->dbTable->setColumnCount(5);
        ui->dbTable->model()->setHeaderData(0,Qt::Horizontal,QStringLiteral("ID"));
        ui->dbTable->model()->setHeaderData(1,Qt::Horizontal,QStringLiteral("Power"));
        ui->dbTable->model()->setHeaderData(2,Qt::Horizontal,QStringLiteral("Radius"));
        ui->dbTable->model()->setHeaderData(3,Qt::Horizontal,QStringLiteral("X Coord"));
        ui->dbTable->model()->setHeaderData(4,Qt::Horizontal,QStringLiteral("Y Coord"));
        ui->dbTable->update();
        ui->createDbBtn->setDisabled(true);
        ui->dropDbBtn->setEnabled(true);
    }
}

void DatabaseDialog::on_dropDbBtn_clicked()
{
    dbase.~Database();
//    if (dbase){
//        ui->dbLabel->setText("Database drop failed");
//        return;
//    }
//    else {
        ui->dbLabel->setText("Fix this shit");
        ui->dbTable->clear();
        ui->dbTable->update();
        ui->createDbBtn->setEnabled(true);
        ui->dropDbBtn->setDisabled(true);
//    }
}

// add change event listener for database updates towards table
//threads maybe?
//
