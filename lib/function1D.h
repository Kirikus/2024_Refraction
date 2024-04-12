#ifndef FUNCTION1D_H
#define FUNCTION1D_H

#include <vector>

struct Point {
    double x;
    double y;
    Point(double x, double y) : x(x), y(y) {}
};

class Function1D {
    public:
        virtual double y(double x) = 0;
};

#endif // FUNCTION1D_H
