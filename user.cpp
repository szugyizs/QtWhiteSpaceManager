#include "user.h"
#include <iostream>
using namespace std;

User::User() { cout << "User object created." << endl;};
User::User(int rad, double x, double y, QString ID, double pow) : Device (rad, x, y, ID, pow)
{
    radius_ = rad;
    x_ = x;
    y_ = y;
    ID_ = ID;
    power_ = pow;
    type_ = "U";
}
User::User(int rad, double x, double y, QString ID) : Device (rad, x, y)
{
    radius_ = rad;
    x_ = x;
    y_ = y;
    ID_ = ID;
    type_ = "U";
}
User::User(int rad, double x, double y) : Device (rad, x, y)
{
    radius_ = rad;
    x_ = x;
    y_ = y;
    type_ = "U";
}

User::~User() { cout << "User object removed." << endl; } //TODO
