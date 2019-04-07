
#include "transmitteradmin.h"
#include "ui_transmitteradmin.h"
using namespace std;
#include <iostream>

TransmitterAdmin::TransmitterAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransmitterAdmin)
{
    ui->setupUi(this);
    setWindowTitle("Transmitter Admin");
    //    ui->ListTableWidget->setRowCount(0);
    //    ui->ListTableWidget->setColumnCount(5);
    //    ui->ListTableWidget->setHorizontalHeaderLabels(QStringList() << "ID" << "Power" << "Radius" << "X Coord" << "Y Coord");
    //set buttons to disabled until db is initialised
    //    ui->addAllBtn->setDisabled(true);
    //    ui->addBtnManual->setDisabled(true);
    //connect(connection, SIGNAL(connEstablished(bool)), this, SLOT(enableButtons(bool)));
    cout << "Transmitter dialog object created." << endl;
}

TransmitterAdmin::~TransmitterAdmin()
{
    delete ui;
    cout << "Transmitter dialog object destroyed." << endl;
}

QList<QStringList> columns;

CreateTab::CreateTab(QWidget *parent) : QWidget(parent) { }
ModifyTab::ModifyTab(QWidget *parent) : QWidget(parent) { }
ListTab::ListTab(QWidget *parent) : QWidget(parent) {}

//-------------------Create Tab----------------------
void TransmitterAdmin::on_addBtnManual_clicked()
{
    //return descriptive error when tried to click/add without db conn
    int xin = ui->xInput->text().toInt();
    int yin = ui->yInput->text().toInt();
    double pin = ui->powerInput->text().toDouble();
    Transmitter *transmitter = new Transmitter(xin, yin, pin);

    //handle transmitter going to same location as user but later

    Database connection;

    QSqlError cerror = connection.addItem("T", pin, transmitter->getRadius(), xin, yin);
    if (cerror.type() != QSqlError::NoError) {
        QMessageBox::critical(this,"Error","Unable to add to the database: "+cerror.text()+" ");
    }
    else{
        QMessageBox::information(this,"Record added","Successfully added to the database");
        ui->powerInput->setText("");
        ui->xInput->setText("");
        ui->yInput->setText("");
    }
}

void TransmitterAdmin::on_clearBtnCreate_clicked()
{
    ui->powerInput->setText("");
    ui->xInput->setText("");
    ui->yInput->setText("");
}

//-----------------Create Tab 2----------------------

void TransmitterAdmin::on_browseFile_clicked()
{

    //    QList<QStringList> headers;
    //    bool firstCheck = true;

    QString line;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"C://","All files (*.*);;Text Files (*.txt);;CSV Files(*.csv)");
    QFile file(fileName);

    QTextStream ipLine(&file);
    if (!file.open(QIODevice::ReadOnly)){
        qDebug()<<file.errorString();
        return;
    }

    do{
        //        if (firstCheck){
        //            line = ipLine.readLine();
        //            headers << line.split(',');

        //            //check if headers are right, and if not, either error out or put line back to first line
        //            int numCount = 0;
        //            while (headers.hasNext()) {
        //                QString current = headers.next();
        //                QRegExp re("\\d*");
        //                if (re.exactMatch(current)){ numCount++;}
        //                //https://stackoverflow.com/questions/8791380/how-to-detect-if-a-qstring-is-made-up-of-all-numeric-characters
        //            }

        //            firstCheck = false;
        //        }
        //        else{
        line = ipLine.readLine();
        columns << line.split(',');
        //        }
    } while (!line.isNull());

    //check if header has same number of columns as data
    //    if(headers.length()!=columns.length()||headers.length()!=3){
    //        QMessageBox::critical(this,"Error","Wrong number of columns in file");
    //        return;
    //    }

    //    if (headers!=nullptr){ ui->fileTableWidget->setHorizontalHeaderLabels(headers); }
    //    else {
    ui->fileTableWidget->model()->setHeaderData(1,Qt::Horizontal,QStringLiteral("Power"));
    ui->fileTableWidget->model()->setHeaderData(3,Qt::Horizontal,QStringLiteral("X Coord"));
    ui->fileTableWidget->model()->setHeaderData(4,Qt::Horizontal,QStringLiteral("Y Coord"));
    //    }
    ui->fileTableWidget->setRowCount(columns.size());
    ui->fileTableWidget->setColumnCount(columns[0].size());

    for (int i = 0; i<columns.size(); ++i){
        for (int j = 0; j<columns[i].size(); ++j){
            ui->fileTableWidget->setItem(i,j,new QTableWidgetItem(columns[i][j]));
        }
    }
}

void TransmitterAdmin::on_addAllBtn_clicked()
{
    //return descriptive error when tried to click/add without db conn

    QVariantList xin;
    QVariantList yin;
    QVariantList pin;
    QVariantList radiusList;

    //action based on number of columns?
    for (int i = 0; i<columns.size()-1; ++i){
        for (int j = 0; j<columns[i].size(); ++j){
            switch(j) {
            case 0 :
                pin<<(columns[i][j]);
                break;
            case 1 :
                xin<<(columns[i][j]);
                break;
            case 2 :
                yin<<(columns[i][j]);
                break;
            default :
                cout << "Invalid item" << endl;
            }
        }
//      Transmitter *transmitter = new Transmitter( xin.last().toDouble(), yin.at(j).toInt(), pin.at(j).toInt()); //?? fix TODO
    }

    for(int i = 0; i<pin.length(); i++){
        radiusList<<(6);
    }

    //handle transmitter going to same location as user but later

    Database connection;

    QSqlError cerror = connection.addBulk("T", pin, radiusList, xin, yin);
    if (cerror.type() != QSqlError::NoError) {
        QMessageBox::critical(this,"Error","Unable to add to the database: "+cerror.text()+" ");
    }
    else{
        QMessageBox::information(this,"Records added","Successfully added to the database");
        ui->fileTableWidget->clear();
    }

}

void TransmitterAdmin::on_toolBox_currentChanged(int index)
{
    foreach(QLineEdit* lineEd, findChildren<QLineEdit*>()) { lineEd->clear(); }
    ui->fileTableWidget->clear();
}

void TransmitterAdmin::on_clearFileBtn_clicked()
{
    ui->fileTableWidget->clear();
}

//-------------------Modify Tab----------------------
void TransmitterAdmin::on_ModifyBtn_clicked()
{
    Database connection;
    QString id = ui->tmitDropDown->currentText();
    QString pin = ui->powerInputModify->text();
    QString xin = ui->xInputModify->text();
    QString yin = ui->yInputModify->text();

    QSqlError cerror = connection.addModifiedItem(id, pin, xin, yin);
    if (cerror.type() != QSqlError::NoError) {
        QMessageBox::critical(this,"Error","Unable to update item in database: "+cerror.text()+" ");
    }
    else{
        QMessageBox::information(this,"Record updated","Successfully updated the record");
        ui->fileTableWidget->clear();
    }

    ui->powerInputModify->clear();
    ui->xInputModify->clear();
    ui->yInputModify->clear();
}

void TransmitterAdmin::on_tmitDropDown_currentIndexChanged(const QString &arg1)
{
    QString tmitID = ui->tmitDropDown->currentText();
    Database connection;

    QSqlQuery query = connection.getRow(tmitID);
    if (query.exec()){
        while(query.next()){
            ui->powerInputModify->setText(query.value(1).toString());
            ui->xInputModify->setText(query.value(3).toString());
            ui->yInputModify->setText(query.value(4).toString());
        }
    } else{QMessageBox::critical(this,"Error","Unable to fetch data from database: "+query.lastError().text());
    }

}

void TransmitterAdmin::on_tabWidget_currentChanged(int index)
{
    //set placeholder item in dropdown?

    Database connection;
    QSqlQueryModel *model = new QSqlQueryModel();
    if(index==1){
        model->setQuery(connection.getIDs());
        ui->tmitDropDown->setModel(model);
    }
    if(index==2){
        model->setQuery(connection.setupModel());
        ui->ListTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->ListTableView->setModel(model);
    }
}
