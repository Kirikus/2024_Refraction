#ifndef LAYERED_MODEL_H
#define LAYERED_MODEL_H

#include "atmospheric_model.h"
#include <vector>

class LayeredModel: public AtmosphericModel {
    public:
        // The dependence of the refractive index on height
        //    N : refractive index, []
        //    h : height above the sea level, [m]
        virtual double N(double h) override;

        LayeredModel(const std::vector<AtmosphericModel*> &atmospheres, const std::vector<double> &heights): models{atmospheres}, heights{heights} {}

    private:
        std::vector<AtmosphericModel*> models;
        std::vector<double> heights;
};

#endif // LAYERED_MODEL_H
