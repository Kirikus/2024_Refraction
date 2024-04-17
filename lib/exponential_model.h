#ifndef EXPONENTIAL_MODEL_H
#define EXPONENTIAL_MODEL_H

#include "atmospheric_model.h"

class ExponentialModel : public AtmosphericModel {
    public:
        // The dependence of the refractive index on height
        // SRC: (2.30, 2.31) from citation
        //    N : refractive index, []
        //    h : height above the sea level, [m]
    inline virtual double N(double h) override{return Ns * exp(-(h - hs) / Hb());};

        // Ns : refractive index at the Earth's surface, []
        // hs : height of the surface above the level, [m]
        ExponentialModel(double Ns = 324.8, double hs = 0): Ns(Ns), hs(hs) {}

        // SRC: (2.30) from citation
        inline double Hb(){
            double hb = 12192;
            double Nb = 66.65;
            return (hb - hs) / log(Ns / Nb);};

    private:
        double Ns;
        double hs;
};

#endif // EXPONENTIAL_MODEL_H
