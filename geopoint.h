#ifndef GEOPOINT_H
#define GEOPOINT_H
class Geopoint {

public:
    Geopoint();
    Geopoint(int x, int y);
    Geopoint(int rad, int x, int y);
    ~Geopoint();

    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    int getRadius();
    void setRadius(int rad);

    //Geopoint getLocation();
    //void setLocation(int x, int y);
    double distance(double x1, double y1, double x2, double y2);

protected:

    int x_;
    int y_;
    int tR_ = 6;
    double D_;
    int radius_;
    //Geopoint location_;
};
#endif
