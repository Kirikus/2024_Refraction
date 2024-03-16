#include "RefractionModel.h"
#include <cmath>

const int R_e = 6371000;

std::vector<float> GeometricLine::calculate(float h_a, float h_s, float R){
    float psi_d = asin((h_a/R)*(1 - h_a/(2*(R_e + h_a))) + R/(2*(R_e + h_a)));
    float psi_g = asin( h_a/R * (1 + h_a/(2 * R_e)) - R/(2 * R_e) );
    float ksi_e = psi_d - psi_g;
    float d = R_e * ksi_e;
    std::vector<float> answer{psi_d, psi_g, d};
    return answer;
}


float FourThirds::k(){
    float answer = 4/3;
    return answer;
}

std::vector<float> EffectiveRadius::calculate(float h_a, float h_s, float R){
    float k_ = k();
    float psi_d = asin((h_a/R) * (1 - h_a/(2*(k_ * R_e + h_a))) + R/(2*(k_ * R_e + h_a)));
    float psi_g = asin(h_a/R * (1 + h_a/(2 * k_ * R_e)) - R/(2 * k_ * R_e) );
    float ksi_e = psi_d - psi_g;
    float d = k_ * R_e * ksi_e;
    std::vector<float> answer{psi_d, psi_g, d};
    return answer;
}


