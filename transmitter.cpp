/**
 * @package QTWhiteSpaceManager
 * @module Transmitter.cpp
 * Source file of the Transmitter class.
 * ----------------------------
 * Updates
 * @date: 18/04/2019
 * @abstract: Added comments, indented code
 * @author:
 */

#include "transmitter.h"
#include <iostream>
using namespace std;

/**
  * Default empty constructor.
  */
Transmitter::Transmitter() { cout << "Transmitter object created." << endl; }

/**
  * Constructor for a fully parameterised Transmitter object.
  * Overloads the parent Device's (ID, power, radius, x, y) constructor.
  * @param ID: the ID of the Transmitter
  * @param pow: the power of the Transmitter
  * @param rad: the radius of the Transmitter
  * @param x: the X coordinate of the Transmitter
  * @param y: the Y coordinate of the Transmitter
  */
Transmitter::Transmitter(QString ID, double power, int radius, double x, double y) : Device (ID, power, radius, x, y)
{
    radius_ = radius;
    type_ = "T";
    x_ = x;
    y_ = y;
    ID_ = ID;
    power_ = power;
    cout << "Transmitter object created." << endl;
}

/**
  * Constructor for a Transmitter object only supplied its location and ID.
  * Overloads the parent Device's (x,y) constructor.
  * @param x: the X coordinate of the Transmitter
  * @param y: the Y coordinate of the Transmitter
  * @param ID: the ID of the Transmitter
  */
Transmitter::Transmitter(double x, double y, QString ID) : Device (x, y)
{
    radius_ = tR_;
    type_ = "T";
    x_ = x;
    y_ = y;
    ID_ = ID;
    power_ = tP_;
    cout << "Transmitter object created." << endl;
}

/**
  * Constructor for a Transmitter object only supplied its location.
  * Overloads the parent Device's (x,y) constructor.
  * @param x: the X coordinate of the Transmitter
  * @param y: the Y coordinate of the Transmitter
  */
Transmitter::Transmitter(double x, double y) : Device (x, y)
{
    radius_ = tR_;
    type_ = "T";
    x_ = x;
    y_ = y;
    power_ = tP_;
    cout << "Transmitter object created." << endl;
}

/**
  * Destructor for the Transmitter object.
  */
Transmitter::~Transmitter() { cout << "Transmitter object removed." << endl; } //TODO
