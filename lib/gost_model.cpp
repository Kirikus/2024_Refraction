#include "gost_model.h"

template <class P_MODEL, class T_MODEL>
double GOSTModel<P_MODEL, T_MODEL>::rho_w(double h) {
    double rh = 0.6;
    double pho_w_max = 12.8;
    const double pho_w0 = pho_w_max * rh;
    const double h_1 = 2000;
    const double h_2 = 8000;
    const double slope_low = 0.2523 / 1000;
    const double rho_w_h_1 = (1 - slope_low * h_1);
    const double slope_mid = 1861;
    const double rho_w_h_2 = rho_w_h_1 * std::exp(-(h_2 - 2000) / slope_mid);
    const double slope_high = 1158;

    if (h < h_1)
      return pho_w0 * (1 - slope_low * h);
    else if (h < h_2)
      return pho_w0 * rho_w_h_1 * std::exp(-(h - h_1) / slope_mid);
    else
      return pho_w0 * rho_w_h_2 * std::exp(-(h - h_2) / slope_high);
}

template <class P_MODEL, class T_MODEL>
double GOSTModel<P_MODEL, T_MODEL>::N(double h) {
    double T = T_h->y(h);
    double P = P_h->y(h);
    double e = T * rho_w(h) / 216.68;
    return 77.6 / T * (P + 4810 * e / T);
}

template class GOSTModel<Function1D*, Function1D*>;
