#include <iostream>
using namespace std;
#include "database.h"
#include "databasedialog.h"
#include "ui_databasedialog.h"

//-----------------Constructors-----------------
//Database::Database() {}
Database::Database() {
    QHash<QString, Device> deviceList_;
    QHash<QString, Device> userList_;
    QHash<QString, Device> transmitterList_;

    QUuid uuid;
//    DatabaseDialog()
//    ui->tableWidget->setRowCount(0);
//    ui->tableWidget->setColumnCount(5);
}
Database::~Database() { cout << "Database object removed." << endl; }

//-----------------List mgmt functions-----------------
void Database::addDevice(Device d, char t){
    QString id;
    if (d.getID()==nullptr||d.getID()==""){
    if (t=='U'){id = "U";}
    else if (t=='T'){id = "T";}
    else { return; }
    id.append(uuid.createUuid().toString()); //do we need a UUID at all
    d.setID(id);
    }
    else {id=d.getID();}
    deviceList_.insert(id,d);
//    int i = ui->tableWidget->getRowCount();

//    ui->tableWidget->setItem(i,j,new QTableWidgetItem(data[i][j]));

}

Device Database::getDevice(QString id){
    return deviceList_.value(id);
}

void Database::removeDevice(QString id){
    deviceList_.remove(id);
}

//-----------------Access functions-----------------
//licence check funct from user in here
//location/distance check
//power check
