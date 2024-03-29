#include "exponential_model.h"

double ExponentialModel::N(double h) {
    return Ns * exp(-(h - hs) / Hb());
}

double ExponentialModel::Hb() {
    double hb = 12192;
    double Nb = 66.65;
    return (hb - hs) / log(Ns / Nb);
}
