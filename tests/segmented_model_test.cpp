#include <QApplication>

#include "../lib/segmented_model.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

SegmentedModel testSegmentedModel;

BOOST_AUTO_TEST_SUITE(test_N)

BOOST_AUTO_TEST_CASE(N_ground_level) {
    BOOST_TEST(testSegmentedModel.N(0) == testSegmentedModel.Ns, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(N_2000m) {
    BOOST_TEST(testSegmentedModel.N(2000 - 1e-6) == testSegmentedModel.N(2000 + 1e-6), tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(N_10000m) {
    BOOST_TEST(testSegmentedModel.N(10000 - 1e-6) == testSegmentedModel.N(10000 + 1e-6), tt::tolerance(1e-6));
}

#ifdef TEST_PLOTS
BOOST_AUTO_TEST_CASE(plot_2_32) {
    // Plot 2.32 from booklet
    int argc = 1;
    char *argv[] = {"The dependence of the refractive index on height for a segmented model"};
    QApplication a(argc, argv);

    QCustomPlot customPlot = QCustomPlot();

    customPlot.addGraph();
    customPlot.graph(0)->setPen(QPen(Qt::blue));
    testSegmentedModel = SegmentedModel(250, 0);
    const int n = 1000;
    const double h_min = 0, h_max = 15000;
    QVector<double> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        y[i] = h_min + i * (h_max - h_min) / (n - 1);
        x[i] = testSegmentedModel.N(y[i]);
    }
    // pass data points to graphs:
    customPlot.graph(0)->setData(x, y);
    customPlot.graph(0)->setName("Ns = 250");

    customPlot.addGraph();
    customPlot.graph(1)->setPen(QPen(Qt::green));
    testSegmentedModel = SegmentedModel(313, 0);
    for (int i = 0; i < n; ++i) {
        y[i] = h_min + i * (h_max - h_min) / (n - 1);
        x[i] = testSegmentedModel.N(y[i]);
    }
    // pass data points to graphs:
    customPlot.graph(1)->setData(x, y);
    customPlot.graph(1)->setName("Ns = 313");

    customPlot.addGraph();
    customPlot.graph(2)->setPen(QPen(Qt::red));
    testSegmentedModel = SegmentedModel(400, 0);
    for (int i = 0; i < n; ++i) {
        y[i] = h_min + i * (h_max - h_min) / (n - 1);
        x[i] = testSegmentedModel.N(y[i]);
    }
    // pass data points to graphs:
    customPlot.graph(2)->setData(x, y);
    customPlot.graph(2)->setName("Ns = 400");

    // add subgrid
    customPlot.xAxis->grid()->setSubGridVisible(true);
    customPlot.yAxis->grid()->setSubGridVisible(true);
    // add labels
    customPlot.xAxis->setLabel("Refractive index N, []");
    customPlot.yAxis->setLabel("Height, [m]");

    // let the ranges scale themselves so graph 0 fits perfectly in the visible
    // area:
    customPlot.graph(0)->rescaleAxes();
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
    // graphs by clicking:
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);

    customPlot.legend->setVisible(true);
    customPlot.show();
    customPlot.resize(640, 480);

    a.exec();
}
#endif

BOOST_AUTO_TEST_SUITE_END()
