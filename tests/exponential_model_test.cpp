#include <QApplication>

#include "../lib/exponential_model.h"
#include "qcustomplot.h"

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;
ExponentialModel testExponentialModel;

BOOST_AUTO_TEST_SUITE(test_N_exponential)

BOOST_AUTO_TEST_CASE(N_ground_level) {
    BOOST_TEST(testExponentialModel.N(0) == 324.8, tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(N_3000m) {
    BOOST_TEST(testExponentialModel.N(3000 - 1e-6) == testExponentialModel.N(3000 + 1e-6), tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(N_10000m) {
    BOOST_TEST(testExponentialModel.N(10000 - 1e-6) == testExponentialModel.N(10000 + 1e-6), tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_SUITE_END()
