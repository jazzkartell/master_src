#ifndef POINT2D_H
#define POINT2D_H

#include <string>

using namespace std;

class Point2D{
public:
    Point2D();
    void set_x(double x);
    void set_y(double y);
    void set_label(string label);
private:
    double x;
    double y;
    string label;
};



#endif