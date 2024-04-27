#ifndef LAYERED_MODEL_H
#define LAYERED_MODEL_H

#include "atmospheric_model.h"
#include <vector>
#include <stdexcept>

class LayeredModel: public AtmosphericModel {
    public:
        // The dependence of the refractive index on height
        //    N : refractive index, []
        //    h : height above the sea level, [m]
        virtual double N(double h) override;

        LayeredModel(const std::vector<AtmosphericModel*> &atmospheres, const std::vector<double> &heights): models{atmospheres}, heights{heights} {
            if (heights.size() - 1 != models.size())
                throw std::invalid_argument("Number of heights should be one less than number of models");

            // Check if heights are sorted in increasing order
            for (size_t i = 0; i < heights.size() - 1; ++i)
                if (heights[i] >= heights[i + 1])
                    throw std::invalid_argument("Heights must be sorted in an increasing order");
        }

    private:
        std::vector<AtmosphericModel*> models;
        std::vector<double> heights;
};

#endif // LAYERED_MODEL_H
