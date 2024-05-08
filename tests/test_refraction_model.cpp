//#define BOOST_TEST_MODULE MyTest

#include "RefractionModel.h"
#include "qcustomplot.h"
#include <boost/test/unit_test.hpp>

/*
void plot_err_line(QCustomPlot &customPlot, QColor color, float R){
    const int n = 1000;
    const double h_a = 1000, h_s = 30000;
    QVector<double> x(n), y(n), y1(n);
    auto graph = customPlot.addGraph();
    graph->setPen(QPen(color));
    FourThirds model_main;
    AverageKAnalytical model;
    ExponentialModel el;
    model.SetAtmosphere(el);

    for (int i = 0; i < n; ++i) {
        calculate_answer res_main = model_main.calculate(h_a, h_s* (i/n), R);
        calculate_answer res = model.calculate(h_a, h_s* (i/n), R);
        y[i] = fabs(res_main.psi_d - res.psi_d);
        x[i] = h_s* (i/n);
        y1[i] = 0;
    }

    graph->setData(x, y);
    graph->setName("err");

}
BOOST_AUTO_TEST_SUITE(plot_test)

BOOST_AUTO_TEST_CASE(err){
    QCustomPlot qcast = QCustomPlot();
    float R = 100000;
    //plot_err_line(qcast, Qt::red, R);
}

BOOST_AUTO_TEST_SUITE_END()

*/
BOOST_AUTO_TEST_SUITE(test_geometric_line)

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    GeometricLine line;

    float h_a = 10.0;
    float h_s = 20.0;
    float R = 63.0;

    calculate_answer result = line.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.159409, 0.01);
    BOOST_CHECK_CLOSE(result.psi_g, 0.1594, 0.01);
    BOOST_CHECK_CLOSE(result.d, 62.1826, 0.01);
}

BOOST_AUTO_TEST_CASE(ErrorByNulls){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    GeometricLine el;

    float h_a = 0;
    float h_s = 0;
    float R = 0;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }

BOOST_AUTO_TEST_CASE(ErrorByNegativeNumbers){
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

BOOST_AUTO_TEST_CASE(ReturnNanOfBigNumbers){
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

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    FourThirds el;
    float h_a = 10.0;
    float h_s = 5.0;
    float R = 20.0;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.252682, 0.01);
    BOOST_CHECK_CLOSE(result.psi_g, 0.252679, 0.01);
    BOOST_CHECK_CLOSE(result.d, 19.3668, 0.01);
    }

BOOST_AUTO_TEST_CASE(ErrorByNulls){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    FourThirds el;

    float h_a = 0;
    float h_s = 0;
    float R = 0;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }

BOOST_AUTO_TEST_CASE(ErrorByNegativeNumbers){

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

BOOST_AUTO_TEST_CASE(ReturnNanOfBigNumbers){

    FourThirds el;
    float h_a = 1e60;
    float h_s = 1e60;
    float R = 1e30;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK(std::isnan(result.psi_d));
    BOOST_CHECK(std::isnan(result.psi_g));
    BOOST_CHECK(std::isnan(result.d));
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_average_P)

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    AverageP el;
    float h_a = 10.0;
    float h_s = 5.0;
    float R = 20.0;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.252678, 0.01);
    BOOST_CHECK_CLOSE(result.psi_g, 0.252682, 0.01);
    BOOST_CHECK_CLOSE(result.d, 19.4901, 0.01);
    }

BOOST_AUTO_TEST_CASE(ErrorByNulls){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    AverageP el;

    float h_a = 0;
    float h_s = 0;
    float R = 0;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }

BOOST_AUTO_TEST_CASE(ErrorByNegativeNumbers){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    AverageP el;

    float h_a = -8;
    float h_s = -3;
    float R = -15;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }

BOOST_AUTO_TEST_CASE(ReturnNanOfBigNumbers){

    AverageP el;
    float h_a = 1e60;
    float h_s = 1e60;
    float R = 1e30;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK(std::isnan(result.psi_d));
    BOOST_CHECK(std::isnan(result.psi_g));
    BOOST_CHECK(std::isnan(result.d));
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Test_AveragePAnalitical)

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    AveragePAnalytical el;
    ExponentialModel model;
    el.SetAtmosphere(model);
    float h_a = 10.0;
    float h_s = 5.0;
    float R = 20.0;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.252681, 0.01);
    BOOST_CHECK_CLOSE(result.psi_g, 0.252679, 0.01);
    BOOST_CHECK_CLOSE(result.d, 19.2979, 0.01);
    }

BOOST_AUTO_TEST_CASE(ErrorByNulls){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    AveragePAnalytical el;
    ExponentialModel model;
    el.SetAtmosphere(model);

    float h_a = 0;
    float h_s = 0;
    float R = 0;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }

BOOST_AUTO_TEST_CASE(ErrorByNegativeNumbers){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    AveragePAnalytical el;
    ExponentialModel model;
    el.SetAtmosphere(model);

    float h_a = -8;
    float h_s = -3;
    float R = -15;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }

BOOST_AUTO_TEST_CASE(ReturnNanOfBigNumbers){

    AveragePAnalytical el;
    ExponentialModel model;
    el.SetAtmosphere(model);

    float h_a = 1e60;
    float h_s = 1e60;
    float R = 1e30;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK(std::isnan(result.psi_d));
    BOOST_CHECK(std::isnan(result.psi_g));
    BOOST_CHECK(std::isnan(result.d));
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Test_AverageKAnalitical)

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    AverageKAnalytical el;
    ExponentialModel model;
    el.SetAtmosphere(model);
    float h_a = 10.0;
    float h_s = 5.0;
    float R = 20.0;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.252681, 0.01);
    BOOST_CHECK_CLOSE(result.psi_g, 0.252679, 0.01);
    BOOST_CHECK_CLOSE(result.d, 19.2979, 0.01);
    }

BOOST_AUTO_TEST_CASE(ErrorByNulls){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    AverageKAnalytical el;
    ExponentialModel model;
    el.SetAtmosphere(model);

    float h_a = 0;
    float h_s = 0;
    float R = 0;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }

BOOST_AUTO_TEST_CASE(ErrorByNegativeNumbers){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    AverageKAnalytical el;
    ExponentialModel model;
    el.SetAtmosphere(model);

    float h_a = -8;
    float h_s = -3;
    float R = -15;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }

BOOST_AUTO_TEST_CASE(ReturnNanOfBigNumbers){

    AverageKAnalytical el;
    ExponentialModel model;
    el.SetAtmosphere(model);

    float h_a = 1e60;
    float h_s = 1e60;
    float R = 1e30;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK(std::isnan(result.psi_d));
    BOOST_CHECK(std::isnan(result.psi_g));
    BOOST_CHECK(std::isnan(result.d));
    }

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(ReverseTask)

BOOST_AUTO_TEST_CASE(GeometricLine_GeometricLine){
    GeometricLine el1;
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = h_s - 50;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el1.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 950, 0.01);
}

BOOST_AUTO_TEST_CASE(AverageP_AverageP){
    AverageP el;
    ExponentialModel model;
    el.SetAtmosphere(model);

    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;

    calculate_answer res = el.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_near = h_s - 50;
    float h_s_guess = el.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 952.754, 0.01);
}

BOOST_AUTO_TEST_CASE(AveragePAnalytical_AveragePAnalytical){
    AveragePAnalytical el1;
    ExponentialModel model;
    el1.SetAtmosphere(model);

    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = h_s - 50;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el1.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 952.748, 0.01);
}

BOOST_AUTO_TEST_CASE(AverageKAnalitical_AverageKAnalitical){
    AverageKAnalytical el1;
    ExponentialModel model;
    el1.SetAtmosphere(model);

    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = h_s - 50;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el1.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 952.748, 0.01);
}

BOOST_AUTO_TEST_CASE(FourThirds_FourThirds){
    FourThirds el1;

    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el1.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 952.748, 0.01);
}

BOOST_AUTO_TEST_CASE(GeometricLine_FourThirds){
    FourThirds el2;
    GeometricLine el1;
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 1006.18, 0.01);
}

BOOST_AUTO_TEST_CASE(GeometricLine_AverageP){
    AverageP el2;
    ExponentialModel model;
    el2.SetAtmosphere(model);
    GeometricLine el1;
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 1007.22, 0.01);
}

BOOST_AUTO_TEST_CASE(GeometricLine_AveragePAnalytical){
    AveragePAnalytical el2;
    ExponentialModel model;
    el2.SetAtmosphere(model);
    GeometricLine el1;
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 1006.35, 0.01);
}

BOOST_AUTO_TEST_CASE(GeometricLine_AverageKAnalytical){
    AverageKAnalytical el2;
    ExponentialModel model;
    el2.SetAtmosphere(model);
    GeometricLine el1;
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 1006.38, 0.01);
}

BOOST_AUTO_TEST_CASE(FourThirds_AverageP){
    AverageP el2;
    ExponentialModel model;
    el2.SetAtmosphere(model);
    FourThirds el1;
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 951.879, 0.01);
}

BOOST_AUTO_TEST_CASE(FourThirds_GeometricLine){
    GeometricLine el2;

    FourThirds el1;
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 1001.39, 0.01);


}

BOOST_AUTO_TEST_CASE(FourThirds_AveragePAnalytical){
    AveragePAnalytical el2;
    ExponentialModel model;
    el2.SetAtmosphere(model);
    FourThirds el1;
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 952.6, 0.01);
}

BOOST_AUTO_TEST_CASE(FourThirds_AverageKAnalytical){
    AverageKAnalytical el2;
    ExponentialModel model;
    el2.SetAtmosphere(model);
    FourThirds el1;
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 952.6, 0.01);
}

BOOST_AUTO_TEST_CASE(AverageP_FourThirds){
    AverageP el1;
    ExponentialModel model;
    el1.SetAtmosphere(model);
    FourThirds el2;
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 953.62, 0.01);
}

BOOST_AUTO_TEST_CASE(AverageP_GeometricLine){
    GeometricLine el2;

    AverageP el1;
    ExponentialModel model;
    el1.SetAtmosphere(model);
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 1002.19, 0.01);


}

BOOST_AUTO_TEST_CASE(AverageP_AveragePAnalytical){
    AveragePAnalytical el2;
    ExponentialModel model;
    el2.SetAtmosphere(model);
    AverageP el1;
    ExponentialModel model1;
    el1.SetAtmosphere(model);
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 953.473, 0.01);
}

BOOST_AUTO_TEST_CASE(AverageP_AverageKAnalytical){
    AverageKAnalytical el2;
    ExponentialModel model;
    el2.SetAtmosphere(model);
    AverageP el1;
    ExponentialModel model1;
    el1.SetAtmosphere(model);
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 953.453, 0.01);
}

BOOST_AUTO_TEST_CASE(AveragePAnalytical_FourThirds){
    AveragePAnalytical el1;
    ExponentialModel model;
    el1.SetAtmosphere(model);
    FourThirds el2;
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 952.895, 0.01);
}

BOOST_AUTO_TEST_CASE(AveragePAnalytical_GeometricLine){
    GeometricLine el2;

    AveragePAnalytical el1;
    ExponentialModel model;
    el1.SetAtmosphere(model);
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 1001.52, 0.01);


}

BOOST_AUTO_TEST_CASE(AveragePAnalytical_AverageP){
    AverageP el2;
    ExponentialModel model;
    el2.SetAtmosphere(model);
    AveragePAnalytical el1;
    ExponentialModel model1;
    el1.SetAtmosphere(model);
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 952.027, 0.01);
}

BOOST_AUTO_TEST_CASE(AveragePAnalytical_AverageKAnalytical){
    AverageKAnalytical el2;
    ExponentialModel model;
    el2.SetAtmosphere(model);
    AveragePAnalytical el1;
    ExponentialModel model1;
    el1.SetAtmosphere(model);
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 952.727, 0.01);
}

BOOST_AUTO_TEST_CASE(AverageKAnalytical_FourThirds){
    AverageKAnalytical el1;
    ExponentialModel model;
    el1.SetAtmosphere(model);
    FourThirds el2;
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 952.915, 0.01);
}

BOOST_AUTO_TEST_CASE(AverageKAnalytical_GeometricLine){
    GeometricLine el2;

    AverageKAnalytical el1;
    ExponentialModel model;
    el1.SetAtmosphere(model);
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 1001.54, 0.01);


}

BOOST_AUTO_TEST_CASE(AverageKAnalytical_AverageP){
    AverageP el2;
    ExponentialModel model;
    el2.SetAtmosphere(model);
    AverageKAnalytical el1;
    ExponentialModel model1;
    el1.SetAtmosphere(model);
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 952.047, 0.01);
}

BOOST_AUTO_TEST_CASE(AverageKAnalytical_AveragePAnalytical){
    AverageKAnalytical el1;
    ExponentialModel model;
    el1.SetAtmosphere(model);
    AveragePAnalytical el2;
    ExponentialModel model1;
    el2.SetAtmosphere(model);
    float h_a = 10000.0;
    float h_s = 1000.0;
    float R = 20000.0;
    float h_s_near = 950;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el2.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 952.768, 0.01);
}

BOOST_AUTO_TEST_SUITE_END()
