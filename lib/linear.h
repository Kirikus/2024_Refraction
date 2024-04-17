#ifndef LINEAR_H
#define LINEAR_H

#include "function1D.h"

class Linear : public Function1D {
    public:
        Linear(const std::vector<double>& x_values, const std::vector<double>& y_values) : Function1D(x_values, y_values) {}
        virtual double y(double x) override;
};

#endif // LINEAR_H
