#include "device.h"
#include <iostream>
using namespace std;

Device::Device() { cout << "Device object created." << endl; }

Device::Device(int rad, double x, double y, QString ID, double pow)
{
    radius_ = rad;
    x_ = x;
    y_ = y;
    ID_ = ID;
    power_ = pow;
    cout << "Device object created." << endl;
}

Device::Device(int rad, double x, double y)
{
    x_ = x;
    y_ = y;
    radius_ = rad;
    cout << "Device object created." << endl;
}

Device::Device(double x, double y)
{
    x_ = x;
    y_ = y;
    cout << "Device object created." << endl;
}

Device::~Device() { cout << "Device object removed." << endl; } //TODO

QString Device::getID() { return ID_; }
QString Device::getType() { return type_; }
double Device::getPower() { return power_; }
int Device::getRadius() { return radius_; }
double Device::getX() { return x_; }
double Device::getY() { return y_; }

void Device::setID(QString id) { ID_ = id; }
void Device::setType(QString type) { type_ = type; }
void Device::setPower(double pow) { power_ = pow; }
void Device::setRadius(int rad) { radius_ = rad; }
void Device::setX(double x) { x_ = x; }
void Device::setY(double y) { y_ = y; }

