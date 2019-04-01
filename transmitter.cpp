#include "transmitter.h"
#include "device.h"
#include <iostream>
using namespace std;

Transmitter::Transmitter() {}

Transmitter::Transmitter(int x, int y, QString ID, double pow) : Device (x, y, ID, pow)
{
    radius_ = tR_;
    x_ = x;
    y_ = y;
    ID_ = ID;
    power_ = pow;
}
Transmitter::Transmitter(int x, int y, double pow) : Device (x, y, pow)
{
    radius_ = tR_;
    x_ = x;
    y_ = y;
    power_ = pow;
}

Transmitter::~Transmitter() { cout << "Transmitter object removed." << endl; } //TODO
