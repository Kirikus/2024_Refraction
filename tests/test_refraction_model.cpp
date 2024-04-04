//#define BOOST_TEST_MODULE MyTest

#include "RefractionModel.cpp"

#include <boost/test/unit_test.hpp>

// тест для плоской земли
BOOST_AUTO_TEST_SUITE(test_segmented)
BOOST_AUTO_TEST_CASE(test_calculate_line) {
    //first testing
    {GeometricLine line;

    float h_a = 10.0;
    float h_s = 20.0;
    float R = 63.0;

    calculate_answer result = line.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.159409, 0.0001);
    BOOST_CHECK_CLOSE(result.psi_g, 0.1594, 0.0001);
    BOOST_CHECK_CLOSE(result.d, 62.1826, 0.0001);
    }
    // second testing
    {GeometricLine line;

    float h_a = 0;
    float h_s = 0;
    float R = 0;

    calculate_answer result = line.calculate(h_a, h_s, R);

    BOOST_TEST(std::isnan(result.psi_d));
    BOOST_TEST(std::isnan(result.psi_g));
    BOOST_TEST(std::isnan(result.d));
    }
    //third testing
    {GeometricLine line;

    float h_a = -8;
    float h_s = -3;
    float R = -15;

    calculate_answer result = line.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.562535, 0.0001);
    BOOST_CHECK_CLOSE(result.psi_g, 0.562537, 0.0001);
    BOOST_CHECK_CLOSE(result.d, -12.9112, 0.0001);
    }
    //forth testing
    {GeometricLine line;

    float h_a = 1e6;
    float h_s = 1e-6;
    float R = -1e3;

    calculate_answer result = line.calculate(h_a, h_s, R);

    BOOST_TEST(std::isnan(result.psi_d));
    BOOST_TEST(std::isnan(result.psi_g));
    BOOST_TEST(std::isnan(result.d));
    }
}

// тест с учетом коэф. преломления = 4/3 вызовом FourThird
BOOST_AUTO_TEST_CASE(test_calculate_Round) {
    //first testing
    {
    RefractionModel* modelPtr;
    GeometricRound* roundPtr;
    EffectiveRadius* el;
    FourThirds el_;
    el = &el_;

    float h_a = 10.0;
    float h_s = 5.0;
    float R = 20.0;

    calculate_answer result = el -> calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.5236, 0.0001);
    BOOST_CHECK_CLOSE(result.psi_g, 0.523597, 0.0001);
    BOOST_CHECK_CLOSE(result.d, 17.4681, 0.0001);
    }
    //second testing
    {
    RefractionModel* modelPtr;
    GeometricRound* roundPtr;
    EffectiveRadius* el;
    FourThirds el_;
    el = &el_;

    float h_a = 0;
    float h_s = 0;
    float R = 0;

    calculate_answer result = el -> calculate(h_a, h_s, R);

    BOOST_TEST(std::isnan(result.psi_d));
    BOOST_TEST(std::isnan(result.psi_g));
    BOOST_TEST(std::isnan(result.d));
    }
    //third testing
    {
    RefractionModel* modelPtr;
    GeometricRound* roundPtr;
    EffectiveRadius* el;
    FourThirds el_;
    el = &el_;

    float h_a = -8;
    float h_s = -3;
    float R = -15;

    calculate_answer result = el -> calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.562535, 0.0001);
    BOOST_CHECK_CLOSE(result.psi_g, 0.562537, 0.0001);
    BOOST_CHECK_CLOSE(result.d, -12.9112, 0.0001);
    }
    //forth testing
    {
    RefractionModel* modelPtr;
    GeometricRound* roundPtr;
    EffectiveRadius* el;
    FourThirds el_;
    el = &el_;

    float h_a = 1e6;
    float h_s = 1e-6;
    float R = -1e3;

    calculate_answer result = el -> calculate(h_a, h_s, R);

    BOOST_TEST(std::isnan(result.psi_d));
    BOOST_TEST(std::isnan(result.psi_g));
    BOOST_TEST(std::isnan(result.d));
    }
}
BOOST_AUTO_TEST_SUITE_END();
