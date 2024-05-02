#ifndef FUNCTION1D_H
#define FUNCTION1D_H

#include <vector>
#include <stdexcept>
#include <algorithm>

struct Point {
    double x;
    double y;
    Point(double x, double y) : x(x), y(y) {}
};

class Function1D {
    public:
        Function1D(const std::vector<double>& x_values, const std::vector<double>& y_values) {
                if(x_values.size() != y_values.size()) {
                    throw std::invalid_argument("X and Y vectors must have the same size");
                }

                for (size_t i = 0; i < x_values.size(); ++i) {
                    Point p(x_values[i], y_values[i]);
                    points.push_back(p);
                }

                std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
                        return a.x < b.x;
                    });
            }
        virtual double y(double x) = 0;

    protected:
        std::vector<Point> points;
};

#endif // FUNCTION1D_H
