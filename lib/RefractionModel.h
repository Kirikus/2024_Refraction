#include <iostream>
#include <vector>

#ifndef REFRACTIONMODEL_H
#define REFRACTIONMODEL_H


#include "exponential_model.cpp"

struct calculate_answer{
    float psi_d;
    float psi_g;
    float d;
    calculate_answer(float _psi_d , float _psi_g, float _d): psi_d(_psi_d), psi_g(_psi_g), d(_d) {};
};


class RefractionModel{
public:
    virtual calculate_answer calculate(float h_a, float h_s, float R) = 0;
    virtual float reverse(float h_a, float h_s, float R) = 0;
};

class GeometricLine : public RefractionModel{
public:
    calculate_answer calculate(float h_a, float h_s, float R) override;
    virtual float reverse(float h_a, float h_s, float R) override;
};

class GeometricRound : public RefractionModel{
public:
    virtual calculate_answer calculate(float h_a, float h_s, float R) = 0;
    virtual float reverse(float h_a, float h_s, float R) = 0;
};

class EffectiveRadius : public GeometricRound{
public:
    calculate_answer calculate(float h_a, float h_s, float R) override;
    virtual float k(float h_a, float h_s, float R) = 0;
    virtual float reverse(float h_a, float h_s, float R) = 0;
};

class FourThirds : public EffectiveRadius{
public:
    float k(float h_a, float h_s, float R) override { return 4/3;};
    virtual float reverse(float h_a, float h_s, float R) override;
};


class AveragePAnalytical : public EffectiveRadius{
public:
    float k(float h_a, float h_s, float R) override;
    void SetAtmosphere(const ExponentialModel &model);
    virtual float reverse(float h_a, float h_s, float R) override;
private:
    ExponentialModel atmosphere;
};

class AverageKAnalytical : public EffectiveRadius{
public:
    float k(float h_a, float h_s, float R) override;
    void SetAtmosphere(const ExponentialModel &model);
    virtual float reverse(float h_a, float h_s, float R) override;
private:
    ExponentialModel atmosphere;
};


class AverageP : public EffectiveRadius{
public:
    float k(float h_a, float h_s, float R) override;
    void SetAtmosphere(const ExponentialModel &model);
    virtual float reverse(float h_a, float h_s, float R) override;
private:
    ExponentialModel atmosphere;
};



#endif // REFRACTIONMODEL_H
