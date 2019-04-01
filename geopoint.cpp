#include "geopoint.h"
#include <iostream>
using namespace std;

Geopoint::Geopoint(){}
Geopoint::Geopoint(int x, int y){
    x_=x;
    y_=y;
}
Geopoint::Geopoint(int rad, int x, int y){
    radius_=rad;
    x_=x;
    y_=y;
}
Geopoint::~Geopoint() { cout << "Geolocation object removed." << endl; } //TODO

int Geopoint::getRadius() { return radius_; }
int Geopoint::getX() { return x_; }
int Geopoint::getY() { return y_; }
//Geopoint Geopoint::getLocation() { return location_; }

void Geopoint::setRadius(int rad) { radius_ = rad; }
void Geopoint::setX(int x) { x_ = x; }
void Geopoint::setY(int y) { y_ = y; }
//void Geopoint::setLocation(int x, int y) {  } //TODO

double distance(double x1, double y1, double x2, double y2){
    //maths to calculate distance
    return 1234;
}

