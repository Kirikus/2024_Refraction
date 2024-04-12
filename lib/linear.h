#ifndef LINEAR_H
#define LINEAR_H

#include "function1D.h"

class Linear : public Function1D {
    public:
        Linear(std::vector<Point> points): points(points) {}
        virtual double y(double x) override;

    private:
        std::vector<Point> points;
};

#endif // LINEAR_H
