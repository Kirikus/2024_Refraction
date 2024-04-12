#include "linear.h"

double Linear::y(double x) {
    for (int i = 0; i < points.size()-1; i++) {
        if (points[i].x <= x && x <= points[i+1].x) {
            double slope = (points[i+1].y - points[i].y) / (points[i+1].x - points[i].x);
            return points[i].y + slope * (x - points[i].x);
        }
    }
    return 0; // Return 0 if x is outside the range
}
