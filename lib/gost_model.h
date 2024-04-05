#ifndef GOST_MODEL_H
#define GOST_MODEL_H

#include "atmospheric_model.h"
#include "function1D.h"

class GOSTModel : public AtmosphericModel {
    public:
        // The dependence of the refractive index on height
        // SRC: (2.23, 2.24) from citation
        //    N : refractive index, []
        //    h : height above the sea level, [m]
        virtual double N(double h) override;

        // P_h : pressure depending on height, [mbar]
        // T_h : temperature depending on height, [K]
        GOSTModel(Function1D* P_h, Function1D* T_h): P_h(P_h), T_h(T_h){}

        // The dependence of the density on height
        // SRC: (2.25, 2.26) from citation
        //    rho_w : density, [g/m**3]
        //    h : height above the sea level, [m]
        double rho_w(double h);

    private:
        Function1D* P_h;
        Function1D* T_h;
};

#endif // GOST_MODEL_H
