#include "user.h"
#include <iostream>
using namespace std;

User::User() { cout << "User object created." << endl;}
User::User(QString ID, double pow, int rad, double x, double y) : Device (ID, pow, rad, x, y)
{
    radius_ = rad;
    x_ = x;
    y_ = y;
    ID_ = ID;
    power_ = pow;
    type_ = "U";
}
User::User(double x, double y, QString ID) : Device (x, y)
{
    radius_ = uR_;
    x_ = x;
    y_ = y;
    ID_ = ID;
    type_ = "U";
}
User::User(double x, double y) : Device (x, y)
{
    radius_ = uR_;
    x_ = x;
    y_ = y;
    type_ = "U";
}

User::~User() { cout << "User object removed." << endl; } //TODO
