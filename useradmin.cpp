/**
 * @package QTWhiteSpaceManager
 * @module UserAdmin.cpp
 * The source file of the class detemining the operations of the User GUI.
 * ----------------------------
 * Updates
 * @date: 18/04/2019
 * @abstract: Added comments, indented code
 * @author:
 */

#include "useradmin.h"
#include "ui_useradmin.h"
#include "helpdialog.h"
using namespace std;
#include <iostream>

/**
  * Constructor for a UserAdmin object.
  * @param parent: the parent of the UserAdmin
  */
UserAdmin::UserAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserAdmin)
{
    ui->setupUi(this);
    setWindowTitle("User Admin");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    cout << "User dialog object created." << endl;
}

/**
 * Destructor of the UserAdmin object.
 */
UserAdmin::~UserAdmin()
{
    delete ui;
    cout << "User dialog object destroyed." << endl;
}

QString helpUserText = "To request access to the WhiteSpace spectrum, input your location (Lat/Lon).\n If no user or transmitter are in interference range, you will be informed of the closest devices distance, their location and what power you can transmit on.";

CreateTab_2::CreateTab_2(QWidget *parent) : QWidget(parent) { }
ModifyTab_2::ModifyTab_2(QWidget *parent) : QWidget(parent) { }
ListTab_2::ListTab_2(QWidget *parent) : QWidget(parent) { }
RemoveTab_2::RemoveTab_2(QWidget *parent) : QWidget(parent) { }

//-------------------Create Tab----------------------
/**
 * A function to add a single User specified by its X and Y coordinates, to the database.
 */
void UserAdmin::on_addBtnManual_2_clicked()
{
    //ensure that input is not empty, not a text, and is in range of +-180 degrees of Lat/Lon
    QDoubleValidator *dValid= new QDoubleValidator(this);
    dValid->setBottom(-180);
    dValid->setTop(180);
    dValid->setNotation(QDoubleValidator::StandardNotation);
    ui->xInput_2->setValidator(dValid);
    ui->yInput_2->setValidator(dValid);

    double xin = ui->xInput_2->text().toDouble();
    double yin = ui->yInput_2->text().toDouble();

    User *user = new User(xin, yin);

    Database connection;
    QVariantList addCheck = connection.addItem(user);

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

/**
 * A function to clear all interface output items.
 */
void UserAdmin::on_clearBtnCreate_2_clicked()
{
    ui->xInput_2->setText("");
    ui->yInput_2->setText("");
    ui->ustatusLabel2->setText("");
    ui->tmitDistLbl->setText("");
    ui->assignedPowLbl->setText("");
}

//-------------------Modify Tab----------------------
/**
 * A function to edit the X and Y coordinates of a User device.
 * Location change may result in change in power.
 */
void UserAdmin::on_ModifyBtn_2_clicked()
{
    Database connection;
    QString id = ui->userDropDown->currentText();

    QDoubleValidator *dValid= new QDoubleValidator(this);
    dValid->setBottom(-180.00000);
    dValid->setDecimals(5);
    dValid->setTop(180.00000);
    dValid->setNotation(QDoubleValidator::StandardNotation);
    ui->xInputModify_2->setValidator(dValid);
    ui->yInputModify_2->setValidator(dValid);

    double xin = ui->xInputModify_2->text().toDouble();
    double yin = ui->yInputModify_2->text().toDouble();

    User *user = new User(xin, yin, id);

    QVariantList addCheck = connection.addModifiedItem(user);

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

/**
 * A function to update the X and Y inputs to the current X and Y values of the
 * device selected in the dropdown list.
 */
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

/**
 * A function to check which administrative tab is selected.
 * Updates/clears GUI elements according to the purpose of the tab.
 * @param index: the index of the tab
 */
void UserAdmin::on_tabWidget_2_currentChanged(int index)
{
    Database connection;
    QSqlQueryModel *model = new QSqlQueryModel();
    if(index==0){
        helpUserText="To request access to the WhiteSpace spectrum, input your location (Lat/Lon). If no user or transmitter are in interference range, you will be informed of the closest devices distance, their location and what power you can transmit on.";
    }
    if(index==1){
        helpUserText="You can change the location of a user by inputting the coordinates. The move may result in a change in the amount of power allowed.";
        ui->powerInputModify_2->clear();
        ui->xInputModify_2->clear();
        ui->yInputModify_2->clear();

        model->setQuery(connection.getIDs("U"));
        ui->userDropDown->setModel(model);
        ui->powerInputModify_2->setReadOnly(true);
        ui->ustatusLabel3->setText("");
    }
    if(index==2){
        helpUserText="You can remove any number of records by clicking on them in the table and clicking remove. Selections can be cleared with clicking again on the selection.";
        model->setQuery(connection.getAllOfType("U"));
        ui->uListView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->uListView_2->setModel(model);
        ui->uListView_2->setSelectionMode(QAbstractItemView::MultiSelection);
        ui->uListView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->ustatusLabel5->setText("");
    }
    if(index==3){
        helpUserText="You can view all devices of this type here. To export it to a CSV file, please hit Export.";
        model->setQuery(connection.getAllOfType("U"));
        ui->uListView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->uListView->setModel(model);
        ui->uListView->setSelectionMode(QAbstractItemView::NoSelection);
        ui->ustatusLabel4->setText("");
    }
}

/**
 * A function to export the user list to a file.
 */
void UserAdmin::on_uExportBtn_clicked()
{
    QString outdata;
    int rows = ui->uListView->model()->rowCount();
    int columns = ui->uListView->model()->columnCount();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            //get each table element, and concatinate them with a ,
            outdata += ui->uListView->model()->data(ui->uListView->model()->index(i,j)).toString();
            //do not add a comma at the end of the line, as the map won't be able to read it
            if (j!=columns-1){outdata += ", ";}
        }
        outdata += "\n";
    }

    //choose a location, a filename and an extension to export to
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

/**
 * A function to remove selected elements from the database.
 */
void UserAdmin::on_removeBtn_clicked()
{
    if(ui->uListView_2->selectionModel()->hasSelection()){
        QModelIndexList selected = ui->uListView_2->selectionModel()->selectedRows();
        QStringList selectedRows;

        for(int i=0; i< selected.count(); i++) {  //get all the records selected
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
            model->setQuery(connection.getAllOfType("U"));      //refresh table view
            ui->uListView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->uListView_2->setModel(model);
        }
    }
}

/**
 * A function to clear selections in the table.
 */
void UserAdmin::on_clrSelectBtn_clicked()
{
    ui->uListView_2->clearSelection();
    ui->ustatusLabel5->setText("");
}

/**
 * The function to call the Help button popup window.
 */
void UserAdmin::on_helpBtn_clicked()
{
    HelpDialog helpPopUp;
    helpPopUp.setHelpText(helpUserText);
    helpPopUp.setModal(true);
    helpPopUp.exec();
}
