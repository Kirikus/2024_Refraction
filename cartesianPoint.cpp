#include "cartesianPoint.h"


cartesianPoint::cartesianPoint(double x_ax, double y_ax, double h_ax){
    x = x_ax;
    y = y_ax;
    h = h_ax;
}

double cartesianPoint::get_x(){
    return x;
}

double cartesianPoint::get_y(){
    return y;
}

double cartesianPoint::get_h(){
    return h;
}
