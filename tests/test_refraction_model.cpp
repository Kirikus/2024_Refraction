//#define BOOST_TEST_MODULE MyTest

#include "RefractionModel.h"

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_geometric_line)

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    GeometricLine line;

    float h_a = 10000;
    float h_s = 1000;
    float R = 12000;

    calculate_answer result = line.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.958, 10);
    BOOST_CHECK_CLOSE(result.psi_g, 0.957, 10);
    BOOST_CHECK_CLOSE(result.d, 6319, 10);
}


BOOST_AUTO_TEST_CASE(ErrorThrow){
    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    GeometricLine el;

    float h_a = -8;
    float h_s = -3;
    float R = -15;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);

    }

BOOST_AUTO_TEST_SUITE_END()

// all next tests using the round model
BOOST_AUTO_TEST_SUITE(test_k_four_thirds)

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    FourThirds el;
    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.958, 10);
    BOOST_CHECK_CLOSE(result.psi_g, 0.957, 10);
    BOOST_CHECK_CLOSE(result.d, 6319, 10);
    }

BOOST_AUTO_TEST_CASE(ErrorThrow){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    FourThirds el;

    float h_a = -8;
    float h_s = -3;
    float R = -15;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_average_P)

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    AverageP el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));
    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.958, 10);
    BOOST_CHECK_CLOSE(result.psi_g, 0.957, 10);
    BOOST_CHECK_CLOSE(result.d, 6319, 10);
    }


BOOST_AUTO_TEST_CASE(ErrorThrow){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    AverageP el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));

    float h_a = -8;
    float h_s = -3;
    float R = -15;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Test_AveragePAnalitical)

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    AveragePAnalytical el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));
    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.958, 10);
    BOOST_CHECK_CLOSE(result.psi_g, 0.957, 10);
    BOOST_CHECK_CLOSE(result.d, 6319, 10);
    }


BOOST_AUTO_TEST_CASE(ErrorThrow){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    AveragePAnalytical el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));

    float h_a = -8;
    float h_s = -3;
    float R = -15;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Test_AverageKAnalitical)

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    AverageKAnalytical el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));
    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.958, 10);
    BOOST_CHECK_CLOSE(result.psi_g, 0.957, 10);
    BOOST_CHECK_CLOSE(result.d, 6319, 10);
    }

BOOST_AUTO_TEST_CASE(ErrorThrow){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    AverageKAnalytical el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));

    float h_a = -8;
    float h_s = -3;
    float R = -15;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Test_AverageK)

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    AverageK el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));
    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.958, 10);
    BOOST_CHECK_CLOSE(result.psi_g, 0.957, 10);
    BOOST_CHECK_CLOSE(result.d, 6319, 10);
    }

BOOST_AUTO_TEST_CASE(ErrorThrow){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    AverageK el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));

    float h_a = -8;
    float h_s = -3;
    float R = -15;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }

BOOST_AUTO_TEST_SUITE_END()

//Reverse calculate from one model to another

BOOST_AUTO_TEST_SUITE(ReverseTask)

BOOST_AUTO_TEST_CASE(GeometricLine_GeometricLine){
    GeometricLine el1;
    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;
    float h_s_near = h_s - h_s*0.5;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el1.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, h_s_near, 1);
}

BOOST_AUTO_TEST_CASE(AverageP_AverageP){
    AverageP el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));

    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;

    calculate_answer res = el.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_near = h_s - h_s*0.5;
    float h_s_guess = el.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 1000, 1);
}

BOOST_AUTO_TEST_CASE(AveragePAnalytical_AveragePAnalytical){
    AveragePAnalytical el1;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el1.SetAtmosphere(std::move(model));

    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;
    float h_s_near = h_s - h_s*0.5;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el1.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 1000, 1);
}

BOOST_AUTO_TEST_CASE(AverageKAnalitical_AverageKAnalitical){
    AverageKAnalytical el1;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el1.SetAtmosphere(std::move(model));

    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;
    float h_s_near = h_s - h_s*0.5;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el1.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 1000, 1);
}

BOOST_AUTO_TEST_CASE(FourThirds_FourThirds){
    FourThirds el1;

    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;
    float h_s_near = h_s - h_s*0.5;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el1.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 1000, 1);
}

BOOST_AUTO_TEST_SUITE_END()

