#ifndef SEGMENTED_MODEL_H
#define SEGMENTED_MODEL_H

#include "atmospheric_model.h"
#include <cmath>

class SegmentedModel : public AtmosphericModel {
    public:
        // The dependence of the refractive index on height
        // SRC: (2.27) from citation
        //    N : refractive index, []
        //    h : height above the sea level, [m]
        virtual double N(double h) override;

        // Ns : refractive index at the Earth's surface, []
        double Ns = 324.8;
        // hs : height of the surface above the level, [m]
        double hs = 0;
        SegmentedModel(double Ns = 324.8, double hs = 0): Ns{Ns}, hs{hs} {}

    private:
        // Get linear coefficient of reduction of refractive index N by 1 m of height
        // SRC: (2.28) from citation
        double get_dN();

        // Get the exponential reduction constant of refractive index N
        // SRC: (2.28) from citation
        double get_H();

        // Get the refractive index at a height of 1 km above the surface
        // SRC: (2.27) from citation
        double get_N1();
};

#endif // SEGMENTED_MODEL_H
