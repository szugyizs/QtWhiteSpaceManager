#ifndef USER_H
#define USER_H
#include "device.h"
#include <QString>

class User : public virtual Device {
public:
    User();
    ~User();
    User(int rad, int x, int y, QString tID, double pow);
    User(int rad, int x, int y, double pow);
};
#endif
