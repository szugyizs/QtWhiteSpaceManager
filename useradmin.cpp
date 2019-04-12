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
//TODO
void UserAdmin::on_addBtnManual_2_clicked()
{
    int xin = ui->xInput_2->text().toInt();
    int yin = ui->yInput_2->text().toInt();
    int rin = ui->radiusInput->text().toInt();
    //User *user = new User(rin, xin, yin);

    Database connection;
    QVariantList addCheck = connection.addItem("U", rin, xin, yin); //change to Device type

    QString cerror = addCheck.last().toString();
    if (cerror != ""&&cerror != " ") {
        QMessageBox::critical(this,"Error","Unable to add to the database: "+cerror);
        ui->ustatusLabel2->setText("Error adding to database");
        return;
    }
    else{
        QMessageBox::information(this,"Record added","Successfully added to the database");
        ui->radiusInput->setText("");
        ui->xInput_2->setText("");
        ui->yInput_2->setText("");
        ui->ustatusLabel2->setText("Record added");
    }
    addCheck.pop_back();
    ui->assignedPowLbl->setText("The power that this user can transmit on is "+addCheck.last().toString()+"W.");
    ui->tmitDistLbl->setText("The closest transmitter is "+addCheck.first().toString()+" units away, at (");//+addCheck.at(1).toString()+","+addCheck.at(2).toString()+").");
    //TODO returns
}

void UserAdmin::on_clearBtnCreate_2_clicked()
{
    ui->radiusInput->setText("");
    ui->xInput_2->setText("");
    ui->yInput_2->setText("");
    ui->ustatusLabel2->setText("");
    ui->tmitDistLbl->setText("");
    ui->assignedPowLbl->setText("");
}

//-------------------Modify Tab----------------------
//TODO
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
        ui->powerInputModify_2->clear();
        ui->radiusInputModify->clear();
        ui->xInputModify_2->clear();
        ui->yInputModify_2->clear();

        model->setQuery(connection.getIDs("U"));
        ui->userDropDown->setModel(model);
        ui->ustatusLabel3->setText("");
    }
    if(index==2){
        model->setQuery(connection.getAllOfType("U"));
        ui->uListView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->uListView_2->setModel(model);
        ui->uListView_2->setSelectionMode(QAbstractItemView::MultiSelection);
        ui->uListView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->ustatusLabel5->setText("");
    }
    if(index==3){
        model->setQuery(connection.getAllOfType("U"));
        ui->uListView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->uListView->setModel(model);
        ui->uListView->setSelectionMode(QAbstractItemView::NoSelection);
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

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save User Devices To File"), "C://","CSV Files(*.csv);;Text Files (*.txt);;All files (*.*)");
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
    if(ui->uListView_2->selectionModel()->hasSelection()){
        QModelIndexList selected = ui->uListView_2->selectionModel()->selectedRows();
        QStringList selectedRows;
        for(int i=0; i< selected.count(); i++) {
            QModelIndex index = selected.at(i);
            selectedRows << ui->uListView_2->model()->data(index).toString();
        }
        Database connection;
        QSqlError err = connection.removeRecords(selectedRows);
        if (err.type() != QSqlError::NoError) {
            QMessageBox::critical(this,"Error","Unable to remove data from database: "+err.text());
            ui->ustatusLabel5->setText("Unable to fetch data");
        } else {
            QMessageBox::information(this,"Success","Successfully removed records from database");
            ui->ustatusLabel5->setText("Successfully removed ");
            QSqlQueryModel *model = new QSqlQueryModel();
            model->setQuery(connection.getAllOfType("U"));
            ui->uListView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->uListView_2->setModel(model);
        }
    }
}

void UserAdmin::on_clrSelectBtn_clicked()
{
    ui->uListView_2->clearSelection();
    ui->ustatusLabel5->setText("");
}

//TODO
void UserAdmin::on_helpBtn_clicked()
{
    QString helpText = "Write this, Aidan, you Irish twat";
    HelpDialog helpPopUp;
    helpPopUp.setHelpText(helpText);
    helpPopUp.setModal(true);
    helpPopUp.exec();
}

//TODO
void UserAdmin::on_plotUBtn_clicked()
{

}
