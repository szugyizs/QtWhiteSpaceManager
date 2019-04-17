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

QString helpUserText = "Create tab helptext.";

CreateTab_2::CreateTab_2(QWidget *parent) : QWidget(parent) { }
ModifyTab_2::ModifyTab_2(QWidget *parent) : QWidget(parent) { }
ListTab_2::ListTab_2(QWidget *parent) : QWidget(parent) { }
RemoveTab_2::RemoveTab_2(QWidget *parent) : QWidget(parent) { }

//-------------------Create Tab----------------------
void UserAdmin::on_addBtnManual_2_clicked()
{
    double xin = ui->xInput_2->text().toDouble();
    double yin = ui->yInput_2->text().toDouble();
    int rin = 1;
    //User *user = new User(rin, xin, yin);

    Database connection;
    QVariantList addCheck = connection.addItem("U", rin, xin, yin);

    QString cerror = addCheck.last().toString();
    if (cerror != ""&&cerror != " ") {
        QMessageBox::critical(this,"Error","Unable to add to the database: "+cerror);
        ui->ustatusLabel2->setText("Error adding to database");
        return;
    }
    else{
        QMessageBox::information(this,"Record added","Successfully added to the database");
        ui->xInput_2->setText("");
        ui->yInput_2->setText("");
        ui->ustatusLabel2->setText("Record added");
    }
    addCheck.pop_back();
    ui->assignedPowLbl->setText("The user can transmit on "+addCheck.last().toString()+"W.");
    addCheck.pop_back();
    ui->tmitDistLbl->setText("It is "+addCheck.first().toString()+" miles away");
    addCheck.pop_front();
    ui->tmitDistLbl_2->setText("It is located at ("+addCheck.first().toString()+","+addCheck.last().toString()+").");
}

void UserAdmin::on_clearBtnCreate_2_clicked()
{
    ui->xInput_2->setText("");
    ui->yInput_2->setText("");
    ui->ustatusLabel2->setText("");
    ui->tmitDistLbl->setText("");
    ui->assignedPowLbl->setText("");
}

//-------------------Modify Tab----------------------
void UserAdmin::on_ModifyBtn_2_clicked()
{
    Database connection;
    QString id = ui->userDropDown->currentText();
    double pin = ui->powerInputModify_2->text().toDouble();
    int rin = 1;
    double xin = ui->xInputModify_2->text().toDouble();
    double yin = ui->yInputModify_2->text().toDouble();
    QString type = "U";

    QVariantList addCheck = connection.addModifiedItem(id, "U", pin, rin, xin, yin); //change to Device type

    QString cerror = addCheck.last().toString();
    if (cerror != ""&&cerror != " ") {
        QMessageBox::critical(this,"Error","Unable to modify to the database: "+cerror);
        ui->ustatusLabel3->setText("Error adding to database");
        return;
    }
    else{
        QMessageBox::information(this,"Record added","Successfully modified to the database");
        ui->powerInputModify_2->setText("");
        ui->xInputModify_2->setText("");
        ui->yInputModify_2->setText("");
        ui->ustatusLabel3->setText("Record added");

        addCheck.pop_back();
        ui->assignedPowLbl_2->setText("The user can transmit on "+addCheck.last().toString()+"W.");
        addCheck.pop_back();
        ui->tmitDistLbl_3->setText("It is "+addCheck.first().toString()+" miles away");
        addCheck.pop_front();
        ui->tmitDistLbl_4->setText("It is located at ("+addCheck.first().toString()+","+addCheck.last().toString()+").");
    }
}

void UserAdmin::on_userDropDown_currentIndexChanged(const QString &arg1) {

    ui->ustatusLabel3->setText("");
    QString uID = ui->userDropDown->currentText();
    Database connection;

    QSqlQuery query = connection.getRow(uID);
    if (query.exec()){
        while(query.next()){
            ui->powerInputModify_2->setText(query.value(2).toString());
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
    if(index==0){
        helpUserText="Create tab helpUserText";
    }
    if(index==1){
        helpUserText="Modify tab helpUserText";
        ui->powerInputModify_2->clear();
        ui->xInputModify_2->clear();
        ui->yInputModify_2->clear();

        model->setQuery(connection.getIDs("U"));
        ui->userDropDown->setModel(model);
        ui->powerInputModify_2->setReadOnly(true);
        ui->ustatusLabel3->setText("");
    }
    if(index==2){
        helpUserText="Remove tab helpUserText";
        model->setQuery(connection.getAllOfType("U"));
        ui->uListView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->uListView_2->setModel(model);
        ui->uListView_2->setSelectionMode(QAbstractItemView::MultiSelection);
        ui->uListView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->ustatusLabel5->setText("");
    }
    if(index==3){
        helpUserText="List tab helpUserText";
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
            if (j!=columns-1){outdata += ", ";}
        }
        outdata += "\n";
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save User Devices To File"), "C://","CSV Files(*.csv);;All files (*.*)");
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

void UserAdmin::on_helpBtn_clicked()
{
    HelpDialog helpPopUp;
    helpPopUp.setHelpText(helpUserText);
    helpPopUp.setModal(true);
    helpPopUp.exec();
}
