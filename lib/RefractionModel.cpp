#include "RefractionModel.h"
#include <cmath>

const int R_e = 6371000; //exemplary radius of the Earth



calculate_answer GeometricLine::calculate(float h_a, float h_s, float R){
    // all formulas were taken from the manual pages 37-38
    //formulas 2.8
    float psi_d = asin((h_a/R)*(1 - h_a/(2*(R_e + h_a))) + R/(2*(R_e + h_a)));
    float psi_g = asin( h_a/R * (1 + h_a/(2 * R_e)) - R/(2 * R_e) );
    // formula 2.9
    float ksi_e = psi_d - psi_g;
    //formula 2.11
    float d = R_e * ksi_e;
    return calculate_answer(psi_d, psi_g, d);
}

calculate_answer EffectiveRadius::calculate(float h_a, float h_s, float R){
    // all formulas were taken from the manual pages 38-39
    float k_ = k();
    //formulas 2.12
    float psi_d = asin((h_a/R) * (1 - h_a/(2*(k_ * R_e + h_a))) + R/(2*(k_ * R_e + h_a)));
    float psi_g = asin(h_a/R * (1 + h_a/(2 * k_ * R_e)) - R/(2 * k_ * R_e) );
    //formula 2.14
    float ksi_e = psi_d - psi_g;
    //formula 2.16
    float d = k_ * R_e * ksi_e;

    return calculate_answer(psi_d, psi_g, d);
}

void AverageKAnalytical::SetAtmosphere(){
    ExponentialModel model;
    atmosphere = model;
}

void AveragePAnalytical::SetAtmosphere(){
    ExponentialModel model;
    atmosphere = model;
}

/*
void AverageP::SetAtmosphere(){
    ExponentialModel model;
    atmosphere = model;
}

float AverageP::k(float h_a, float h_s, float R){
    SetAtmosphere();
    float h = 8; // for now dont know where it will get from
    float H_b = 8; // its just a mock in future will be copy from SegmentedModel
    float psi_g = 1; // from page 46
    float p = 1 / (( (10^(-6) * atmosphere.Ns *cos(psi_g)) / H_b) * exp((-h + h_s) / H_b)); // formul 2.34
    float k_ = 1 / ( 1 - (R_e/ p));
    return k_;
}
*/


float AverageKAnalytical::k(float h_a, float h_s, float R){
    SetAtmosphere();
    //formula 2.9
    float psi_g = asin(h_a/R * (1 + h_a/(2 * R_e)) - R/(2 * R_e) );
    //formula 2.38
    k_avg = (atmosphere.H_b / (h_a - h_s)) * log((exp((h_a-h_s)/atmosphere.H_b) - (10^(-6) * atmosphere.N_s * cos(psi_g)*R_e)/atmosphere.H_b)/(1 - (10^(_6)*atmosphere.N_s*cos(psi_g)*R_e)/atmosphere.H_b) );
    return k_avg;
}

float AveragePAnalytical::k(float h_a, float h_s, float R){
    SetAtmosphere();
    //formula 2.9
    float psi_g = asin(h_a/R * (1 + h_a/(2 * R_e)) - R/(2 * R_e) );
    //formula 2.39
    float p_avg = (0atmosphere.H_b / (10^(-6) * atmosphere.N_s * cos(psi_g))) * ((exp((h_a-h_s)/atmosphere.H_b) - 1)/((h_a-h_s)/atmosphere.H_b));
    //formula 2.40
    float k_avg = 1 / (1 - (R_e/p_avg));
    return k_avg;
}



