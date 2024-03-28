#include <iostream>
#include <vector>

#ifndef REFRACTIONMODEL_H
#define REFRACTIONMODEL_H

#include "segmented_model.h" // in future it will re-incldue by exponential_model

struct calculate_answer{
    float psi_d;
    float psi_g;
    float d;
    calculate_answer(float _psi_d , float _psi_g, float _d): psi_d(_psi_d), psi_g(_psi_g), d(_d) {};
};

class RefractionModel{
public:
    virtual calculate_answer calculate(float h_a, float h_s, float R) = 0;
    float reverse(float hs_a, float psi_d, float R);
};

class GeometricLine : public RefractionModel{
public:
    calculate_answer calculate(float h_a, float h_s, float R) override;
};

class GeometricRound : public RefractionModel{
public:
    virtual calculate_answer calculate(float h_a, float h_s, float R) = 0;
};

class EffectiveRadius : public GeometricRound{
public:
    calculate_answer calculate(float h_a, float h_s, float R) override;
    virtual float k() = 0;
};

class FourThirds : public EffectiveRadius{
public:
    float k() override { return 4/3;};
};

/*
class AveragePAnalytical : public EffectiveRadius{
public:
    float k(float h_a, float h_s, float R); // override ?
    void SetAtmosphere();
private:
    ExponentialModel atmosphere;
};

class AverageKAnalytical : public EffectiveRadius{
public:
    float k(float h_a, float h_s, float R); // override ?
    void SetAtmosphere();
private:
    ExponentialModel atmosphere;
};


// will be done in future commits
class AverageK : public EffectiveRadius{
public:
    float k() override;
    void SetAtmosphere(SegmentedModel atmosphere);
private:
    SegmentedModel atmosphere;
};

class AverageP : public EffectiveRadius{
public:
    float k(float h_a, float h_s, float R); // override ?
    void SetAtmosphere();
private:
    ExponentialModel atmosphere;
};

*/

#endif // REFRACTIONMODEL_H
