/**
 * @package QTWhiteSpaceManager
 * @module Device.cpp
 * Source file of the parent class Device.
 * ----------------------------
 * Updates
 * @date: 18/04/2019
 * @abstract: Added comments, indented code
 * @author:
 */

#include "device.h"
#include <iostream>
using namespace std;

//-----------Constructors/destructor-----------
/**
  * Default empty constructor.
  */
Device::Device() { cout << "Device object created." << endl; }

/**
  * Constructor for a fully parameterised Device object.
  * @param ID: the ID of the Device
  * @param pow: the power of the Device
  * @param rad: the radius of the Device
  * @param x: the X coordinate of the Device
  * @param y: the Y coordinate of the Device
  */
Device::Device(QString ID, double pow, int rad, double x, double y)
{
    radius_ = rad;
    x_ = x;
    y_ = y;
    ID_ = ID;
    power_ = pow;
    cout << "Device object created." << endl;
}

/**
  * Constructor for a Device object only supplied its location.
  * @param x: the X coordinate of the Device
  * @param y: the Y coordinate of the Device
  */
Device::Device(double x, double y)
{
    x_ = x;
    y_ = y;
    cout << "Device object created." << endl;
}

/**
  * Destructor for the Device object.
  */
Device::~Device() { cout << "Device object removed." << endl; } //TODO

//-----------Getters-----------
/**
  * Accessing the ID of the Device from a non-dependent class.
  * @return ID_: the ID of the Device
  */
QString Device::getID() { return ID_; }

/**
  * Accessing the Type of the Device from a non-dependent class.
  * @return type_: the type of the Device
  */
QString Device::getType() { return type_; }

/**
  * Accessing the Power of the Device from a non-dependent class.
  * @return power_: the power of the Device
  */
double Device::getPower() { return power_; }

/**
  * Accessing the radius of the Device from a non-dependent class.
  * @return radius_: the radius of the Device
  */
int Device::getRadius() { return radius_; }

/**
  * Accessing the X coordinate of the Device from a non-dependent class.
  * @return x_: the X coordinate of the Device
  */
double Device::getX() { return x_; }

/**
  * Accessing the Y coordinate of the Device from a non-dependent class.
  * @return y_: the Y coordinate of the Device
  */
double Device::getY() { return y_; }

//-----------Setters-----------
/**
  * Accessing the ID of the Device from a non-dependent class.
  * @param ID_: the ID of the Device
  */
void Device::setID(QString id) { ID_ = id; }

/**
  * Accessing the Type of the Device from a non-dependent class.
  * @param type_: the type of the Device
  */
void Device::setType(QString type) { type_ = type; }

/**
  * Accessing the Power of the Device from a non-dependent class.
  * @param power_: the power of the Device
  */
void Device::setPower(double pow) { power_ = pow; }

/**
  * Accessing the radius of the Device from a non-dependent class.
  * @param radius_: the radius of the Device
  */
void Device::setRadius(int rad) { radius_ = rad; }

/**
  * Accessing the X coordinate of the Device from a non-dependent class.
  * @param x_: the X coordinate of the Device
  */
void Device::setX(double x) { x_ = x; }

/**
  * Accessing the Y coordinate of the Device from a non-dependent class.
  * @return y_: the Y coordinate of the Device
  */
void Device::setY(double y) { y_ = y; }

