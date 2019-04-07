#include "database.h"
using namespace std;
#include <iostream>
#include <cmath>

Database::Database(){cout<<"Database object created."<<endl;}
Database::~Database() { cout << "Database object removed." << endl; }
QSqlDatabase db;

QSqlError Database::setupConnection(QString host, QString dbname, QString uname, int port, QString pw, QWidget *window){
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setDatabaseName(dbname);
    db.setUserName(uname);
    db.setPort(port);
    db.setPassword(pw);
    if(!db.open()){
        return db.lastError();
    }
    else {
        return QSqlError();
    }
}

void Database::closeConnection(QWidget *window){
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
    QMessageBox::warning(window,"Connection closed","Database connection closed");
}

QSqlQuery Database::setupModel(){
    QSqlQuery *query = new QSqlQuery(db);
    query->prepare("select * from whitespacetable");
    query->exec();
    return *query;
}

QSqlError Database::addItem(QString type, double power, int radius, float x, float y){
    QString ID = createID(type);
    QSqlQuery queryAdd;
    //does the id exist? if not, do the xy pair exist? if not, proceed, otherwise return msg
    queryAdd.prepare("INSERT INTO `whitespacetable` (`ID`, `Power`, `Radius`, `X`, `Y`) VALUES (?, ?, ?, ?, ?)");
    queryAdd.addBindValue(ID);
    queryAdd.addBindValue(power);
    queryAdd.addBindValue(radius);
    queryAdd.addBindValue(x);
    queryAdd.addBindValue(y);
    if(queryAdd.exec()){ return QSqlError(); }
    else{ return queryAdd.lastError(); }
}

QSqlError Database::addModifiedItem(QString ID, QString power, QString x, QString y){
    QSqlQuery queryAdd;
    //do the xy pair exist? if not, proceed, otherwise return msg
    queryAdd.prepare("UPDATE `whitespacetable` SET Power = '"+power+"',X = '"+x+"',Y = '"+y+"' WHERE ID = '"+ID+"'");
    if(queryAdd.exec()){ return QSqlError(); }
    else{ return queryAdd.lastError(); }
}

QSqlError Database::addBulk(QString type, QVariantList power, QVariantList radius, QVariantList x, QVariantList y){
    QStringList ID;
    for (int i = 0; i<power.length(); i++){ ID.push_back(createID(type)); }
    QSqlQuery queryBulk;
    //does the id exist? if not, do the xy pair exist? if not, proceed, otherwise return msg
    queryBulk.prepare("INSERT INTO whitespacetable VALUES (?, ?, ?, ?, ?)");
    queryBulk.addBindValue(ID);
    queryBulk.addBindValue(power);
    queryBulk.addBindValue(radius);
    queryBulk.addBindValue(x);
    queryBulk.addBindValue(y);
    if(queryBulk.execBatch()){ return QSqlError(); }
    else{ return queryBulk.lastError(); }

}

QString Database::createID(QString type){
    //does id exist
    //ensure temp only numerical
    int temp = QRandomGenerator::global()->generate();
    temp = abs(temp);
    cout<<temp<<endl;
    type.append(QString::number(temp));
    return type;
}

QSqlQuery Database::getIDs(){
    QSqlQuery *query = new QSqlQuery(db);
    query->prepare("select ID from whitespacetable");
    query->exec();
    return *query;
}


QSqlQuery Database::getRow(QString ID){
    QSqlQuery *query = new QSqlQuery(db);
    query->prepare("select * from whitespacetable where ID='"+ID+"'");
    query->exec();
    return *query;
}
