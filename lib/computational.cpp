#include "computational.h"
#include <iostream>

double Computational::psi_d(double psi_g, double ha, double hs) {
    double integral = 0;
    int steps = 1000;
    double dh = (ha - hs) / steps;
    for (int i = 1; i < steps; ++i) {
        integral += 1 / (1 + atmosphere.N(hs + i * dh) * 1e-6)
                * ((atmosphere.N(hs  + (i + 0.5) * dh) - atmosphere.N(hs  + (i - 0.5) * dh)) * 1e-6);
    }
    double numerator = (Re + hs) * exp(-integral) * cos(psi_g);
    double denumerator = Re + ha;
    return acos(numerator / denumerator);
}

double Computational::psi_g(double psi_d, double ha, double hs) {
    double integral = 0;
    int steps = 1000;
    double dh = (ha - hs) / steps;
    for (int i = 1; i < steps; ++i) {
        integral += 1 / (1 + atmosphere.N(hs + i * dh) * 1e-6)
                * ((atmosphere.N(hs  + i * dh) - atmosphere.N(hs  + (i - 1) * dh)) * 1e-6);
    }
    double numerator = (Re + ha) * cos(psi_d);
    double denumerator = (Re + hs) * exp(-integral);
    return acos(numerator / denumerator);
}
