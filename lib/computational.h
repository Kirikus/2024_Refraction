#ifndef COMPUTATIONAL_H
#define COMPUTATIONAL_H

#include "angle_difference_calculator.h"
#include "atmospheric_model.h"

class Computational : public AngleDifferenceCalculator {
    public:
        // SRC: (2.42) from citation
        // psi_d : declination angle, radians
        // psi_g : sliding angle, radians
        // ha : flight altitude of the aircraft, m
        // hs : height of the target above sea level, m
        virtual double psi_d(double psi_g, double ha, double hs) override;

        // SRC: (2.42) from citation
        // psi_g : sliding angle, radians
        // psi_d : declination angle, radians
        // ha : flight altitude of the aircraft, m
        // hs : height of the target above sea level, m
        virtual double psi_g(double psi_d, double ha, double hs) override;

        Computational(AtmosphericModel &atmosphere): atmosphere(atmosphere) {}

    private:
        AtmosphericModel &atmosphere;
        // Re: radious of the Earth
        double Re = 6378000;
};

#endif // COMPUTATIONAL_H
