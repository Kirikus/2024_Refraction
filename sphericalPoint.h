#ifndef SPHERICPOINT_H
#define SPHERICPOINT_H

#include <iostream>
#include "pointAxes.h"

class sphericalPoint
{
private:
    double center, R, azimuth, phi;
public:
    sphericalPoint(point &center, point &position); // конструктор

    double get_x();
    double get_y();
    double get_h();
    double get_R();
    double get_phi();
};

#endif
