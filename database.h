#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>

class Database : public  QSqlDatabase {
public:
    Database();
    ~Database();

    QSqlError setupConnection(QString host, QString dbname, QString uname, int port, QString pw, QWidget *window);
    void closeConnection(QWidget *window);
    QSqlQuery setupModel();
    QSqlError addItem(QString type, double power, int radius, float x, float y);
    QSqlError addModifiedItem(QString ID, QString power, QString radius, QString x, QString y);
    QString createID(QString type);
    QSqlError addBulk(QString type, QVariantList power, QVariantList radius, QVariantList x, QVariantList y);
    QSqlQuery getIDs(QString type);
    QSqlQuery getRow(QString ID);
    QSqlQuery getAllOfType(QString type);

private:
    QSqlDatabase db;
};

#endif // DATABASE_H
