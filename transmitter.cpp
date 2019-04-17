#include "transmitter.h"
#include "device.h"
#include <iostream>
using namespace std;

Transmitter::Transmitter() { cout << "Transmitter object created." << endl; }
Transmitter::Transmitter(QString ID, double power, int radius, double x, double y) : Device (ID, power, radius, x, y)
{
    radius_ = radius;
    type_ = "T";
    x_ = x;
    y_ = y;
    ID_ = ID;
    power_ = power;
    cout << "Transmitter object created." << endl;
}
Transmitter::Transmitter(double x, double y, QString ID) : Device (x, y)
{
    radius_ = tR_;
    type_ = "T";
    x_ = x;
    y_ = y;
    ID_ = ID;
    power_ = tP_;
    cout << "Transmitter object created." << endl;
}
Transmitter::Transmitter(double x, double y) : Device (x, y)
{
    radius_ = tR_;
    type_ = "T";
    x_ = x;
    y_ = y;
    power_ = tP_;
    cout << "Transmitter object created." << endl;
}
Transmitter::~Transmitter() { cout << "Transmitter object removed." << endl; } //TODO
