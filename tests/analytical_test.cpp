#include <QApplication>

#include "../lib/analytical.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(test_angles_exponential_model_atmosphere)

#ifdef TEST_PLOTS
BOOST_AUTO_TEST_CASE(plot_2_34) {
    // Plot 2.34 from booklet
    int argc = 1;
    char *argv[] = {"Differences in the angles of declination and sliding calculated for different atmospheric parameters of Exponential Model"};
    QApplication a(argc, argv);

    QCustomPlot customPlot;

    QVector<double> angles = {M_PI / 6, M_PI / 18, M_PI / 60, M_PI / 180, 0.3 * M_PI / 180, 0.1 * M_PI / 180};
    QVector<QColor> colors = {Qt::blue, Qt::red, Qt::green, Qt::gray, Qt::cyan, Qt::black};
    double hs = 0;
    QVector<double> Ns_values = {250, 313, 400};
    QVector<Qt::PenStyle> lines = {Qt::SolidLine, Qt::DashLine, Qt::DotLine};


    for (int k = 0; k < Ns_values.size(); ++k){
        ExponentialModel exp_model(Ns_values[k], hs);
        Analytical testAnalytical(exp_model);

        const int N = 100;
        const double h_min = 0, h_max = 30000;
        QVector<double> x(N), y(N);

        for (int j = 0; j < angles.size(); ++j) {
            customPlot.addGraph();
            for (int i = 0; i < N; ++i) {
                customPlot.graph(j + k * 6)->setPen(QPen(colors[j], 2,  lines[k]));
                y[i] = h_min + i * (h_max - h_min) / (N - 1);
                x[i] = abs(testAnalytical.psi_d(angles[j], y[i], hs) - angles[j]) * 180 / M_PI;
            }
            customPlot.graph(j + k * 6)->setData(x, y);
            customPlot.graph(j + k * 6)->setName("psi_g  = " + QString::number(angles[j] * 180 / M_PI) + " at "+ QString::number(Ns_values[k]));
        }
    }

    customPlot.xAxis->grid()->setSubGridVisible(true);
    customPlot.yAxis->grid()->setSubGridVisible(true);

    customPlot.yAxis->setLabel("Height, m");
    customPlot.xAxis->setLabel("|psi_d - psi_g|, degrees");

    customPlot.graph(angles.size() - 1)->rescaleAxes();

    customPlot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                               QCP::iSelectPlottables);

    customPlot.legend->setVisible(true);
    customPlot.show();
    customPlot.resize(640, 480);

    a.exec();
}
#endif

BOOST_AUTO_TEST_SUITE_END()
