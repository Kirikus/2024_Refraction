#ifndef CARTESIANPOINT_H
#define CARTESIANPOINT_H

class cartesianPoint{
private:
    double x, y, h;
public:
    cartesianPoint(double x_ax, double y_ax, double h_ax);
    double get_x();
    double get_y();
    double get_h();
};

#endif
