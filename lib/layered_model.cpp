#include "layered_model.h"

double LayeredModel::N(double h) {
    int i;
    for (i = 0; i < heights.size(); ++i)
        if (h < heights[i])
            break;
    return models[i]->N(h);
}
