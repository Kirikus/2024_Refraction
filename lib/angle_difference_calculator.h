#ifndef ANGLE_DIFFERENCE_CALCULATOR_H
#define ANGLE_DIFFERENCE_CALCULATOR_H

#include <cmath>

class AngleDifferenceCalculator {
     public:
        // Range on the ground at the height of the target
        // SRC : (2.47) from citation
        // psi_g : sliding angle, radians
        // ha : flight altitude of the aircraft, m
        // hs : height of the target above sea level, m
        double d(double psi_g, double ha, double hs);

        // psi_d : declination angle, radians
        // psi_g : sliding angle, radians
        // ha : flight altitude of the aircraft, m
        // hs : height of the target above sea level, m
        virtual double psi_d(double psi_g, double ha, double hs) = 0;

        // psi_g : sliding angle, radians
        // psi_d : declination angle, radians
        // ha : flight altitude of the aircraft, m
        // hs : height of the target above sea level, m
        virtual double psi_g(double psi_d, double ha, double hs) = 0;
};

#endif // ANGLE_DIFFERENCE_CALCULATOR_H
