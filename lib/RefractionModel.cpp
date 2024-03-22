#include "RefractionModel.h"
#include <cmath>

const int R_e = 6371000; //exemplary radius of the Earth



calculate_answer GeometricLine::calculate(float h_a, float h_s, float R){
    // all formulas were taken from the manual pages 37-38
    float psi_d = asin((h_a/R)*(1 - h_a/(2*(R_e + h_a))) + R/(2*(R_e + h_a)));
    float psi_g = asin( h_a/R * (1 + h_a/(2 * R_e)) - R/(2 * R_e) );
    float ksi_e = psi_d - psi_g;
    float d = R_e * ksi_e;
    return calculate_answer(psi_d, psi_g, d);
}

calculate_answer EffectiveRadius::calculate(float h_a, float h_s, float R){
    // all formulas were taken from the manual pages
    float k_ = k();
    float psi_d = asin((h_a/R) * (1 - h_a/(2*(k_ * R_e + h_a))) + R/(2*(k_ * R_e + h_a)));
    float psi_g = asin(h_a/R * (1 + h_a/(2 * k_ * R_e)) - R/(2 * k_ * R_e) );
    float ksi_e = psi_d - psi_g;
    float d = k_ * R_e * ksi_e;

    return calculate_answer(psi_d, psi_g, d);
}


/*
float AverageK::k(){
    float psi_g = asin(h_a/R * (1 + h_a/(2 * k_ * R_e)) - R/(2 * k_ * R_e) );
    k = 1 / ( 1 - ( (10^(-6) * N_s * cos(psi_g) * R_e)/ H_b) * exp(- (h - h_s)/H_b ) );
    return k;
}

float AverageKAnalytical::k(){
    k_avg = (H_b / (h_a - h_s)) * log((exp((h_a-h_s)/H_b) - (10^(-6)*N_s*cos(psi_g)*R_e)/H_b)/(1 - (10^(_6)*N_s*cos(psi_g)*R_e)/H_b) );
    return k_avg;
}

*/
