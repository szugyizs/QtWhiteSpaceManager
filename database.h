#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QStandardItemModel>
#include <cmath>

class Database : public  QSqlDatabase {
public:
    Database();
    ~Database();

    QSqlError setupConnection(QString host, QString dbname, QString uname, int port, QString pw, QWidget *window);
    void closeConnection(QWidget *window);
    QSqlQuery setupModel();
    QVariantList addItem(QString type, int radius, double x, double y);
    QVariantList addModifiedItem(QString ID, QString type, double power, int radius, double x, double y);
    QString createID(QString type);
    QSqlError addBulk(QString type, QVariantList power, QVariantList radius, QVariantList x, QVariantList y);
    QSqlQuery getIDs(QString type);
    QSqlQuery getRow(QString ID);
    QSqlQuery getAllOfType(QString type);
    QSqlError removeRecords(QStringList rows);
    QVariantList checkInterference(double x, double y, QString type, QString ID);
    double distance(double x1, double y1, double x2, double y2);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
