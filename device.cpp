#include "device.h"
#include <iostream>
#include <cmath>
using namespace std;

Device::Device() { cout << "Device object created." << endl; }

Device::Device(int rad, int x, int y, QString ID, double pow)
{
    radius_ = rad;
    x_ = x;
    y_ = y;
    ID_ = ID;
    power_ = pow;
    cout << "Device object created." << endl;
}
Device::Device(int rad, int x, int y, double pow)
{
    radius_ = rad;
    x_ = x;
    y_ = y;
    power_ = pow;
    cout << "Device object created." << endl;
}
Device::Device(int x, int y, double pow)
{
    radius_ = tR_;
    x_ = x;
    y_ = y;
    power_ = pow;
    cout << "Device object created." << endl;
}

Device::~Device() { cout << "Device object removed." << endl; } //TODO

QString Device::getID() { return ID_; }
QString Device::getType() { return type_; }
double Device::getPower() { return power_; }
int Device::getRadius() { return radius_; }
int Device::getX() { return x_; }
int Device::getY() { return y_; }

void Device::setID(QString id) { ID_ = id; }
void Device::setType(QString type) { type_ = type; }
void Device::setPower(double pow) { power_ = pow; }
void Device::setRadius(int rad) { radius_ = rad; }
void Device::setX(int x) { x_ = x; }
void Device::setY(int y) { y_ = y; }

double distance(double x1, double y1, double x2, double y2){
    double dist;
    double delx, dely;
    delx = abs(x2 - x1);
    dely = abs(y2 - y1);
    dist = sqrt(pow(delx,2) + pow(dely,2));
    return dist;
}
