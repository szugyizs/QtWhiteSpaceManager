#include "transmitter.h"
#include "device.h"
#include <iostream>
using namespace std;

Transmitter::Transmitter() { cout << "Transmitter object created." << endl; }

Transmitter::Transmitter(int x, int y, QString ID, double pow) : Device (x, y, pow)
{
    radius_ = tR_;
    type_ = "T";
    x_ = x;
    y_ = y;
    ID_ = ID;
    power_ = pow;
    cout << "Transmitter object created." << endl;
}
Transmitter::Transmitter(int x, int y, double pow) : Device (x, y, pow)
{
    radius_ = tR_;
    type_ = "T";
    x_ = x;
    y_ = y;
    power_ = pow;
    cout << "Transmitter object created." << endl;
}

Transmitter::~Transmitter() { cout << "Transmitter object removed." << endl; } //TODO
