/**
 * @package QTWhiteSpaceManager
 * @module Database.cpp
 * The class containing all the functions and variables belonging with the operations
 * of the Database.
 * ----------------------------
 * Updates
 * @date: 18/04/2019
 * @abstract: Added comments, indented code
 * @author:
 */

#include "database.h"
using namespace std;
#include <iostream>
#include <math.h>
#include <cmath>
#define earthRadiusKm 6371.0

/**
 * The constructor to a database object.
 */
Database::Database(){cout<<"Database object created."<<endl;}
/**
 * The deconstructor to a database object.
 */
Database::~Database() { cout << "Database object removed." << endl; }
QSqlDatabase db;

/**
 * A function to connect to a MySql database.
 * @param host: the host name to connect to
 * @param dbname: the database to connect to
 * @param uname: the username to allow access to the database
 * @param port: the port on which the database listens/communicates
 * @param pw: the password to allow access to the database
 * @param window: the parent object
 * @return the last if any error produced during the execution of the connection setup
 */
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

/**
 * A function to close the connection to the database.
 * @param window
 */
void Database::closeConnection(QWidget *window){
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
    QMessageBox::warning(window,"Connection closed","Database connection closed");
}

/**
 * A query to fill up the database window table with all the data in the database table
 * @return
 */
QSqlQuery Database::setupModel(){
    QSqlQuery *query = new QSqlQuery(db);
    query->prepare("select * from whitespacetable");
    query->exec();
    return *query;
}

/**
 * A function to add a new item to a database.
 * @param d: the device to be added
 * @return: a range of messages relating to nearby devices, power levels and any errors that occured.
 */
QVariantList Database::addItem(Device *d){
    QSqlQuery queryAdd;
    double power;
    QVariantList result;

    QString type = d->getType();
    int radius = d->getRadius();
    double x = d->getX();
    double y = d->getY();

    if (type.compare("U")==0){
        result = checkInterference(x, y, "U", nullptr);
        if (result.length()==3){    //if it's close to another user, add error
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
        }
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

/**
 * A function to modify the details of an item in the database.
 * @param d: the device to be modified
 * @return a range of messages relating to nearby devices, power levels, and any errors produced
 */
QVariantList Database::addModifiedItem(Device *d){
    QSqlQuery queryAdd;
    QVariantList result;

    QString type = d->getType();
    double power = d->getPower();
    int radius = d->getRadius();
    double x = d->getX();
    double y = d->getY();
    QString ID = d->getID();

    // if it's a user added, check for nearby users first
    if (type.compare("U")==0){
        result = checkInterference(x, y, "U", ID);
        if(!(result.at(0).toInt()>2)){ result.push_back(QSqlError("Device cannot move here, is in close proximity to another user.").text()); return result;}
        result.clear();
    }

    //check for any transmitters with which interference may occur
    result = checkInterference(x, y, "T", ID);

    //action based on the length of the distance
    if (type.compare("U")==0){
        if(!(result.at(0).toInt()>6)){ result.push_back(QSqlError("Device cannot move here, is in close proximity to a transmitter.").text()); return result;}
        else if(!(result.at(0).toInt()>15)){ power = 1;} //limited power
        else { power = 4;} //full power
    }
    else{
        if(!(result.at(0).toInt()>12)){ result.push_back(QSqlError("Transmitter cannot be moved here, is in close proximity to another transmitter.").text()); return result;}
    }

    //if passed without errors, update record in table
    queryAdd.prepare("UPDATE `whitespacetable` SET Type = ? , Power = ? , Radius = ? , X = ? , Y = ? WHERE ID = ?");
    queryAdd.addBindValue(type);
    queryAdd.addBindValue(power);
    queryAdd.addBindValue(radius);
    queryAdd.addBindValue(x);
    queryAdd.addBindValue(y);
    queryAdd.addBindValue(ID);
    //inform the user gui about the power
    result.push_back(power);

    if(queryAdd.exec()){ result.push_back(QSqlError().text()); }
    else{ result.push_back(queryAdd.lastError().text()); }
    return result;
}

/**
  * A function to bulk add n number of records to the database, while validating whichever is allowed to.
*/
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

            if(queryBulk.exec()){ out.push_back(QString::number(i+1)); } //add the index(by table view) of each record that succeeded in adding
        }
    }
    return out;
}

/**
 * A function to get all the IDs of all the devices of a set type
 * @param type: the type of records which are to be retrieved
 * @return the query: the list of values retrieved from the database
 */
QSqlQuery Database::getIDs(QString type){
    QSqlQuery *query = new QSqlQuery(db);
    query->prepare("select ID from whitespacetable where type='"+type+"'");
    query->exec();
    return *query;
}

/**
 * A function to get all of the values of a row with a selected ID.
 * @param ID: the primary key with which the record is identifyable
 * @return: the query: the list of values retrieved from the database
 */
QSqlQuery Database::getRow(QString ID){
    QSqlQuery *query = new QSqlQuery(db);
    query->prepare("select * from whitespacetable where ID='"+ID+"'");
    query->exec();
    return *query;
}

/**
 * @brief A function to get all records with the specified type.
 * @param type: the type of device sought after
 * @return the query: the list of values retrieved from the database
 */
QSqlQuery Database::getAllOfType(QString type){
    QSqlQuery *query = new QSqlQuery(db);
    query->prepare("select * from whitespacetable where type='"+type+"'");
    query->exec();
    return *query;
}

/**
 * A function to remove selected items from the database
 * @param rows: the list of IDs selected
 * @return the last, if any errors occurring
 */
QSqlError Database::removeRecords(QStringList rows){
    QSqlQuery queryBulkRemove;
    //bulk remove source: https://lists.qt-project.org/pipermail/qt-interest-old/2011-September/035927.html
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

/**
 * A function to evaluate what distance an item added/modified is from the closest devices,
 * and whether that distance has any implications towards the power.
 * @param x: added/modified item X coord
 * @param y: added/modified item Y coord
 * @param type: the type of device to check for
 * @param ID: ID of device modified or flag that item is newly created and has no ID
 * @return: a list of messages with the shortest distance to the selected type of device,
 * the x and y coordinates of that device, the power set for a user if applicable,
 * and any error messages that may occur.
 */
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

// distanceCoordinate source: https://stackoverflow.com/questions/10198985/calculating-the-distance-between-2-latitudes-and-longitudes-that-are-saved-in-a
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

    return (2.0 * earthRadiusKm * asin(sqrt(u * u + cos(y1r) * cos(y2r) * v * v)))/1.609; //divided by 1.609 to get miles for output
}
