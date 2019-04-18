/**
 * @package QTWhiteSpaceManager
 * @module Transmitter.h
 * Header file for Transmitter class.
 * ----------------------------
 * Updates
 * @date: 18/04/2019
 * @abstract: Added comments, indented code
 * @author:
 */

#ifndef TRANSMITTER_H
#define TRANSMITTER_H
#include "device.h"
#include <QString>

class Transmitter : public Device {
public:
    Transmitter();
    ~Transmitter();
    Transmitter(QString id, double pow, int rad, double x, double y);
    Transmitter(double x, double y, QString ID);
    Transmitter(double x, double y);
};
#endif
