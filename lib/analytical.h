#ifndef ANALYTICAL_H
#define ANALYTICAL_H

#include "angle_difference_calculator.h"
#include "exponential_model.h"

class Analytical : public AngleDifferenceCalculator {
    public:
        // SRC: (2.44) from citation
        // psi_d : declination angle, radians
        // psi_g : sliding angle, radians
        // ha : flight altitude of the aircraft, m
        // hs : height of the target above sea level, m
        virtual double psi_d(double psi_g, double ha, double hs) override;

        // SRC: (2.44) from citation
        // psi_g : sliding angle, radians
        // psi_d : declination angle, radians
        // ha : flight altitude of the aircraft, m
        // hs : height of the target above sea level, m
        virtual double psi_g(double psi_d, double ha, double hs) override;

        Analytical(ExponentialModel atmosphere): atmosphere(atmosphere) {}

    private:
        ExponentialModel atmosphere;
        // Re: radious of the Earth
        double Re = 6378000;
};

#endif // ANALYTICAL_H
