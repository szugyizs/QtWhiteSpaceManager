#include "transmitteradmin.h"
#include "ui_transmitteradmin.h"
#include "helpdialog.h"
using namespace std;
#include <iostream>
#include <QCheckBox>

TransmitterAdmin::TransmitterAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransmitterAdmin)
{
    ui->setupUi(this);
    setWindowTitle("Transmitter Admin");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    cout << "Transmitter dialog object created." << endl;
}

TransmitterAdmin::~TransmitterAdmin()
{
    delete ui;
    cout << "Transmitter dialog object destroyed." << endl;
}

QList<QStringList> columns;
QString helpTmitText = "Create file tab helptext.";

CreateTab::CreateTab(QWidget *parent) : QWidget(parent) { }
ModifyTab::ModifyTab(QWidget *parent) : QWidget(parent) { }
RemoveTab::RemoveTab(QWidget *parent) : QWidget(parent) { }
ListTab::ListTab(QWidget *parent) : QWidget(parent) { }

//-------------------Create Tab----------------------
void TransmitterAdmin::on_addBtnManual_clicked()
{
    int xin = ui->xInput->text().toInt();
    int yin = ui->yInput->text().toInt();
    //Transmitter *transmitter = new Transmitter(xin, yin);
    int rin = 6;

    Database connection;
    QVariantList addCheck = connection.addItem("T", rin, xin, yin);

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

void TransmitterAdmin::on_clearBtnCreate_clicked()
{
    ui->xInput->setText("");
    ui->yInput->setText("");
    ui->tstatusLabel2->setText("");
}

//-----------------Create Tab 2----------------------
void TransmitterAdmin::on_browseFile_clicked()
{
    columns.clear();
    QList<QString> headers;
    bool firstCheck = true;
    bool toHeader = true;
    int numOfCols = 0;

    QString line;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"C://","All files (*.*);;CSV Files(*.csv)");
    QFile file(fileName);

    QTextStream ipLine(&file);
    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::critical(this,"Error","Unable to import file: "+file.errorString());
        ui->tstatusLabel1->setText("Error loading file");
        return;
    }
    QFileInfo fInfo(fileName);
    if (fInfo.completeSuffix()!="csv"){
        QMessageBox::critical(this,"Error","Unable to import file, wrong file type.");
        ui->tstatusLabel1->setText("Error loading file");
        return;
    }

    do{
        if (firstCheck){
            line = ipLine.readLine();
            headers << line.split(',');
            numOfCols = headers.count();

            QListIterator<QString> hIt(headers);
            while (hIt.hasNext()) {
                QString current = hIt.next();
                bool isNum = false;
                current.toDouble(&isNum);
                if(isNum){ toHeader = false; }
            }
            if (!toHeader){
                columns<<line.split(',');
                if (columns.count()!=numOfCols){
                    QMessageBox::critical(this,"Error","Unable to import file, entries with empty fields.");
                    ui->tstatusLabel1->setText("Error loading file");
                    return;
                }
            }
            firstCheck = false;
        }
        else{
            line = ipLine.readLine();
            columns << line.split(',');
            if (columns.count()!=numOfCols){
                QMessageBox::critical(this,"Error","Unable to import file, entries with empty fields.");
                ui->tstatusLabel1->setText("Error loading file");
                return;
            }
        }
    } while (!line.isNull());

    ui->fileTableWidget->setRowCount(columns.size()-1);
    ui->fileTableWidget->setColumnCount(columns[0].size());
    ui->fileTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    for (int i=0; i<headers.length(); i++){ ui->fileTableWidget->setHorizontalHeaderItem(i,new QTableWidgetItem(headers.at(i)));}

    for (int i = 0; i<columns.size(); ++i){
        for (int j = 0; j<columns[i].size(); ++j){
            ui->fileTableWidget->setItem(i,j,new QTableWidgetItem(columns[i][j]));
        }
    }
    ui->tstatusLabel1->setText("File loaded");
}

//TODO
void TransmitterAdmin::on_addAllBtn_clicked()
{
    QVariantList xin;
    QVariantList yin;
    QVariantList pin;
    QVariantList radiusList;

    //action based on number of columns?
    for (int i = 0; i<columns.size()-1; ++i){
        for (int j = 0; j<columns[i].size(); ++j){
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
                return;
            }
        }
        //      Transmitter *transmitter = new Transmitter( xin.last().toDouble(), yin.at(j).toInt(), pin.at(j).toInt()); //?? fix TODO
    }

    for(int i = 0; i<xin.length(); i++){
        pin<<(4);
        radiusList<<(6);
    }

    Database connection;

    QSqlError cerror = connection.addBulk("T", pin, radiusList, xin, yin);
    if (cerror.type() != QSqlError::NoError) {
        QMessageBox::critical(this,"Error","Unable to add to the database: "+cerror.text()+" ");
        ui->tstatusLabel1->setText("Error loading database");
    }
    else{
        QMessageBox::information(this,"Records added","Successfully added to the database");
        ui->fileTableWidget->clear();
        ui->tstatusLabel1->setText("Records added");
    }

}

void TransmitterAdmin::on_toolBox_currentChanged(int index)
{
    if (index==0){ helpTmitText = "Create file page helpTmitText";}
    else{ helpTmitText = "Create manual helpTmitText";}
    foreach(QLineEdit* lineEd, findChildren<QLineEdit*>()) { lineEd->clear(); }
    ui->fileTableWidget->clear();
    ui->tstatusLabel1->setText("");
    ui->tstatusLabel2->setText("");
}

void TransmitterAdmin::on_clearFileBtn_clicked() {
    ui->fileTableWidget->clear();
    ui->fileTableWidget->setRowCount(0);
    ui->fileTableWidget->setColumnCount(0);
    ui->tstatusLabel1->setText("");
}

//-------------------Modify Tab----------------------
void TransmitterAdmin::on_ModifyBtn_clicked()
{
    Database connection;
    QString id = ui->tmitDropDown->currentText();
    QString type = "T";
    double pin = 1000;
    double xin = ui->xInputModify->text().toDouble();
    double yin = ui->yInputModify->text().toDouble();
    int rin = 6;

    QVariantList addCheck = connection.addModifiedItem(id, type, pin, rin, xin, yin);

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

void TransmitterAdmin::on_tabWidget_currentChanged(int index)
{
    Database connection;
    QSqlQueryModel *model = new QSqlQueryModel();
    if(index==1){
        helpTmitText = "Modify page helpTmitText";
        model->setQuery(connection.getIDs("T"));
        ui->tmitDropDown->setModel(model);
        ui->tstatusLabel3->setText("");
    }
    if(index==2){
        helpTmitText = "Remove page helpTmitText";
        model->setQuery(connection.getAllOfType("T"));
        model->setHeaderData(0, Qt::Horizontal, tr("Select"));
        ui->ListTableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->ListTableView_2->setModel(model);
        ui->ListTableView_2->setSelectionMode(QAbstractItemView::MultiSelection);
        ui->ListTableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tstatusLabel5->setText("");
    }
    if(index==3){
        helpTmitText = "List page helpTmitText";
        model->setQuery(connection.getAllOfType("T"));
        ui->ListTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->ListTableView->setModel(model);
        ui->ListTableView->setSelectionMode(QAbstractItemView::NoSelection);
        ui->tstatusLabel4->setText("");
    }
}

void TransmitterAdmin::on_tExportBtn_clicked()
{
    QString outdata;
    int rows = ui->ListTableView->model()->rowCount();
    int columns = ui->ListTableView->model()->columnCount();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            outdata += ui->ListTableView->model()->data(ui->ListTableView->model()->index(i,j)).toString();
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
        ui->tstatusLabel4->setText("List exported");
    }
    else {
        QMessageBox::critical(this,"Error","Unable to export to file: "+file.errorString()+" ");
        ui->tstatusLabel4->setText("Error exporting");
    }
}

void TransmitterAdmin::on_removeBtn_clicked()
{
    if(ui->ListTableView_2->selectionModel()->hasSelection()){
        QModelIndexList selected = ui->ListTableView_2->selectionModel()->selectedRows();
        QStringList selectedRows;
        for(int i=0; i< selected.count(); i++) {
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
            model->setQuery(connection.getAllOfType("U"));
            ui->ListTableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->ListTableView_2->setModel(model);
        }
    }
}

void TransmitterAdmin::on_clrSelectBtn_clicked()
{
    ui->ListTableView_2->clearSelection();
    ui->tstatusLabel5->setText("");
}

void TransmitterAdmin::on_helpBtn_clicked()
{
    HelpDialog helpPopUp;
    helpPopUp.setHelpText(helpTmitText);
    helpPopUp.setModal(true);
    helpPopUp.exec();
}

