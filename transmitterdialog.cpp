#include "transmitterdialog.h"
#include "transmitter.h"
#include "database.h"
#include "ui_transmitterdialog.h"

TransmitterDialog::TransmitterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransmitterDialog)
{
    ui->setupUi(this);
    setWindowTitle("Transmitter Admin");
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint);
}

TransmitterDialog::~TransmitterDialog()
{
    delete ui;
}

Database db;

CreateTab::CreateTab(QWidget *parent) : QWidget(parent) { }
ModifyTab::ModifyTab(QWidget *parent) : QWidget(parent) { }
ListTab::ListTab(QWidget *parent) : QWidget(parent)
{
    //add event listener to fill this in when transmitter is added
}

//-------------------Create Tab----------------------
void TransmitterDialog::on_addBtnManual_clicked()
{
    int xin = ui->xInput->text().toInt();
    int yin = ui->yInput->text().toInt();
    double pin = ui->yInput->text().toDouble();
    Transmitter transmitter(xin, yin, pin);

    db.addDevice(transmitter,'t');

    //block user to add to db before a transmitter is in
    //how to handle transmitter going to same location as user but later?

    ui->powerInput->setText("");
    ui->xInput->setText("");
    ui->yInput->setText("");
}

void TransmitterDialog::on_clearBtnCreate_clicked()
{
    ui->powerInput->setText("");
    ui->xInput->setText("");
    ui->yInput->setText("");
}

//-----------------Create Tab 2----------------------

void TransmitterDialog::on_browseFile_clicked()
{
    QList<QStringList> columns;
    QString line;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"C://","All files (*.*);;Text Files (*.txt);;CSV Files(*.csv)");
    QFile file(fileName);
    QTextStream ipLine(&file);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug()<<file.errorString();
        return;
    }

    do{
        line = ipLine.readLine();
        columns << line.split(',');
    } while (!line.isNull());

    ui->tableWidget->setRowCount(columns.size());
    ui->tableWidget->setColumnCount(columns[0].size());

    for (int i = 0; i<columns.size(); ++i){
        for (int j = 0; j<columns[i].size(); ++j){
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(columns[i][j]));
        }
    }
}

void TransmitterDialog::on_fileNameEdit_returnPressed()
{
    QList<QStringList> columns;
    QString line;
    QString fileName = ui->fileNameEdit->text();
    QFile file(fileName);
    QTextStream ipLine(&file);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug()<<file.errorString();
        return;
    }

    do{
        line = ipLine.readLine();
        columns << line.split(',');
    } while (!line.isNull());

    ui->tableWidget->setRowCount(columns.size());
    ui->tableWidget->setColumnCount(columns[0].size());

    for (int i = 0; i<columns.size(); ++i){
        for (int j = 0; j<columns[i].size(); ++j){
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(columns[i][j]));
        }

    }
}

void TransmitterDialog::on_addAllBtn_clicked()
{
    //add to db
    ui->fileNameEdit->clear();
    ui->tableWidget->clear();
}

void TransmitterDialog::on_toolBox_currentChanged(int index)
{
    foreach(QLineEdit* lineEd, findChildren<QLineEdit*>()) {
        lineEd->clear();
    }
    ui->tableWidget->clear();
}

void TransmitterDialog::on_clearFileBtn_clicked()
{
    ui->fileNameEdit->clear();
    ui->tableWidget->clear();
}

//-------------------Modify Tab----------------------
void TransmitterDialog::on_ModifyBtn_clicked()
{
    //Transmitter
    //clear input lineedits
}

void TransmitterDialog::on_tmitDropDown_currentIndexChanged(int index)
{

    //refill line edits with new element
    //connect db population to filling this in
}
