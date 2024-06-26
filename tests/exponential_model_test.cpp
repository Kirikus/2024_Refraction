#include <QApplication>

#include "../lib/exponential_model.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(test_N_exponential)

BOOST_AUTO_TEST_CASE(N_at_ground_level_Ns_324_8_equals_to_324_8) {
    ExponentialModel testExponentialModelGroundLevel(324.8, 0);
    BOOST_TEST(testExponentialModelGroundLevel.N(0) == 324.8, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(N_at_ground_level_hs_12192_division_by_0_inf) {
    ExponentialModel testExponentialModelGroundLevel(324.8, 12192);
    BOOST_TEST(std::isinf(testExponentialModelGroundLevel.N(0)));
}

BOOST_AUTO_TEST_CASE(N_at_ground_level_Ns_66_65_equals_to_66_65) {
    ExponentialModel testExponentialModelGroundLevel(66.65, 0);
    BOOST_TEST(testExponentialModelGroundLevel.N(0) == 66.65, tt::tolerance(1e-6));
}

ExponentialModel testExponentialModel;

void plot_Ns_line(QCustomPlot &customPlot, double Ns, QColor color){
    const int n = 1000;
    const double h_min = 0, h_max = 15000;
    QVector<double> x(n), y(n);

    auto graph = customPlot.addGraph();
    graph->setPen(QPen(color));
    testExponentialModel = ExponentialModel(Ns, 0);
    for (int i = 0; i < n; ++i) {
        y[i] = h_min + i * (h_max - h_min) / (n - 1);
        x[i] = testExponentialModel.N(y[i]);
    }
    graph->setData(x, y);
    graph->setName("Ns = " + QString::number(Ns));
}

#ifdef TEST_PLOTS
BOOST_AUTO_TEST_CASE(plot_2_32) {
    // Plot 2.32 from booklet
    int argc = 1;
    char *argv[] = {"The dependence of the refractive index on height for an Exponential model"};
    QApplication a(argc, argv);

    QCustomPlot customPlot = QCustomPlot();

    plot_Ns_line(customPlot, 250, Qt::blue);
    plot_Ns_line(customPlot, 313, Qt::green);
    plot_Ns_line(customPlot, 400, Qt::red);

    // add subgrid
    customPlot.xAxis->grid()->setSubGridVisible(true);
    customPlot.yAxis->grid()->setSubGridVisible(true);
    // add labels
    customPlot.xAxis->setLabel("Refractive index N, []");
    customPlot.yAxis->setLabel("Height, [m]");

    // let the ranges scale themselves so graph 2 fits perfectly in the visible
    // area:
    customPlot.graph(2)->rescaleAxes();
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select
    // graphs by clicking:
    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    customPlot.legend->setVisible(true);
    customPlot.show();
    customPlot.resize(640, 480);

    a.exec();
}
#endif

BOOST_AUTO_TEST_SUITE_END()
