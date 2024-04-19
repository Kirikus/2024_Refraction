#include <QApplication>

#include "../lib/gost_model.cpp"
#include "../lib/cubicspline.h"
#include "../lib/linear.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(test_GOST_model)

const std::vector<double> h_values = {0, 1000, 3000, 6000, 9000, 12000};
const double h_min = 0, h_max = 12000;
const std::vector<double> P_values = {1, 15, 20, 11, 30, 45};
const std::vector<double> T_values = {1, 288, 150, 250, 300, 280};

CubicSpline* testCubicSpline_P = new CubicSpline(h_values, P_values);
Linear* testLinear_T = new Linear(h_values, T_values);
GOSTModel testGOSTModel = GOSTModel(testCubicSpline_P, testLinear_T);

BOOST_AUTO_TEST_CASE(N_at_2000m_continuous) {
    BOOST_TEST(testGOSTModel.N(2000 - 1e-6) == testGOSTModel.N(2000 + 1e-6), tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(N_at_8000m_continuous) {
    BOOST_TEST(testGOSTModel.N(8000 - 1e-6) == testGOSTModel.N(8000 + 1e-6), tt::tolerance(1e-6));
}

#ifdef TEST_PLOTS
BOOST_AUTO_TEST_CASE(plot_dummy) {
  // Plot 2.31 from booklet
  int argc = 1;
  char *argv[] = {"The dependence of the water vapor density on height for GOST Model"};
  QApplication a(argc, argv);

  QCustomPlot customPlot = QCustomPlot();
  customPlot.addGraph();
  customPlot.graph(0)->setPen(QPen(Qt::blue));
  const int N = 1000;
  QVector<double> x(N), y(N);
  for (int i = 0; i < N; ++i) {
    y[i] = h_min + i * (h_max - h_min) / (N - 1);
    x[i] = testGOSTModel.rho_w(y[i]);
  }
  // make x axis logarithmic
  customPlot.xAxis->setScaleType(QCPAxis::stLogarithmic);
  QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
  customPlot.xAxis->setTicker(logTicker);
  // add subgrid
  customPlot.xAxis->grid()->setSubGridVisible(true);
  customPlot.yAxis->grid()->setSubGridVisible(true);
  // add labels
  customPlot.xAxis->setLabel("Water vapor density, g/m³");
  customPlot.yAxis->setLabel("Height, m");
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
