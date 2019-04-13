#ifndef DEVICE_H
#define DEVICE_H
#include <QString>

class Device{
public:
    Device();
    virtual ~Device();
    Device(int rad, double x, double y, QString tID, double pow);
    Device(int rad, double x, double y);
    Device(double x, double y);

    double getX();
    double getY();
    void setX(double x);
    void setY(double y);
    int getRadius();
    void setRadius(int rad);
    QString getType();
    void setType(QString type);
    QString getID();
    void setID(QString id);
    double getPower();
    void setPower(double pow);

protected:
    QString ID_;
    QString type_;
    double power_;
    double x_;
    double y_;
    int tR_ = 6;
    double tP_ = 1000;
    double D_;
    int radius_;
};
#endif
