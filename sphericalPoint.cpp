#include <cmath>
#include "sphericalPoint.h"

sphericalPoint::sphericalPoint(point &center, point &position){
    double dx = center.X - position.X;
    double dy = center.Y - position.Y;
    double dh = center.H - position.H;
    R = sqrt(dx*dx + dy*dy +dh*dh);
    double d = sqrt(dx*dx + dy*dy);
    phi = acos(d/R);
    azimuth = atan(dy / dx);
}

double sphericalPoint::get_x(){
    return R*sin(phi)*cos(azimuth);
}

double sphericalPoint::get_y(){
    return R*sin(phi)*sin(azimuth);
}

double sphericalPoint::get_h(){
    return R*cos(phi);
}

double sphericalPoint::get_R(){
    return R;
}

double sphericalPoint::get_phi(){
    return phi;
}
