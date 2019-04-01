#ifndef DATABASE_H
#define DATABASE_H

#include <list>
#include "device.h"
#include "ui_databasedialog.h"
#include <QUuid>
#include <QHash>
#include <QFile>

class Database
{
public:
    Database();
    //Database();
    ~Database();
//    Database(QFile in, QFile out); //TODO do we need this
//    Database(QFile out);    //TODO do we need this

    void addDevice(Device d, char t);
    Device getDevice(QString id);
    void removeDevice(QString id);

    void modifyDevice(QString id, Device d);

    //check against distances
    //  check against power <-where do these funct go
    //TODO
private:
    QHash<QString, Device> deviceList_;
    QUuid uuid;
//    QFile inFile;    //TODO do we need this
//    QFile outFile;    //TODO do we need this
};

#endif // DATABASE_H
