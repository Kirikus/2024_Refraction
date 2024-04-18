#include "RefractionModel.h"
#include <cmath>

const int R_e = 6371000; //exemplary radius of the Earth


calculate_answer GeometricLine::calculate(float h_a, float h_s, float R){
    // all formulas were taken from the manual pages 37-38
    //formulas 2.8
    if (!(h_a >0) or !(h_s >0) or !(R >0)){
        std::cerr<<"incorrect values supplied"<<std::endl;
    }

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
    if (!(h_a >0) or !(h_s >0) or !(R >0)){
        std::cerr<<"incorrect values supplied"<<std::endl;
    }
    float k_ = k(h_a, h_s, R);
    //formulas 2.17
    float term_h_a_R = (h_a - h_s) / R;
    float term_1 = 1 - (h_a - h_s) / (2 * (k_ * R_e + h_a));
    float term_R = R / (2 * (k_ * R_e + h_a));
    float psi_d = asin(term_h_a_R * term_1 + term_R);

    float term_h_a_R_2 = (h_a - h_s) / R;
    float term_2 = 1 + (h_a - h_s) / (2 * (k_ * R_e + h_s));
    float term_R_2 = R / (2 * (k_ * R_e + h_s));
    float psi_g = asin(term_h_a_R_2 * term_2 - term_R_2);

    float ksi_e = psi_d - psi_g;
    //formula 2.19
    float d = (k_ * R_e + h_s) * ksi_e;

    return calculate_answer(psi_d, psi_g, d);
}

void AverageKAnalytical::SetAtmosphere(const ExponentialModel &model){
    atmosphere = model;
}

void AveragePAnalytical::SetAtmosphere(const ExponentialModel &model){
    atmosphere = model;
}

void AverageP::SetAtmosphere(const ExponentialModel &model){
    atmosphere = model;
}


float AverageKAnalytical::k(float h_a, float h_s, float R){
    if (!(h_a >0) or !(h_s >0) or !(R >0)){
        std::cerr<<"incorrect values supplied"<<std::endl;
    }
    //formula 2.9
    float term1 = h_a / R;
    float term2 = 1 + h_a / (2 * R_e);
    float term3 = R / (2 * R_e);
    float psi_g = asin(term1 * term2 - term3);

    //formula 2.38
    double H_b = atmosphere.Hb(); //Hb
    double N_s = atmosphere.N(h_s); //Ns // затычка для h, вопрос по использованию так как в
    double term4 = H_b / (h_a - h_s);
    double term4_5 = ((pow(10, -6) * N_s * cos(psi_g) * R_e) / H_b);
    double term5 = exp((h_a - h_s) / H_b) - term4_5;
    double term6 = (pow(10, -6) * N_s * cos(psi_g) * R_e) / H_b;
    double term7 = 1 - term6;
    double k_avg = term4 * log(term5 / term7);

    return k_avg;
}

float AveragePAnalytical::k(float h_a, float h_s, float R){
    if (!(h_a >0) or !(h_a >0) or !(h_a >0)){
        std::cerr<<"incorrect values supplied"<<std::endl;
    }
    //formula 2.9
    float term1 = h_a / R;
    float term2 = 1 + h_a / (2 * R_e);
    float term3 = R / (2 * R_e);
    float psi_g = asin(term1 * term2 - term3);

    double H_b = atmosphere.Hb(); //Hb
    double N_s = atmosphere.N(h_s); //Ns // затычка для h, вопрос по использованию так как в
    //formula 2.39
    float term4 = H_b / (pow(10, -6) * N_s * cos(psi_g));
    float term5 = exp((h_a - h_s) / H_b) - 1;
    float term6 = (h_a - h_s) / H_b;
    float p_avg = term4 * (term5 / term6);
    //formula 2.40
    float k_avg = 1 / (1 - (R_e/p_avg));
    return k_avg;
}



float FourThirds::reverse(float h_a, float h_s, float R){
    float d_h = h_s * 0.01;
    float h_s_guess = 0.9 * h_s;
    FourThirds model;

    calculate_answer res_0 = model.calculate(h_a, h_s, R);
    float angle_real = res_0.psi_d;

    for (int iter = 0; iter<5000; iter++){
        calculate_answer res_plus = model.calculate(h_a, (h_s_guess + d_h), R);
        calculate_answer res_minus =  model.calculate(h_a, h_s - d_h, R);
        float angle_plus = res_plus.psi_d;
        float angle_minus = res_minus.psi_d;
        float d = res_plus.d;
        float angle = (angle_minus + angle_plus) / 2;
        float error = abs(angle_real - angle);
        float derivattive = (angle_plus + angle_minus) / (2 * d_h);
        h_s_guess = h_s_guess + error / derivattive;
    }

    return h_s_guess;
}

float AveragePAnalytical::reverse(float h_a, float h_s, float R){
    float d_h = h_s * 0.01;
    float h_s_guess = 0.9 * h_s;
    AveragePAnalytical model;

    calculate_answer res_0 = model.calculate(h_a, h_s, R);
    float angle_real = res_0.psi_d;

    for (int iter = 0; iter<5000; iter++){
        calculate_answer res_plus = model.calculate(h_a, (h_s_guess + d_h), R);
        calculate_answer res_minus =  model.calculate(h_a, h_s - d_h, R);
        float angle_plus = res_plus.psi_d;
        float angle_minus = res_minus.psi_d;
        float d = res_plus.d;
        float angle = (angle_minus + angle_plus) / 2;
        float error = abs(angle_real - angle);
        float derivattive = (angle_plus + angle_minus) / (2 * d_h);
        h_s_guess = h_s_guess + error / derivattive;
    }

    return h_s_guess;
}

float AverageKAnalytical::reverse(float h_a, float h_s, float R){
    float d_h = h_s * 0.01;
    float h_s_guess = 0.9 * h_s;
    AveragePAnalytical model;

    calculate_answer res_0 = model.calculate(h_a, h_s, R);
    float angle_real = res_0.psi_d;

    for (int iter = 0; iter<5000; iter++){
        calculate_answer res_plus = model.calculate(h_a, (h_s_guess + d_h), R);
        calculate_answer res_minus =  model.calculate(h_a, h_s - d_h, R);
        float angle_plus = res_plus.psi_d;
        float angle_minus = res_minus.psi_d;
        float d = res_plus.d;
        float angle = (angle_minus + angle_plus) / 2;
        float error = abs(angle_real - angle);
        float derivattive = (angle_plus + angle_minus) / (2 * d_h);
        h_s_guess = h_s_guess + error / derivattive;
    }

    return h_s_guess;
}

float GeometricLine::reverse(float h_a, float h_s, float R){
    float d_h = h_s * 0.01;
    float h_s_guess = 0.9 * h_s;
    GeometricLine model;

    calculate_answer res_0 = model.calculate(h_a, h_s, R);
    float angle_real = res_0.psi_d;

    for (int iter = 0; iter<5000; iter++){
        calculate_answer res_plus = model.calculate(h_a, (h_s_guess + d_h), R);
        calculate_answer res_minus =  model.calculate(h_a, h_s - d_h, R);
        float angle_plus = res_plus.psi_d;
        float angle_minus = res_minus.psi_d;
        float d = res_plus.d;
        float angle = (angle_minus + angle_plus) / 2;
        float error = abs(angle_real - angle);
        float derivattive = (angle_plus + angle_minus) / (2 * d_h);
        h_s_guess = h_s_guess + error / derivattive;
    }

    return h_s_guess;
}

