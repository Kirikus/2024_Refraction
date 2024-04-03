#include "RefractionModel.h"
#include <cmath>

const int R_e = 6371000; //exemplary radius of the Earth



calculate_answer GeometricLine::calculate(float h_a, float h_s, float R){
    // all formulas were taken from the manual pages 37-38
    //formulas 2.8
    float term1 = h_a / R;
    float term2 = 1 - h_a / (2 * (R_e + h_a));
    float term3 = R / (2 * (R_e + h_a));
    float psi_d = asin(term1 * term2 + term3);

    float term4 = h_a / R;
    float term5 = 1 + h_a / (2 * R_e);
    float term6 = R / (2 * R_e);
    float psi_g = asin(term4 * term5 - term6);

    // formula 2.9
    float ksi_e = psi_d - psi_g;
    //formula 2.11
    float d = R_e * ksi_e;
    return calculate_answer(psi_d, psi_g, d);
}

calculate_answer EffectiveRadius::calculate(float h_a, float h_s, float R){
    // all formulas were taken from the manual pages 38-39
    float k_ = k(h_a, h_s, R);
    //formulas 2.12
    float term_h_a_R = h_a / R;
    float term_1 = 1 - h_a / (2 * (k_ * R_e + h_a));
    float term_R = R / (2 * (k_ * R_e + h_a));
    float psi_d = asin(term_h_a_R * term_1 + term_R);

    float term_h_a_R_2 = h_a / R;
    float term_2 = 1 + h_a / (2 * k_ * R_e);
    float term_R_2 = R / (2 * k_ * R_e);
    float psi_g = asin(term_h_a_R_2 * term_2 - term_R_2);

    //formula 2.14
    float ksi_e = psi_d - psi_g;
    //formula 2.16
    float d = k_ * R_e * ksi_e;

    return calculate_answer(psi_d, psi_g, d);
}

void AverageKAnalytical::SetAtmosphere(ExponentialModel model){
    atmosphere = model;
}

void AveragePAnalytical::SetAtmosphere(ExponentialModel model){
    atmosphere = model;
}

void AverageP::SetAtmosphere(ExponentialModel model){
    atmosphere = model;
}

float AverageKAnalytical::k(float h_a, float h_s, float R){
    //formula 2.9
    float term1 = h_a / R;
    float term2 = 1 + h_a / (2 * R_e);
    float term3 = R / (2 * R_e);
    float psi_g = asin(term1 * term2 - term3);

    //formula 2.38
    double H_b = atmosphere.Hb(); //Hb
    double N_s = atmosphere.N(1000); //Ns // затычка для h, вопрос по использованию так как в
    double term4 = H_b / (h_a - h_s);
    double term4_5 = ((pow(10, -6) * N_s * cos(psi_g) * R_e) / H_b);
    double term5 = exp((h_a - h_s) / H_b) - term4_5;
    double term6 = (pow(10, -6) * N_s * cos(psi_g) * R_e) / H_b;
    double term7 = 1 - term6;
    double k_avg = term4 * log(term5 / term7);

    return k_avg;
}

float AveragePAnalytical::k(float h_a, float h_s, float R){
    //formula 2.9
    float term1 = h_a / R;
    float term2 = 1 + h_a / (2 * R_e);
    float term3 = R / (2 * R_e);
    float psi_g = asin(term1 * term2 - term3);

    double H_b = atmosphere.Hb(); //Hb
    double N_s = atmosphere.N(1000); //Ns // затычка для h, вопрос по использованию так как в
    //formula 2.39
    float term4 = H_b / (pow(10, -6) * N_s * cos(psi_g));
    float term5 = exp((h_a - h_s) / H_b) - 1;
    float term6 = (h_a - h_s) / H_b;
    float p_avg = term4 * (term5 / term6);
    //formula 2.40
    float k_avg = 1 / (1 - (R_e/p_avg));
    return k_avg;
}



