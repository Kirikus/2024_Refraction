#include <QApplication>

#include "../lib/linear.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(test_linear_interpolation)

const std::vector<double> x_values = {1, 3, 5, 7};
const std::vector<double> y_values = {3, 5, 7, 9};
constexpr int x_min = 1;
constexpr int x_max = 7;
Linear testLinear = Linear(x_values, y_values);

BOOST_AUTO_TEST_CASE(linear_interpolation_at_dots) {
    for (int i = 0; i < x_values.size(); ++i)
        BOOST_TEST(testLinear.y(x_values[i]) == y_values[i], tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(linear_interpolation_between_dots) {
    std::vector<double> weights = {0.1, 0.3, 0.5, 0.6, 0.8};
    for (int i = 1; i < x_values.size(); i++) {
        for (auto w: weights) {
            double x = w * x_values[i-1] + (1-w) * x_values[i];
            double y = w * y_values[i-1] + (1-w) * y_values[i];
            BOOST_TEST(testLinear.y(x) == y, tt::tolerance(1e-6));
        }
    }
}

#ifdef TEST_PLOTS
BOOST_AUTO_TEST_CASE(plot_linear_interpolation) {
    int argc = 1;
    char *argv[] = {"Linear interpolation"};
    QApplication a(argc, argv);

    QCustomPlot customPlot = QCustomPlot();
    customPlot.addGraph();
    customPlot.graph(0)->setPen(QPen(Qt::blue));

    QVector<double> xInterp, yInterp;
    for (double x = x_min; x <= x_max; x += 0.1) {
        xInterp.push_back(x);
        yInterp.push_back(testLinear.y(x));
    }

    // add subgrid
    customPlot.xAxis->grid()->setSubGridVisible(true);
    customPlot.yAxis->grid()->setSubGridVisible(true);
    // add labels
    customPlot.xAxis->setLabel("X");
    customPlot.yAxis->setLabel("Y");
    // pass data points to graphs:
    customPlot.graph(0)->setData(xInterp, yInterp);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible
    // area:
    customPlot.graph(0)->rescaleAxes();
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
    // graphs by clicking:
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);

    customPlot.show();
    customPlot.resize(640, 480);

    a.exec();
}
#endif

BOOST_AUTO_TEST_SUITE_END()
