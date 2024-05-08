#include <iostream>
#include <vector>
#include <memory>

#ifndef REFRACTIONMODEL_H
#define REFRACTIONMODEL_H

#include "atmospheric_model.h"
#include "exponential_model.h"

struct calculate_answer{
    float psi_d;
    float psi_g;
    float d;
    calculate_answer(float _psi_d , float _psi_g, float _d): psi_d(_psi_d), psi_g(_psi_g), d(_d) {};
};


class RefractionModel{
public:
    virtual calculate_answer calculate(float h_a, float h_s, float R) = 0;
    float reverse(float h_a, float h_s_guess, float R, float psi_d);
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
    virtual float k(float h_a, float h_s, float R) = 0;
};

class FourThirds : public EffectiveRadius{
public:
    float k(float h_a, float h_s, float R) override { return 4/3;};
};

class AveragePAnalytical : public EffectiveRadius{
public:
    float k(float h_a, float h_s, float R) override;
    void SetAtmosphere(std::unique_ptr<AtmosphericModel> model);
private:
    std::unique_ptr<ExponentialModel> atmosphere;
};


class AverageKAnalytical : public EffectiveRadius{
public:
    float k(float h_a, float h_s, float R) override;
    void SetAtmosphere(std::unique_ptr<AtmosphericModel> model);
private:
    std::unique_ptr<ExponentialModel> atmosphere;
};


class AverageP : public EffectiveRadius{
public:
    float k(float h_a, float h_s, float R) override;
    void SetAtmosphere(std::unique_ptr<AtmosphericModel> model);
private:
    std::unique_ptr<AtmosphericModel> atmosphere;
};

class AverageK : public EffectiveRadius{
public:
    float k(float h_a, float h_s, float R) override;
    void SetAtmosphere(std::unique_ptr<AtmosphericModel> model);
private:
    std::unique_ptr<AtmosphericModel> atmosphere;
};

#endif // REFRACTIONMODEL_H
