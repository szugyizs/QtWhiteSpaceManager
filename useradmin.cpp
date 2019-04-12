#include "useradmin.h"
#include "ui_useradmin.h"
#include "helpdialog.h"
using namespace std;
#include <iostream>
#include <QCheckBox>

UserAdmin::UserAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserAdmin)
{
    ui->setupUi(this);
    setWindowTitle("User Admin");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
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
ListTab_2::ListTab_2(QWidget *parent) : QWidget(parent) { }
RemoveTab_2::RemoveTab_2(QWidget *parent) : QWidget(parent) { }

//-------------------Create Tab----------------------
void UserAdmin::on_addBtnManual_2_clicked()
{
    int xin = ui->xInput_2->text().toInt();
    int yin = ui->yInput_2->text().toInt();
    int rin = ui->radiusInput->text().toInt();
    //User *user = new User(rin, xin, yin);

    Database connection;
//    QVariantList addCheck = connection.addItem("U", rin, xin, yin); //change to Device type

//    QString cerror = addCheck.pop_back();
//    if (cerror != "") {
//        QMessageBox::critical(this,"Error","Unable to add to the database: "+cerror.toStdString());
//        ui->ustatusLabel2->setText("Error adding to database");
//        return;
//    }
//    else{
//        QMessageBox::information(this,"Record added","Successfully added to the database");
//        ui->radiusInput->setText("");
//        ui->xInput_2->setText("");
//        ui->yInput_2->setText("");
//        ui->ustatusLabel2->setText("Record added");
//    }
//    ui->tmitDistLbl->setText("The closest transmitter is "+addCheck.pop_front()+" units away, at ("+addCheck.pop_front()+","+addCheck.pop_front()+").");
//    ui->assignedPowLbl->setText("The power that this user can transmit on is "+addCheck.pop_front()+"W.");
}

void UserAdmin::on_clearBtnCreate_2_clicked()
{
    ui->radiusInput->setText("");
    ui->xInput_2->setText("");
    ui->yInput_2->setText("");
    ui->ustatusLabel2->setText("");
}

//-------------------Modify Tab----------------------
void UserAdmin::on_ModifyBtn_2_clicked()
{
    Database connection;
    QString id = ui->userDropDown->currentText();
    QString pin = ui->powerInputModify_2->text();
    QString rin = ui->radiusInputModify->text();
    QString xin = ui->xInputModify_2->text();
    QString yin = ui->yInputModify_2->text();
    QString type = "U";

    QSqlError cerror = connection.addModifiedItem(id, type, pin, rin, xin, yin);
    if (cerror.type() != QSqlError::NoError) {
        QMessageBox::critical(this,"Error","Unable to update item in database: "+cerror.text()+" ");
        ui->ustatusLabel3->setText("Error updating item");
    }
    else{
        QMessageBox::information(this,"Record updated","Successfully updated the record");
        ui->ustatusLabel3->setText("Record updated");
    }

    ui->powerInputModify_2->clear();
    ui->radiusInputModify->clear();
    ui->xInputModify_2->clear();
    ui->yInputModify_2->clear();
}

void UserAdmin::on_userDropDown_currentIndexChanged(const QString &arg1) {

    ui->ustatusLabel3->setText("");
    QString uID = ui->userDropDown->currentText();
    Database connection;

    QSqlQuery query = connection.getRow(uID);
    if (query.exec()){
        while(query.next()){
            ui->powerInputModify_2->setText(query.value(2).toString());
            ui->radiusInputModify->setText(query.value(3).toString());
            ui->xInputModify_2->setText(query.value(4).toString());
            ui->yInputModify_2->setText(query.value(5).toString());
        }
    } else {
        QMessageBox::critical(this,"Error","Unable to fetch data from database: "+query.lastError().text());
        ui->ustatusLabel3->setText("Unable to fetch data");
    }
}

void UserAdmin::on_tabWidget_2_currentChanged(int index)
{
    Database connection;
    QSqlQueryModel *model = new QSqlQueryModel();
    if(index==1){
        model->setQuery(connection.getIDs("U"));
        ui->userDropDown->setModel(model);
        ui->ustatusLabel3->setText("");
    }
    if(index==2){
        model->setQuery(connection.getAllOfType("U"));
        model->insertColumn(0);
        model->setHeaderData(0, Qt::Horizontal, tr("Select"));
        ui->uListView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->uListView_2->setModel(model);
        //https://stackoverflow.com/questions/21409457/a-checkbox-only-column-in-qtableview
        int p;
        for(p = 0;p<model ->rowCount();p++)
        {
            ui->uListView_2->setIndexWidget(model->index(p,0),new QCheckBox());
        }
        ui->ustatusLabel5->setText("");
    }
    if(index==3){
        model->setQuery(connection.getAllOfType("U"));
        ui->uListView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->uListView->setModel(model);
        ui->ustatusLabel4->setText("");
    }
}

void UserAdmin::on_uExportBtn_clicked()
{
    QString outdata;
    int rows = ui->uListView->model()->rowCount();
    int columns = ui->uListView->model()->columnCount();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

                outdata += ui->uListView->model()->data(ui->uListView->model()->index(i,j)).toString();
                outdata += ", ";
        }
        outdata += "\n";
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save WSDB To File"), "C://","CSV Files(*.csv);;Text Files (*.txt);;All files (*.*)");
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&file);
        out << outdata;
        file.close();

        QMessageBox::information(this,"List exported","Successfully exported to file");
        ui->ustatusLabel4->setText("List exported");
    }
    else {
        QMessageBox::critical(this,"Error","Unable to export to file: "+file.errorString()+" ");
        ui->ustatusLabel4->setText("Error exporting");
    }
}

void UserAdmin::on_removeBtn_clicked()
{
    //update status label
}

void UserAdmin::on_clrSelectBtn_clicked()
{

}

void UserAdmin::on_helpBtn_clicked()
{
    QString helpText = "Write this, Aidan, you Irish twat";
    HelpDialog helpPopUp;
    helpPopUp.setHelpText(helpText);
    helpPopUp.setModal(true);
    helpPopUp.exec();
}
