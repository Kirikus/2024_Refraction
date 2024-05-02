#ifndef CUBICSPLINE_H
#define CUBICSPLINE_H

#include "function1D.h"

struct CubicSplineCoefficients {
    double a, b, c, d;
};

class CubicSpline : public Function1D {
    public:
        CubicSpline(const std::vector<double>& x_values, const std::vector<double>& y_values);
        virtual double y(double x) override;

    private:
        std::vector<CubicSplineCoefficients> coefficients;
};

#endif // CUBICSPLINE_H
