#include "useradmin.h"
#include "ui_useradmin.h"
using namespace std;
#include <iostream>

UserAdmin::UserAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserAdmin)
{
    ui->setupUi(this);
    setWindowTitle("User Admin");
    //    ui->ListTableWidget->setRowCount(0);
    //    ui->ListTableWidget->setColumnCount(5);
    //    ui->ListTableWidget->setHorizontalHeaderLabels(QStringList() << "ID" << "Power" << "Radius" << "X Coord" << "Y Coord");
    //set buttons to disabled until db is initialised
    //    ui->addAllBtn->setDisabled(true);
    //    ui->addBtnManual->setDisabled(true);
    //connect(connection, SIGNAL(connEstablished(bool)), this, SLOT(enableButtons(bool)));
    cout << "User dialog object created." << endl;
}

UserAdmin::~UserAdmin()
{
    delete ui;
    cout << "User dialog object destroyed." << endl;
}

QList<QStringList> columns_2;

CreateTab_2::CreateTab_2(QWidget *parent) : QWidget(parent) { }
ModifyTab_2::ModifyTab_2(QWidget *parent) : QWidget(parent) { }
ListTab_2::ListTab_2(QWidget *parent) : QWidget(parent) {}

//-------------------Create Tab----------------------
void UserAdmin::on_addBtnManual_2_clicked()
{
    //return descriptive error when tried to click/add without db conn
    int xin = ui->xInput_2->text().toInt();
    int yin = ui->yInput_2->text().toInt();
    double pin = ui->powerInput_2->text().toDouble();
    int rin = ui->radiusInput_2->text().toInt();
    User *user = new User(rin, xin, yin, pin);

    //handle User going to same location as user but later

    Database connection;

    QSqlError cerror = connection.addItem("U", pin, rin, xin, yin);
    if (cerror.type() != QSqlError::NoError) {
        QMessageBox::critical(this,"Error","Unable to add to the database: "+cerror.text()+" ");
    }
    else{
        QMessageBox::information(this,"Record added","Successfully added to the database");
        ui->powerInput_2->setText("");
        ui->xInput_2->setText("");
        ui->yInput_2->setText("");
    }
}

void UserAdmin::on_clearBtnCreate_2_clicked()
{
    ui->powerInput_2->setText("");
    ui->xInput_2->setText("");
    ui->yInput_2->setText("");
}

//-----------------Create Tab 2----------------------

void UserAdmin::on_browseFile_2_clicked()
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
        columns_2 << line.split(',');
        //        }
    } while (!line.isNull());

    //check if header has same number of columns_2 as data
    //    if(headers.length()!=columns_2.length()||headers.length()!=3){
    //        QMessageBox::critical(this,"Error","Wrong number of columns_2 in file");
    //        return;
    //    }

    //    if (headers!=nullptr){ ui->fileTableWidget->setHorizontalHeaderLabels(headers); }
    //    else {
    ui->tableWidget_2->model()->setHeaderData(1,Qt::Horizontal,QStringLiteral("Power"));
    ui->tableWidget_2->model()->setHeaderData(2,Qt::Horizontal,QStringLiteral("Radius"));
    ui->tableWidget_2->model()->setHeaderData(3,Qt::Horizontal,QStringLiteral("X Coord"));
    ui->tableWidget_2->model()->setHeaderData(4,Qt::Horizontal,QStringLiteral("Y Coord"));
    //    }
    ui->tableWidget_2->setRowCount(columns_2.size());
    ui->tableWidget_2->setColumnCount(columns_2[0].size());

    for (int i = 0; i<columns_2.size(); ++i){
        for (int j = 0; j<columns_2[i].size(); ++j){
            ui->tableWidget_2->setItem(i,j,new QTableWidgetItem(columns_2[i][j]));
        }
    }
}

void UserAdmin::on_addAllBtn_2_clicked()
{
    //return descriptive error when tried to click/add without db conn

    QVariantList xin;
    QVariantList yin;
    QVariantList pin;
    QVariantList radiusList;

    //action based on number of columns_2?
    for (int i = 0; i<columns_2.size()-1; ++i){
        for (int j = 0; j<columns_2[i].size(); ++j){
            switch(j) {
            case 0 :
                radiusList<<(columns_2[i][j]);
                break;
            case 1 :
                pin<<(columns_2[i][j]);
                break;
            case 2 :
                xin<<(columns_2[i][j]);
                break;
            case 3 :
                yin<<(columns_2[i][j]);
                break;
            default :
                cout << "Invalid item" << endl;
            }
        }
        //      User *User = new User( xin.last().toDouble(), yin.at(j).toInt(), pin.at(j).toInt()); //?? fix TODO
    }

    //handle User going to same location as user but later

    Database connection;

    QSqlError cerror = connection.addBulk("U", pin, radiusList, xin, yin);
    if (cerror.type() != QSqlError::NoError) {
        QMessageBox::critical(this,"Error","Unable to add to the database: "+cerror.text()+" ");
    }
    else{
        QMessageBox::information(this,"Records added","Successfully added to the database");
        ui->tableWidget_2->clear();
    }

}

void UserAdmin::on_toolBox_2_currentChanged(int index)
{
    foreach(QLineEdit* lineEd, findChildren<QLineEdit*>()) { lineEd->clear(); }
    ui->tableWidget_2->clear();
}

void UserAdmin::on_clearFileBtn_2_clicked()
{
    ui->tableWidget_2->clear();
}

//-------------------Modify Tab----------------------
void UserAdmin::on_ModifyBtn_2_clicked()
{
    Database connection;
    QString id = ui->userDropDown->currentText();
    QString pin = ui->powerInputModify_2->text();
    QString rin = ui->powerInputModify_2->text();
    QString xin = ui->xInputModify_2->text();
    QString yin = ui->yInputModify_2->text();

    QSqlError cerror = connection.addModifiedItem(id, pin, rin, xin, yin);
    if (cerror.type() != QSqlError::NoError) {
        QMessageBox::critical(this,"Error","Unable to update item in database: "+cerror.text()+" ");
    }
    else{
        QMessageBox::information(this,"Record updated","Successfully updated the record");
        ui->tableWidget_2->clear();
    }

    ui->powerInputModify_2->clear();
    ui->radiusInputModify_2->clear();
    ui->xInputModify_2->clear();
    ui->yInputModify_2->clear();
}

void UserAdmin::on_userDropDown_currentIndexChanged(const QString &arg1) {
    QString uID = ui->userDropDown->currentText();
    Database connection;

    QSqlQuery query = connection.getRow(uID);
    if (query.exec()){
        while(query.next()){
            ui->powerInputModify_2->setText(query.value(1).toString());
            ui->radiusInputModify_2->setText(query.value(2).toString());
            ui->xInputModify_2->setText(query.value(3).toString());
            ui->yInputModify_2->setText(query.value(4).toString());
        }
    } else{QMessageBox::critical(this,"Error","Unable to fetch data from database: "+query.lastError().text());
    }

}

void UserAdmin::on_tabWidget_2_currentChanged(int index)
{
    //set placeholder item in dropdown?
    //only get user devices
    Database connection;
    QSqlQueryModel *model = new QSqlQueryModel();
    if(index==1){
        model->setQuery(connection.getIDs("U"));
        ui->userDropDown->setModel(model);
    }
    if(index==2){
        model->setQuery(connection.getAllOfType("U"));
        ui->uListView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->uListView->setModel(model);
    }
}
