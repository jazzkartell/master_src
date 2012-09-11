#include "Point2D.h"

#include <string>

using namespace std;

Point2D::Point2D(){}

void Point2D::set_x(double x){
    this->x = x;
}

void Point2D::set_y(double y){
    this->y = y;
}

void Point2D::set_label(string label){
    this->label = label;
}