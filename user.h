/**
 * @package QTWhiteSpaceManager
 * @module User.h
 * Header file for the User class.
 * ----------------------------
 * Updates
 * @date: 18/04/2019
 * @abstract: Added comments, indented code
 * @author:
 */


#ifndef USER_H
#define USER_H
#include "device.h"
#include <QString>

class User : public Device {
public:
    User();
    ~User();
    User(QString ID, double pow, int rad, double x, double y);
    User(double x, double y, QString ID);
    User(double x, double y);
};
#endif
