/**
 * @package QTWhiteSpaceManager
 * @module User.cpp
 * Source file of the User class.
 * ----------------------------
 * Updates
 * @date: 18/04/2019
 * @abstract: Added comments, indented code
 * @author:
 */

#include "user.h"
#include <iostream>
using namespace std;

/**
  * Default empty constructor.
  */
User::User() { cout << "User object created." << endl;}

/**
  * Constructor for a fully parameterised User object.
  * Overloads the parent Device's (ID, power, radius, x, y) constructor.
  * @param ID: the ID of the User
  * @param pow: the power of the User
  * @param rad: the radius of the User
  * @param x: the X coordinate of the User
  * @param y: the Y coordinate of the User
  */
User::User(QString ID, double pow, int rad, double x, double y) : Device (ID, pow, rad, x, y)
{
    radius_ = rad;
    x_ = x;
    y_ = y;
    ID_ = ID;
    power_ = pow;
    type_ = "U";
}

/**
  * Constructor for a User object only supplied its location and ID.
  * Overloads the parent Device's (x,y) constructor.
  * @param x: the X coordinate of the User
  * @param y: the Y coordinate of the User
  * @param ID: the ID of the User
  */
User::User(double x, double y, QString ID) : Device (x, y)
{
    radius_ = uR_;
    x_ = x;
    y_ = y;
    ID_ = ID;
    type_ = "U";
}

/**
  * Constructor for a User object only supplied its location.
  * Overloads the parent Device's (x,y) constructor.
  * @param x: the X coordinate of the User
  * @param y: the Y coordinate of the User
  */
User::User(double x, double y) : Device (x, y)
{
    radius_ = uR_;
    x_ = x;
    y_ = y;
    type_ = "U";
}

/**
  * Destructor for the User object.
  */
User::~User() { cout << "User object removed." << endl; }
