#ifndef TRANSMITTER_H
#define TRANSMITTER_H
#include "device.h"
#include <QString>

class Transmitter : public virtual Device {
public:
    Transmitter();
    ~Transmitter();
    Transmitter(int rad, double x, double y, QString id, double pow);
    Transmitter(double x, double y, QString ID);
    Transmitter(double x, double y);
};
#endif
