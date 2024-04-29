#include "angle_difference_calculator.h"

double AngleDifferenceCalculator::d(double psi_g, double ha, double hs) {
    double N = 1000;
    double dh = (hs - ha) / N;
    double integral = 0;
    for (int i = 0; i <= N; ++i) {
        double cos_psi = cos(psi_d(psi_g, ha, ha + dh * i));
        if (cos_psi != 1.0)
            integral += cos_psi / sqrt(1 - cos_psi * cos_psi) * dh;
    }
    return integral;
}
