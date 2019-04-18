/**
 * @package QTWhiteSpaceManager
 * @module Database.h
 * Header file of Database class.
 * ----------------------------
 * Updates
 * @date: 18/04/2019
 * @abstract: Added comments, indented code
 * @author:
 */

#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QStandardItemModel>
#include "device.h"

class Database : public  QSqlDatabase {
public:
    Database();
    ~Database();

    QSqlError setupConnection(QString host, QString dbname, QString uname, int port, QString pw, QWidget *window);
    void closeConnection(QWidget *window);
    QSqlQuery setupModel();
    QVariantList addItem(Device *d);
    QVariantList addModifiedItem(Device *d);
    QString createID(QString type);
    QVariantList addBulk(QString type, QVariantList power, QVariantList radius, QVariantList x, QVariantList y);
    QSqlQuery getIDs(QString type);
    QSqlQuery getRow(QString ID);
    QSqlQuery getAllOfType(QString type);
    QSqlError removeRecords(QStringList rows);
    QVariantList checkInterference(double x, double y, QString type, QString ID);
    double distanceCoordinate(double x1d, double y1d, double x2d, double y2d);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
