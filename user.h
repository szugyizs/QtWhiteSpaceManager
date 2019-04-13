#ifndef USER_H
#define USER_H
#include "device.h"
#include <QString>

class User : public virtual Device {
public:
    User();
    ~User();
    User(int rad, double x, double y, QString ID, double pow);
    User(int rad, double x, double y, QString ID);
    User(int rad, double x, double y);
};
#endif
