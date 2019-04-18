/**
 * @package QTWhiteSpaceManager
 * @module TransmitterAdmin.cpp
 * The source file of the class detemining the operations of the Transmitter GUI.
 * ----------------------------
 * Updates
 * @date: 18/04/2019
 * @abstract: Added comments, indented code
 * @author:
 */

#include "transmitteradmin.h"
#include "ui_transmitteradmin.h"
#include "helpdialog.h"
using namespace std;
#include <iostream>
#include <QCheckBox>

/**
  * Constructor for a TransmitterAdmin object.
  * @param parent: the parent of the TransmitterAdmin
  */
TransmitterAdmin::TransmitterAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransmitterAdmin)
{
    ui->setupUi(this);
    setWindowTitle("Transmitter Admin");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    cout << "Transmitter dialog object created." << endl;
}

/**
 * Destructor for the TransmitterAdmin
 */
TransmitterAdmin::~TransmitterAdmin()
{
    delete ui;
    cout << "Transmitter dialog object destroyed." << endl;
}

CreateTab::CreateTab(QWidget *parent) : QWidget(parent) { }
ModifyTab::ModifyTab(QWidget *parent) : QWidget(parent) { }
RemoveTab::RemoveTab(QWidget *parent) : QWidget(parent) { }
ListTab::ListTab(QWidget *parent) : QWidget(parent) { }

QList<QStringList> columns;
QString helpTmitText = "You can import transmitters from a file. Ensure the only columns in there are X and Y coordinates, in that order. Headers are allowed.";

//-------------------Create Tab----------------------
/**
 * The slot of the addBtnManual being clicked.
 * It takes the Transmitter item to be added, and passes the details to the database function.
 */
void TransmitterAdmin::on_addBtnManual_clicked()
{
    //ensure that input is not empty, not a text, and is in range of +-180 degrees of Lat/Lon
    QDoubleValidator *dValid= new QDoubleValidator(this);
    dValid->setBottom(-180);
    dValid->setTop(180);
    dValid->setNotation(QDoubleValidator::StandardNotation);
    ui->xInput->setValidator(dValid);
    ui->yInput->setValidator(dValid);

    double xin = ui->xInput->text().toDouble();
    double yin = ui->yInput->text().toDouble();
    Transmitter *transmitter = new Transmitter(xin, yin);

    Database connection;
    QVariantList addCheck = connection.addItem(transmitter);

    QString cerror = addCheck.last().toString();
    if (cerror != ""&&cerror != " ") {
        QMessageBox::critical(this,"Error","Unable to add to the database: "+cerror);
        ui->tstatusLabel2->setText("Error adding to database");
        return;
    }
    else{
        QMessageBox::information(this,"Record added","Successfully added to the database");
        ui->xInput->setText("");
        ui->yInput->setText("");
        ui->tstatusLabel2->setText("Record added");
    }
}

/**
 * A function to clean GUI.
 */
void TransmitterAdmin::on_clearBtnCreate_clicked()
{
    ui->xInput->setText("");
    ui->yInput->setText("");
    ui->tstatusLabel2->setText("");
}

//-----------------Create Tab 2----------------------
/**
 * A function to read in transmitter values from a file.
 */
void TransmitterAdmin::on_browseFile_clicked()
{
    columns.clear();
    QList<QString> headers;
    bool firstCheck = true;
    bool toHeader = true;
    int numOfCols = 0;

    //choose file to read in from certain location and of a certain type
    QString line;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"C://","All files (*.*);;CSV Files(*.csv)");
    QFile file(fileName);

    QTextStream ipLine(&file);
    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::critical(this,"Error","Unable to import file: "+file.errorString());
        ui->tstatusLabel1->setText("Error loading file");
        return;
    }

    //only csv files allowed
    QFileInfo fInfo(fileName);
    if (fInfo.completeSuffix()!="csv"){
        QMessageBox::critical(this,"Error","Unable to import file, wrong file type.");
        ui->tstatusLabel1->setText("Error loading file");
        return;
    }

    int i = 0;
    do{
        if (firstCheck){  //if it's the first row, separate values into a different list
            line = ipLine.readLine();
            headers << line.split(',');
            numOfCols = headers.count();
            if (numOfCols!=2){
                QMessageBox::critical(this,"Error","Invalid number of columns. Please restructure data to an (X,Y) format.");
                ui->tstatusLabel1->setText("Invalid number of columns");
                ui->fileTableWidget->clear();
                ui->fileTableWidget->setRowCount(0);
                ui->fileTableWidget->setColumnCount(0);
                return;
            }

            QListIterator<QString> hIt(headers); //iterate through the headers list and check if they are all valid types
            while (hIt.hasNext()) {
                QString current = hIt.next();
                bool isNum = false;
                current.toDouble(&isNum);
                if(isNum){
                    int temp = headers.count();
                    headers.clear();
                    for(int j=0; j<temp; j++){
                        headers<<(QString::number(j+1)); //if row is values, headers replaced by index numbers
                    }
                    toHeader = false;
                }
            }
            if (!toHeader){
                columns<<line.split(',');       //if there are less elements in any row, error out
                if (columns[0].size()!=numOfCols){
                    QMessageBox::critical(this,"Error","Unable to import file, entries with empty fields.");
                    ui->tstatusLabel1->setText("Error loading file");
                    return;
                }
            }
            firstCheck = false; //move onto next row in the next iteration
        }
        else{
            line = ipLine.readLine();
            if (!(line == "")){
                columns << line.split(',');
                if (columns[i].size()!=numOfCols){     //if there are less elements in any row, error out
                    QMessageBox::critical(this,"Error","Unable to import file, entries with empty fields.");
                    ui->tstatusLabel1->setText("Error loading file");
                    return;
                }
                i++;
            }
        }
    } while (!line.isNull());

    //set tablewidget to be of the size of the data
    ui->fileTableWidget->setRowCount(columns.size());
    ui->fileTableWidget->setColumnCount(columns[0].size());
    ui->fileTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    for (int i=0; i<headers.length(); i++){ ui->fileTableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(headers.at(i)));}

    for (int i = 0; i<columns.size(); ++i){
        for (int j = 0; j<columns[i].size(); ++j){
            ui->fileTableWidget->setItem(i,j,new QTableWidgetItem(columns[i][j]));  //fill table
        }
    }
    ui->tstatusLabel1->setText("File loaded");
    ui->addAllBtn->setEnabled(true);
}

/**
 * A function to add all of the values in the table read in from a file.
 */
void TransmitterAdmin::on_addAllBtn_clicked()
{
    QVariantList xin;
    QVariantList yin;
    QVariantList pin;
    QVariantList radiusList;
    QString confirmMsg;

    confirmMsg="Are the columns: X , Y; in this order?";
    if (confirmPopUp(confirmMsg)==0){
        for (int i = 0; i<columns.size(); ++i){
            for (int j = 0; j<columns[i].size(); ++j){ //read in items one by one
                switch(j) {
                case 0 :
                    xin<<(columns[i][j]);
                    break;
                case 1 :
                    yin<<(columns[i][j]);
                    break;
                default :
                    QMessageBox::critical(this,"Error","Invalid item ");
                    ui->tstatusLabel1->setText("Invalid item");
                    ui->fileTableWidget->clear();
                    ui->fileTableWidget->setRowCount(0);
                    ui->fileTableWidget->setColumnCount(0);
                    return;
                }
            }
        }
        for(int i = 0; i<xin.length(); i++){
            pin<<(4);
            radiusList<<(6);
        }
    }
    else {
        QMessageBox::critical(this,"Error","Invalid column structure. Restructure file and load again.");
        ui->tstatusLabel1->setText("Invalid types of columns");
        ui->fileTableWidget->clear();
        ui->fileTableWidget->setRowCount(0);
        ui->fileTableWidget->setColumnCount(0);
        return;
    }
    //list of transmitters? // Transmitter *transmitter = new Transmitter(xin, yin);
    Database connection;
    QVariantList addBulkCheck = connection.addBulk("T", pin, radiusList, xin, yin);
    QString cerror;
    for(int i=0; i<addBulkCheck.length(); i++){
        cerror.append(addBulkCheck.at(i).toString());
    }

    bool isNum = false;
    cerror.toDouble(&isNum);

    QString cerror2 = addBulkCheck.last().toString();

    if ((cerror2 != ""&&cerror2 != " ") && (addBulkCheck.length()==1 && !isNum || addBulkCheck.length()==0)) {
        QMessageBox::critical(this,"Error","Unable to add to the database: "+addBulkCheck.last().toString());
        ui->tstatusLabel1->setText("Error adding to database");
        return;
    }
    else{
        QMessageBox::information(this,"Record added","Successfully added rows "+cerror);
        ui->fileTableWidget->clear();
        ui->fileTableWidget->setRowCount(0);
        ui->fileTableWidget->setColumnCount(0);
        ui->tstatusLabel1->setText("Record added");
    }
}

/**
 * A function to check which tab is selected.
 */
void TransmitterAdmin::on_toolBox_currentChanged(int index)
{
    if (index==0){ helpTmitText = "You can import transmitters from a file. Ensure the only columns in there are X and Y coordinates, in that order. Headers are allowed.";}
    else{ helpTmitText = "If no transmitters are in interference range, you will be allowed to install a transmitter.";}
    foreach(QLineEdit* lineEd, findChildren<QLineEdit*>()) { lineEd->clear(); }
    ui->fileTableWidget->clear();
    ui->tstatusLabel1->setText("");
    ui->tstatusLabel2->setText("");
}

/**
 * A function to clear all interface output items.
 */
void TransmitterAdmin::on_clearFileBtn_clicked() {
    ui->fileTableWidget->clear();
    ui->fileTableWidget->setRowCount(0);
    ui->fileTableWidget->setColumnCount(0);
    ui->tstatusLabel1->setText("");
}

//-------------------Modify Tab----------------------
/**
 * A function to edit the X and Y coordinates of a User device.
 * Location change may result in change in power.
 */
void TransmitterAdmin::on_ModifyBtn_clicked()
{
    Database connection;
    QString id = ui->tmitDropDown->currentText();

    QDoubleValidator *dValid= new QDoubleValidator(this);
    dValid->setBottom(-180.00000);
    dValid->setDecimals(5);
    dValid->setTop(180.00000);
    dValid->setNotation(QDoubleValidator::StandardNotation);
    ui->xInputModify->setValidator(dValid);
    ui->yInputModify->setValidator(dValid);

    double xin = ui->xInputModify->text().toDouble();
    double yin = ui->yInputModify->text().toDouble();

    Transmitter *transmitter = new Transmitter(xin, yin, id);

    QVariantList addCheck = connection.addModifiedItem(transmitter);

    QString cerror = addCheck.last().toString();
    if (cerror != ""&&cerror != " ") {
        QMessageBox::critical(this,"Error","Unable to update item in database: "+cerror+" ");
        ui->tstatusLabel3->setText("Unable to update");
        return;
    }
    else{
        QMessageBox::information(this,"Record updated","Successfully updated the record");
        ui->tstatusLabel3->setText("Record updated");
        ui->xInputModify->clear();
        ui->yInputModify->clear();
    }
}

/**
 * A function to update the X and Y inputs to the current X and Y values of the
 * device selected in the dropdown list.
 */
void TransmitterAdmin::on_tmitDropDown_currentIndexChanged(const QString &arg1)
{
    ui->tstatusLabel3->setText("");
    QString tmitID = ui->tmitDropDown->currentText();
    Database connection;

    QSqlQuery query = connection.getRow(tmitID);
    if (query.exec()){
        while(query.next()){
            ui->xInputModify->setText(query.value(4).toString());
            ui->yInputModify->setText(query.value(5).toString());
        }
    } else{
        QMessageBox::critical(this,"Error","Unable to fetch data from database: "+query.lastError().text());
        ui->tstatusLabel3->setText("Error fetching data");
    }

}

/**
 * A function to check which administrative tab is selected.
 * Updates/clears GUI elements according to the purpose of the tab.
 * @param index: the index of the tab
 */
void TransmitterAdmin::on_tabWidget_currentChanged(int index)
{
    Database connection;
    QSqlQueryModel *model = new QSqlQueryModel();
    if(index==1){
        helpTmitText = "You can change the location of a transmitter by inputting the coordinates.";
        model->setQuery(connection.getIDs("T"));
        ui->tmitDropDown->setModel(model);
        ui->tstatusLabel3->setText("");
    }
    if(index==2){
        helpTmitText = "You can remove any number of records by clicking on them in the table and clicking remove. Selections can be cleared with clicking again on the selection.";
        model->setQuery(connection.getAllOfType("T"));
        model->setHeaderData(0, Qt::Horizontal, tr("Select"));
        ui->ListTableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->ListTableView_2->setModel(model);
        ui->ListTableView_2->setSelectionMode(QAbstractItemView::MultiSelection);
        ui->ListTableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tstatusLabel5->setText("");
    }
    if(index==3){
        helpTmitText = "You can view all devices of this type here. To export it to a CSV file, please hit Export.";
        model->setQuery(connection.getAllOfType("T"));
        ui->ListTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->ListTableView->setModel(model);
        ui->ListTableView->setSelectionMode(QAbstractItemView::NoSelection);
        ui->tstatusLabel4->setText("");
    }
}

/**
 * A function to export the transmitter list to a file.
 */
void TransmitterAdmin::on_tExportBtn_clicked()
{
    QString outdata;
    int rows = ui->ListTableView->model()->rowCount();
    int columns = ui->ListTableView->model()->columnCount();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            //get each table element, and concatinate them with a ,
            outdata += ui->ListTableView->model()->data(ui->ListTableView->model()->index(i,j)).toString();
            //do not add a comma at the end of the line, as the map won't be able to read it
            if (j!=columns-1){outdata += ", ";}
        }
        outdata += "\n";
    }

    //choose a location, a filename and an extension to export to
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save WSDB To File"), "C://","CSV Files(*.csv);;All files (*.*)");
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&file);
        out << outdata;
        file.close();

        QMessageBox::information(this,"List exported","Successfully exported to file");
        ui->tstatusLabel4->setText("List exported");
    }
    else {
        QMessageBox::critical(this,"Error","Unable to export to file: "+file.errorString()+" ");
        ui->tstatusLabel4->setText("Error exporting");
    }
}

/**
 * A function to remove selected elements from the database.
 */
void TransmitterAdmin::on_removeBtn_clicked()
{
    if(ui->ListTableView_2->selectionModel()->hasSelection()){
        QModelIndexList selected = ui->ListTableView_2->selectionModel()->selectedRows();
        QStringList selectedRows;
        for(int i=0; i< selected.count(); i++) { //get all the records selected
            QModelIndex index = selected.at(i);
            selectedRows << ui->ListTableView_2->model()->data(index).toString();
        }
        Database connection;
        QSqlError err = connection.removeRecords(selectedRows);
        if (err.type() != QSqlError::NoError) {
            QMessageBox::critical(this,"Error","Unable to remove data from database: "+err.text());
            ui->tstatusLabel5->setText("Unable to fetch data");
        } else {
            QMessageBox::information(this,"Success","Successfully removed records from database");
            ui->tstatusLabel5->setText("Successfully removed ");
            QSqlQueryModel *model = new QSqlQueryModel();
            model->setQuery(connection.getAllOfType("T"));      //refresh table view
            ui->ListTableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->ListTableView_2->setModel(model);
        }
    }
}

/**
 * A function to clear all selections in the remove table.
 */
void TransmitterAdmin::on_clrSelectBtn_clicked()
{
    ui->ListTableView_2->clearSelection();
    ui->tstatusLabel5->setText("");
}

/**
 * A function to set the dialog text of help.
 */
void TransmitterAdmin::on_helpBtn_clicked()
{
    HelpDialog helpPopUp;
    helpPopUp.setHelpText(helpTmitText);
    helpPopUp.setModal(true);
    helpPopUp.exec();
}

/**
 * The popup box creating the help dialog.
 * @param values: the text to be shown in the popup
 * @return if agreed or not
 */
int TransmitterAdmin::confirmPopUp(QString values) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm column setup", values, QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {return 0;}
    else {return 1;}
}
