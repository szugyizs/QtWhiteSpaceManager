#ifndef DEVICE_H
#define DEVICE_H
#include <QString>

class Device{
public:
    Device();
    virtual ~Device();
    Device(int rad, int x, int y, QString tID, double pow);
    Device(int rad, int x, int y, double pow);
    Device(int x, int y, double pow);

    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
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
    int x_;
    int y_;
    int tR_ = 6;
    double tP_ = 1000;
    double D_;
    int radius_;
};
#endif
