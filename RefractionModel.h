#include <iostream>
#include <vector>

#ifndef REFRACTIONMODEL_H
#define REFRACTIONMODEL_H



class RefractionModel{
public:
    virtual std::vector<float> calculate(float h_a, float h_s, float R) = 0;
    std::vector<float> reverse(float hs_a, float psi_d, float R);
};

class GeometricLine : public RefractionModel{
public:
    std::vector<float> calculate(float h_a, float h_s, float R) override;
};

class GeometricRound : public RefractionModel{
public:
    virtual std::vector<float> calculate(float h_a, float h_s, float R) = 0;
};

class EffectiveRadius : public GeometricRound{
public:
    std::vector<float> calculate(float h_a, float h_s, float R) override;
    virtual float k() = 0;
};

class FourThirds : public EffectiveRadius{
public:
    float k() override;
};

class AverageP : public EffectiveRadius{
public:
    float k() override;
    //atmosphere
};

class AverageK : public EffectiveRadius{
public:
    float k() override;
    //atmosphere
};

class AveragePAnalytical : public EffectiveRadius{
public:
    float k() override;
    //atmosphere
};

class AverageKAnalytical : public EffectiveRadius{
public:
    float k() override;
    //atmosphere
};

#endif // REFRACTIONMODEL_H
