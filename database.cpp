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
//TODO
QVariantList Database::addItem(QString type, int radius, double x, double y){
    QSqlQuery queryAdd;
    double power;
    QVariantList result = checkInterference(x, y, type);
    if (result.length()!=3){ result.push_back(QSqlError("No other points to compare with.").text()); return result;}

    if (type.compare("U")==0){
        if(!(result.at(0).toInt()>6)){ result.push_back(QSqlError("Device cannot join here, is in close proximity to a transmitter.").text()); return result;}
        else if(!(result.at(0).toInt()>15)){ power = 1; result.push_back(power);} //limited power
        else { power = 4; result.push_back(power);} //full power
    }
    else{
        if(!(result.at(0).toInt()>12)){ result.push_back(QSqlError("Transmitter cannot be built here, is in close proximity to another transmitter.").text()); return result;}
    }
    queryAdd.prepare("INSERT INTO `whitespacetable` (`Type`, `Power`, `Radius`, `X`, `Y`) VALUES (?, ?, ?, ?, ?)");
    queryAdd.addBindValue(type);
    queryAdd.addBindValue(power);
    queryAdd.addBindValue(radius);
    queryAdd.addBindValue(x);
    queryAdd.addBindValue(y);
    result.push_back(power);
    if(queryAdd.exec()){ result.push_back(QSqlError().text()); }
    else{ result.push_back(queryAdd.lastError().text()); }
    return result;
}

//TODO
QSqlError Database::addModifiedItem(QString ID, QString type, QString power, QString radius, QString x, QString y){
    QSqlQuery queryAdd;
    queryAdd.prepare("UPDATE `whitespacetable` SET Type = '"+type+"',Power = '"+power+"',Radius = '"+radius+"',X = '"+x+"',Y = '"+y+"' WHERE ID = '"+ID+"'");
    if(queryAdd.exec()){ return QSqlError(); }
    else{ return queryAdd.lastError(); }
}

//TODO
QSqlError Database::addBulk(QString type, QVariantList power, QVariantList radius, QVariantList x, QVariantList y){
    QSqlQuery queryBulk;
//    for(int i=0; i<x.length(); i++){}
//    //double power;
//    QVariantList canJoin = checkInterference(x, y, type);
//    if (canJoin.length()!=3){ return QSqlError("No other points to compare with."); }

//    if (type.compare("U")==0){
//        if(!(canJoin>6)){ return QSqlError("Device cannot join here, is in close proximity to a transmitter."); }
//        else if(!(canJoin>15)){ power = 1; } //limited power
//        else { power = 4; } //full power
//    }
//    else{
//        if(!(canJoin>12)){ return QSqlError("Transmitter cannot be built here, is in close proximity to another transmitter."); }
//    }

    queryBulk.prepare("INSERT INTO whitespacetable (`Type`, `Power`, `Radius`, `X`, `Y`) VALUES (?, ?, ?, ?, ?)");
    queryBulk.addBindValue(type);
    queryBulk.addBindValue(power);
    queryBulk.addBindValue(radius);
    queryBulk.addBindValue(x);
    queryBulk.addBindValue(y);
    if(queryBulk.execBatch()){ return QSqlError(); }
    else{ return queryBulk.lastError(); }
}

QSqlQuery Database::getIDs(QString type){
    QSqlQuery *query = new QSqlQuery(db);
    query->prepare("select ID from whitespacetable where type='"+type+"'");
    query->exec();
    return *query;
}

QSqlQuery Database::getRow(QString ID){
    QSqlQuery *query = new QSqlQuery(db);
    query->prepare("select * from whitespacetable where ID='"+ID+"'");
    query->exec();
    return *query;
}

QSqlQuery Database::getAllOfType(QString type){
    QSqlQuery *query = new QSqlQuery(db);
    query->prepare("select * from whitespacetable where type='"+type+"'");
    query->exec();
    return *query;
}

QSqlError Database::removeRecords(QStringList rows){
    QSqlQuery queryBulkRemove;
    //https://lists.qt-project.org/pipermail/qt-interest-old/2011-September/035927.html
    QStringList placeholders;
    for (int i = 0; i < rows.size(); ++i) {placeholders << "?";}

    if (rows.size()==1){
        queryBulkRemove.prepare("DELETE FROM `whitespacetable` WHERE `whitespacetable`.`ID`  = ?");
        queryBulkRemove.addBindValue(rows[0]);
    }
    else{
        QString rj = rows.join(", ");
        queryBulkRemove.prepare("DELETE FROM `whitespacetable` WHERE `whitespacetable`.`ID`  IN ("+rj+")");
    }
    if(queryBulkRemove.exec()){ return QSqlError(); }
    else{ return queryBulkRemove.lastError(); }
}

QVariantList Database::checkInterference(double x, double y, QString type){
    QSqlQuery *query = new QSqlQuery(db);
    query->prepare("select X, Y from whitespacetable where type='T'");
    query->exec();

    QList<QVariantList> queryPairs;

    while (query->next()) {
        QSqlRecord queryData = query->record();
        QVariantList temp;
        temp.push_back(query->value(0));
        temp.push_back(query->value(1));
        queryPairs.push_back(temp);
    }

    double shortestDist=99999999999;
    QVariantList closestPt;

    if (type.compare("U")==0){
        for(int i = 0; i<queryPairs.length();i++){
            double tempDist = distance(x,y,queryPairs.at(i).at(0).toDouble(),queryPairs.at(i).at(1).toDouble());
            if(tempDist<shortestDist){
                closestPt.clear();
                shortestDist = tempDist;
                closestPt.push_back(shortestDist);
                closestPt.push_back(queryPairs.at(i).at(0));
                closestPt.push_back(queryPairs.at(i).at(1));
            }
        }
    }
    else{
        for(int i = 0; i<queryPairs.length();i++){
            double tempDist = distance(x,y,queryPairs.at(i).at(0).toDouble(),queryPairs.at(i).at(1).toDouble());
            if(tempDist<shortestDist){
                shortestDist = tempDist;
                closestPt.push_back(shortestDist);
                closestPt.push_back(queryPairs.at(i).at(0));
                closestPt.push_back(queryPairs.at(i).at(1));
            }
        }
        //do transmitters care about users already on location, and if so, how?
    }
    return closestPt;
}

double Database::distance(double x1, double y1, double x2, double y2){
    double dist;
    double delx, dely;
    delx = abs(x2 - x1);
    dely = abs(y2 - y1);
    dist = sqrt(pow(delx,2) + pow(dely,2));
    return dist;
}
