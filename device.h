#ifndef DEVICE_H
#define DEVICE_H
#include "geopoint.h"
#include <QString>

class Device : public virtual Geopoint{
public:
    Device();
    ~Device();
    Device(int rad, int x, int y, QString tID, double pow);
    Device(int rad, int x, int y, double pow);
    Device(int x, int y, QString tID, double pow);
    Device(int x, int y, double pow);
//    Device(QString tID, double pow, int rad, Geopoint* loc);

    QString getID();
    void setID(QString id);
    double getPower();
    void setPower(double pow);

protected:
    QString ID_;
    double power_;
};
#endif
