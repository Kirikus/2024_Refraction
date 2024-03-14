#include "model_rectilinear_propagation.h"

double calculate_d(double psi_d, double psi_g)
{
    double d = R_e * (psi_d - psi_g);
    return d;
}
