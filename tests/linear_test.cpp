#include <QApplication>

#include "../lib/linear.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(test_linear_interpolation)

std::vector<Point> test_data {Point(1, 3), Point(3, 5), Point(5, 7), Point(7, 9)};

BOOST_AUTO_TEST_CASE(linear_interpolation_at_dots) {
    Linear testLinear = Linear(test_data);
    for (int i = 0; i < test_data.size(); ++i)
        BOOST_TEST(testLinear.y(test_data[i].x) == test_data[i].y, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(linear_interpolation_between_dots) {
    std::vector<Point> test_data {Point(0, 1), Point(2, 3)};
    Linear testLinear = Linear(test_data);
    BOOST_TEST(testLinear.y(1) == 2, tt::tolerance(1e-6));
}

#ifdef TEST_PLOTS
BOOST_AUTO_TEST_CASE(plot_linear_interpolation) {
    int argc = 1;
    char *argv[] = {"Linear interpolation"};
    QApplication a(argc, argv);

    QCustomPlot customPlot = QCustomPlot();
    customPlot.addGraph();
    customPlot.graph(0)->setPen(QPen(Qt::blue));

    Linear testLinear = Linear(test_data);
    int min = 1;
    int max = 9;
    QVector<double> x(max), y(max);
    for (int i = min; i < max; ++i) {
      y[i] = testLinear.y(test_data[i].x);
      x[i] = test_data[i].x;
    }

    // make x axis logarithmic
    customPlot.xAxis->setScaleType(QCPAxis::stLogarithmic);
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    customPlot.xAxis->setTicker(logTicker);
    // add subgrid
    customPlot.xAxis->grid()->setSubGridVisible(true);
    customPlot.yAxis->grid()->setSubGridVisible(true);
    // add labels
    customPlot.xAxis->setLabel("X");
    customPlot.yAxis->setLabel("Y");
    // pass data points to graphs:
    customPlot.graph(0)->setData(x, y);
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
