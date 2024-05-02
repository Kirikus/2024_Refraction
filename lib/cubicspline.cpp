#include "cubicspline.h"

CubicSpline::CubicSpline(const std::vector<double>& x_values, const std::vector<double>& y_values) : Function1D(x_values, y_values) {
    int n = points.size() - 1;

    std::vector<double> h(n);
    std::vector<double> alpha(n);
    std::vector<double> l(n + 1);
    std::vector<double> mu(n);
    std::vector<double> z(n + 1);

    for (int i = 0; i <= n - 1; ++i)
        h[i] = points[i + 1].x - points[i].x;

    for (int i = 1; i <= n - 1; ++i)
        alpha[i] = 3 * ((points[i + 1].y - points[i].y) / h[i] - (points[i].y - points[i - 1].y) / h[i - 1]);

    l[0] = 1;
    mu[0] = 0;
    z[0] = 0;

    for (int i = 1; i <= n - 1; ++i) {
        l[i] = 2 * (points[i + 1].x - points[i - 1].x) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n] = 1;
    z[n] = 0;

    std::vector<double> c(n + 1, 0);
    std::vector<double> b(n, 0);
    std::vector<double> d(n, 0);

    for (int j = n - 1; j >= 0; --j) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (points[j + 1].y - points[j].y) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
    }

    for (int i = 0; i <= n - 1; ++i) {
        coefficients.push_back({points[i].y, b[i], c[i], d[i]});
    }
}

double CubicSpline::y(double x) {
    for (int j = 0; j < coefficients.size(); ++j) {
        if (points[j].x <= x && x <= points[j + 1].x) {
            double h = x - points[j].x;
            return coefficients[j].a +
                   coefficients[j].b * h +
                   coefficients[j].c * h * h +
                   coefficients[j].d * h * h * h;
        }
    }
    return 0; // Return 0 if x is outside the range
}
