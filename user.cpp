#include "user.h"
#include <iostream>
using namespace std;

User::User() {};
User::User(int rad, int x, int y, QString ID, double pow) : Device (rad, x, y, ID, pow)
{
    radius_ = rad;
    x_ = x;
    y_ = y;
    ID_ = ID;
    power_ = pow;
}
User::User(int rad, int x, int y, double pow) : Device (rad, x, y, pow)
{
    radius_ = rad;
    x_ = x;
    y_ = y;
    power_ = pow;
}

User::~User() { cout << "User object removed." << endl; } //TODO
