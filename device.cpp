#include "device.h"
#include <iostream>
using namespace std;

Device::Device() {}
Device::Device(int rad, int x, int y, QString ID, double pow) : Geopoint(rad, x, y)
{
    radius_ = rad;
    x_ = x;
    y_ = y;
    ID_ = ID;
    power_ = pow;
}
Device::Device(int rad, int x, int y, double pow) : Geopoint(rad, x, y)
{
    radius_ = rad;
    x_ = x;
    y_ = y;
    power_ = pow;
}
Device::Device(int x, int y, QString ID, double pow) : Geopoint(x, y)
{
    radius_ = tR_;
    x_ = x;
    y_ = y;
    ID_ = ID;
    power_ = pow;
}
Device::Device(int x, int y, double pow) : Geopoint(x, y)
{
    radius_ = tR_;
    x_ = x;
    y_ = y;
    power_ = pow;
}
//Device::Device(QString ID, double pow, int rad, Geopoint* loc)
//{
//    ID_ = ID;
//    power_ = pow;
//    radius_ = rad;
//    location_ = (*loc);
//}
Device::~Device() { cout << "Device object removed." << endl; } //TODO

QString Device::getID() { return ID_; }
double Device::getPower() { return power_; }

void Device::setID(QString id) { ID_ = id; }
void Device::setPower(double pow) { power_ = pow; }
