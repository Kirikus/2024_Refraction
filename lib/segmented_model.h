#ifndef SEGMENTED_MODEL_H
#define SEGMENTED_MODEL_H

#include "atmospheric_model.h"

class SegmentedModel : public AtmosphericModel {
    public:
        // The dependence of the refractive index on height
        // SRC: (2.27) from citation
        //    N : refractive index, []
        //    h : height above the sea level, [m]
        virtual double N(double h) override;

        // Ns : refractive index at the Earth's surface, []
        // hs : height of the surface above the level, [m]
        SegmentedModel(double Ns = 324.8, double hs = 0): Ns(Ns), hs(hs) {}

    private:
        double Ns;
        double hs;

        // Get linear coefficient of reduction of refractive index N by 1 m of height
        // SRC: (2.28) from citation
        double dN();

        // Get the exponential reduction constant of refractive index N
        // SRC: (2.28) from citation
        double H();

        // Get the refractive index at a height of 1 km above the surface
        // SRC: (2.27) from citation
        double N1();
};

#endif // SEGMENTED_MODEL_H
