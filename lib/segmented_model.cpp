#include "segmented_model.h"

double SegmentedModel::N(double h) {
    if (hs <= h && h <= hs + 1000) {
        return Ns + (h - hs) * dN();
    }
    if (hs + 1000 <= h && h <= 9000) {
        return N1() * exp(-(h - hs - 1000) / H());
    }
    if (h > 9000) {
        return 105 * exp(-(h - 9000) / 7023);
    }
    return 0;
}

double SegmentedModel::dN() {
    return -0.00732 * exp(0.005577 * Ns);
}

double SegmentedModel::H() {
    return (8000 - hs) / log(N1() / 105);
}

double SegmentedModel::N1() {
    return Ns + (1000 - hs) * dN();
}
