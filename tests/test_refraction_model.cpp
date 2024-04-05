#define BOOST_TEST_MODULE MyTest

#include "RefractionModel.cpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_geometric_line)

BOOST_AUTO_TEST_CASE(return_correct_answer) {

    GeometricLine line;

    float h_a = 10.0;
    float h_s = 20.0;
    float R = 63.0;

    calculate_answer result = line.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.159409, 0.0001);
    BOOST_CHECK_CLOSE(result.psi_g, 0.1594, 0.0001);
    BOOST_CHECK_CLOSE(result.d, 62.1826, 0.0001);
}

BOOST_AUTO_TEST_CASE(throw_error_of_test_nulls){

    GeometricLine line;

    float h_a = 0;
    float h_s = 0;
    float R = 0;

    BOOST_CHECK_THROW(line.calculate(h_a, h_s, R), std::runtime_error);
    }

BOOST_AUTO_TEST_CASE(throw_error_of_negative_numbers){
    GeometricLine line;

    float h_a = -8;
    float h_s = -3;
    float R = -15;

    BOOST_CHECK_THROW(line.calculate(h_a, h_s, R), std::runtime_error);

    }

BOOST_AUTO_TEST_CASE(return_nan_of_big_numbers){
    GeometricLine line;

    float h_a = 1e6;
    float h_s = 1e-6;
    float R = 1e3;

    calculate_answer result = line.calculate(h_a, h_s, R);

    BOOST_TEST(std::isnan(result.psi_d));
    BOOST_TEST(std::isnan(result.psi_g));
    BOOST_TEST(std::isnan(result.d));
}

BOOST_AUTO_TEST_SUITE_END()

// all next tests using the round model
BOOST_AUTO_TEST_SUITE(test_k_four_thirds)

BOOST_AUTO_TEST_CASE(return_correct_answer) {

    FourThirds el;
    float h_a = 10.0;
    float h_s = 5.0;
    float R = 20.0;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.5236, 0.0001);
    BOOST_CHECK_CLOSE(result.psi_g, 0.523597, 0.0001);
    BOOST_CHECK_CLOSE(result.d, 17.4681, 0.0001);
    }

BOOST_AUTO_TEST_CASE(throw_error_from_nulls){

    FourThirds el;

    float h_a = 0;
    float h_s = 0;
    float R = 0;

    BOOST_CHECK_THROW(el.calculate(h_a, h_s, R), std::runtime_error);
    }

BOOST_AUTO_TEST_CASE(throw_error_of_negative_numbers){

    FourThirds el;

    float h_a = -8;
    float h_s = -3;
    float R = -15;

    BOOST_CHECK_THROW(el.calculate(h_a, h_s, R), std::runtime_error);
    }

BOOST_AUTO_TEST_CASE(return_nan_of_big_numbers){

    FourThirds el;
    float h_a = 1e6;
    float h_s = 1e6;
    float R = 1e3;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_TEST(std::isnan(result.psi_d));
    BOOST_TEST(std::isnan(result.psi_g));
    BOOST_TEST(std::isnan(result.d));
    }

BOOST_AUTO_TEST_SUITE_END()
