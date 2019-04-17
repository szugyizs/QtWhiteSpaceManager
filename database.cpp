#include "database.h"
using namespace std;
#include <iostream>
#include <math.h>
#include <cmath>
#define earthRadiusKm 6371.0


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

QVariantList Database::addItem(QString type, int radius, double x, double y){
    QSqlQuery queryAdd;
    double power;
    QVariantList result;

    if (type.compare("U")==0){
        result = checkInterference(x, y, "U", nullptr);
        if (result.length()==3){
            if(!(result.at(0).toInt()>2)){ result.push_back(QSqlError("Device cannot be here, is in close proximity to another user.").text()); return result;}
        }
        result.clear();
    }

    result = checkInterference(x, y, "T", nullptr);

    if (type.compare("U")==0){
        if (result.length()==3){
            if(!(result.at(0).toInt()>6)){ result.push_back(QSqlError("Device cannot be here, is in close proximity to a transmitter.").text()); return result;}
            else if(!(result.at(0).toInt()>15)){ power = 1;}
            else { power = 4;}
        } else { power = 4;}
    }
    else{
        if (result.length()==3){
            if(!(result.at(0).toInt()>12)){ result.push_back(QSqlError("Transmitter cannot be here, is in close proximity to another transmitter.").text()); return result;}
        }
        power = 1000;
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

QVariantList Database::addModifiedItem(QString ID, QString type, double power, int radius, double x, double y){
    QSqlQuery queryAdd;
    QVariantList result;

    if (type.compare("U")==0){
        result = checkInterference(x, y, "U", nullptr);
        if(!(result.at(0).toInt()>2)){ result.push_back(QSqlError("Device cannot move here, is in close proximity to another user.").text()); return result;}
        result.clear();
    }

    result = checkInterference(x, y, "T", ID);

    if (type.compare("U")==0){
        if(!(result.at(0).toInt()>6)){ result.push_back(QSqlError("Device cannot move here, is in close proximity to a transmitter.").text()); return result;}
        else if(!(result.at(0).toInt()>15)){ power = 1;} //limited power
        else { power = 4;} //full power
    }
    else{
        if(!(result.at(0).toInt()>12)){ result.push_back(QSqlError("Transmitter cannot be moved here, is in close proximity to another transmitter.").text()); return result;}
    }
    queryAdd.prepare("UPDATE `whitespacetable` SET Type = ? , Power = ? , Radius = ? , X = ? , Y = ? WHERE ID = ?");
    queryAdd.addBindValue(type);
    queryAdd.addBindValue(power);
    queryAdd.addBindValue(radius);
    queryAdd.addBindValue(x);
    queryAdd.addBindValue(y);
    queryAdd.addBindValue(ID);
    result.push_back(power);

    if(queryAdd.exec()){ result.push_back(QSqlError().text()); }
    else{ result.push_back(queryAdd.lastError().text()); }
    return result;
}

//TODO
QVariantList Database::addBulk(QString type, QVariantList power, QVariantList radius, QVariantList x, QVariantList y){
    QSqlQuery queryBulk;
    QVariantList result;
    QVariantList out;
    QString tempType;
    double tempPower;
    int tempRad;
    double tempX;
    double tempY;


    for(int i=0; i<x.length(); i++){
        tempType=type;
        tempPower=power.at(i).toDouble();
        tempRad=radius.at(i).toInt();
        tempX=x.at(i).toDouble();
        tempY=y.at(i).toDouble();

        result = checkInterference(tempX, tempY, "T", nullptr);

        if(result.at(0).toInt()>12){
            tempPower = 1000;
            queryBulk.prepare("INSERT INTO whitespacetable (`Type`, `Power`, `Radius`, `X`, `Y`) VALUES (?, ?, ?, ?, ?)");
            queryBulk.addBindValue(tempType);
            queryBulk.addBindValue(tempPower);
            queryBulk.addBindValue(tempRad);
            queryBulk.addBindValue(tempX);
            queryBulk.addBindValue(tempY);

            if(queryBulk.exec()){ out.push_back(QString::number(i+1)); }
        }
    }
    return out;
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

QVariantList Database::checkInterference(double x, double y, QString type, QString ID){
    QSqlQuery *query = new QSqlQuery(db);
    if(type.compare("U")==0){
        if(ID==nullptr){
            query->prepare("select X, Y from whitespacetable where type='U'");
            query->exec();
        }
        else{
            query->prepare("select X, Y from whitespacetable where type='U' and not ID='"+ID+"'");
            query->exec();
        }
    }
    else {
        if(ID==nullptr){
            query->prepare("select X, Y from whitespacetable where type='T'");
            query->exec();
        }
        else{
            query->prepare("select X, Y from whitespacetable where type='T' and not ID='"+ID+"'");
            query->exec();
        }
    }

    QList<QVariantList> queryPairs;

    while (query->next()) {
        QVariantList temp;
        temp.push_back(query->value(0));
        temp.push_back(query->value(1));
        queryPairs.push_back(temp);
    }

    double shortestDist=99999999999;
    QVariantList closestPt;

    for(int i = 0; i<queryPairs.length();i++){
        double tempDist = distanceCoordinate(x,y,queryPairs.at(i).at(0).toDouble(),queryPairs.at(i).at(1).toDouble());
        if(tempDist<shortestDist){
            closestPt.clear();
            shortestDist = tempDist;
            closestPt.push_back(shortestDist);
            closestPt.push_back(queryPairs.at(i).at(0));
            closestPt.push_back(queryPairs.at(i).at(1));
        }
    }
    return closestPt;
}

// https://stackoverflow.com/questions/10198985/calculating-the-distance-between-2-latitudes-and-longitudes-that-are-saved-in-a
/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in miles
 */
double Database::distanceCoordinate(double x1d, double y1d, double x2d, double y2d) {
  double y1r, x1r, y2r, x2r, u, v;
  y1r = (y1d* M_PI / 180);
  x1r = (x1d* M_PI / 180);
  y2r = (y2d* M_PI / 180);
  x2r = (x2d* M_PI / 180);

  u = sin((y2r - y1r)/2);
  v = sin((x2r - x1r)/2);

  return (2.0 * earthRadiusKm * asin(sqrt(u * u + cos(y1r) * cos(y2r) * v * v)))/1.609;
}
