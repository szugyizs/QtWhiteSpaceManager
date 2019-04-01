#ifndef TRANSMITTER_H
#define TRANSMITTER_H
#include "device.h"
#include <QString>

class Transmitter : public virtual Device {
public:
    Transmitter();
    ~Transmitter();
    Transmitter(int x, int y, QString tID, double pow);
    Transmitter(int x, int y, double pow);
};
#endif
