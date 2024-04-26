#ifndef EXPONENTIAL_MODEL_H
#define EXPONENTIAL_MODEL_H

#include "atmospheric_model.h"

class ExponentialModel : public AtmosphericModel {
    public:
        // The dependence of the refractive index on height
        // SRC: (2.30, 2.31) from citation
        //    N : refractive index, []
        //    h : height above the sea level, [m]
        virtual double N(double h) override;

        // Ns : refractive index at the Earth's surface, []
        double Ns;

        ExponentialModel(double Ns = 324.8, double hs = 0): Ns(Ns), hs(hs) {}

        // SRC: (2.30) from citation
        double Hb();

    private:
        // hs : height of the surface above the level, [m]
        double hs;
};

#endif // EXPONENTIAL_MODEL_H
