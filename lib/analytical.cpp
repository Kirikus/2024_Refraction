#include "analytical.h"

double Analytical::psi_d(double psi_g, double ha, double hs) {
    double Ns = atmosphere.Ns;
    double Hb = atmosphere.Hb();
    double numerator = (1 + 1e-6 * Ns) * (Re + hs) * cos(psi_g);
    double denumerator = (1 + 1e-6 * Ns * exp(-(ha - hs) / Hb)) * (Re + ha);
    return acos(numerator / denumerator);
}

double Analytical::psi_g(double psi_d, double ha, double hs) {
    double Ns = atmosphere.Ns;
    double Hb = atmosphere.Hb();
    double numerator = (1 + 1e-6 * Ns * exp(-(ha - hs) / Hb)) * (Re + ha) * cos(psi_d);
    double denumerator = (1 + 1e-6 * Ns) * (Re + hs);
    return acos(numerator / denumerator);
}
