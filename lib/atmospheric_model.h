#ifndef ATMOSPHERIC_MODEL_H
#define ATMOSPHERIC_MODEL_H

class AtmosphericModel {
    public:
        // The dependence of the refractive index on height
        virtual double N(double h) = 0;
};

#endif // ATMOSPHERIC_MODEL_H
