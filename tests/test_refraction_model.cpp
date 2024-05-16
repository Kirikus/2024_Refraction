//#define BOOST_TEST_MODULE MyTest

#include "RefractionModel.h"
#include "qcustomplot.h"
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_etalon)

BOOST_AUTO_TEST_CASE(calculate)
{
    int argc = 1;
    char *argv[] = {"The dependence of the refractive index on height for a segmented model"};
    QApplication app(argc, argv);

    // Создаем простой виджет
    QWidget window;
    window.resize(800, 600);

    // Создаем QCustomPlot и добавляем его в виджет
    QCustomPlot *customPlot = new QCustomPlot(&window);
    customPlot->setGeometry(0, 0, 800, 600);

    //QCustomPlot customPlot = QCustomPlot();
    float h_a = 400000;
    float h_s_fn = 15000;
    float R = 410000;

    FourThirds el_etalon;
    GeometricLine el_line;
    AverageK el_k;
    AverageP el_p;
    AverageKAnalytical el_Ka;
    AveragePAnalytical el_Pa;
    std::unique_ptr<AtmosphericModel> model0(new ExponentialModel());
    std::unique_ptr<AtmosphericModel> model1(new ExponentialModel());
    std::unique_ptr<AtmosphericModel> model2(new ExponentialModel());
    std::unique_ptr<AtmosphericModel> model3(new ExponentialModel());
    el_k.SetAtmosphere(std::move(model0));
    el_p.SetAtmosphere(std::move(model1));
    el_Ka.SetAtmosphere(std::move(model2));
    el_Pa.SetAtmosphere(std::move(model3));
    QVector<double> x_et(1500), x_l(1500), x_p(1500), x_k(1500), x_Ka(1500), x_Pa(1500), y(1500);
    int n = 0;
    for (int h = 0; h < h_s_fn; h = h + 10){

        calculate_answer res_etalon = el_etalon.calculate(h_a, h, R);
        calculate_answer res_line = el_line.calculate(h_a, h, R);
        calculate_answer res_k = el_k.calculate(h_a, h, R);
        calculate_answer res_p = el_p.calculate(h_a, h, R);
        calculate_answer res_Ka = el_Ka.calculate(h_a, h, R);
        calculate_answer res_Pa = el_Pa.calculate(h_a, h, R);

        y[n] = h/1000;
        x_et[n] = 0;
        x_l[n] = ((res_etalon.psi_d - res_line.psi_d) / res_etalon.psi_d) * 100;
        x_p[n] = ((res_etalon.psi_d - res_p.psi_d) / res_etalon.psi_d) * 100;
        x_k[n] = ((res_etalon.psi_d - res_k.psi_d) / res_etalon.psi_d) * 100;
        x_Ka[n] = ((res_etalon.psi_d - res_Ka.psi_d) / res_etalon.psi_d) * 100;
        x_Pa[n] = ((res_etalon.psi_d - res_Pa.psi_d) / res_etalon.psi_d) * 100;
        std::cout<< x_l[n] << " geom_line" <<std::endl;
        std::cout<< x_p[n] << " averageP" <<std::endl;
        std::cout<< x_k[n] << " averageK" <<std::endl;
        std::cout<< x_Ka[n] << " averagePAnal" <<std::endl;
        std::cout<< x_Pa[n] << " averageKAnal" <<std::endl;
        n = n + 1;
    }

    // Добавляем графики и устанавливаем данные
    customPlot->addGraph();
    customPlot->graph(0)->setData(x_et, y);
    customPlot->graph(0)->setPen(QPen(Qt::black)); // Черный цвет для первого графика
    customPlot->graph(0)->setName("Etalon");

    customPlot->addGraph();
    customPlot->graph(1)->setData(x_l, y);
    customPlot->graph(1)->setPen(QPen(Qt::blue)); // Синий цвет для второго графика
    customPlot->graph(1)->setName("Geometric Line");

    customPlot->addGraph();
    customPlot->graph(2)->setData(x_p, y);
    customPlot->graph(2)->setPen(QPen(Qt::red)); // Красный цвет для третьего графика
    customPlot->graph(2)->setName("Average P");

    customPlot->addGraph();
    customPlot->graph(3)->setData(x_k, y);
    customPlot->graph(3)->setPen(QPen(Qt::green)); // Зеленый цвет для четвертого графика
    customPlot->graph(3)->setName("Average K");

    customPlot->addGraph();
    customPlot->graph(4)->setData(x_Ka, y);
    customPlot->graph(4)->setPen(QPen(Qt::cyan)); // Голубой цвет для пятого графика
    customPlot->graph(4)->setName("Average K Analytical");

    customPlot->addGraph();
    customPlot->graph(5)->setData(x_Pa, y);
    customPlot->graph(5)->setPen(QPen(Qt::magenta)); // Магента цвет для шестого графика
    customPlot->graph(5)->setName("Average P Analytical");

        // Подписываем оси
    customPlot->xAxis->setLabel("Height (h)");
    customPlot->yAxis->setLabel("Percentage Difference");

        // Задаем границы осей (при необходимости можно адаптировать под ваши данные)
    customPlot->xAxis->setRange(0, h_s_fn);
    customPlot->yAxis->setRange(-100, 100); // Пример диапазона, настройте под ваши данные

        // Включаем легенду
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));
    // Включаем перемещение и зум
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // Опционально: настраиваем направления зума и перемещения
    customPlot->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    customPlot->axisRect()->setRangeZoom(Qt::Horizontal | Qt::Vertical);
        // Перерисовываем график
    customPlot->replot();
    customPlot->xAxis->setRange(0, h_s_fn / 100);
    // Показываем окно
        window.show();

    app.exec();
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_geometric_line)

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    GeometricLine line;

    float h_a = 10000;
    float h_s = 1000;
    float R = 12000;

    calculate_answer result = line.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.958, 10);
    BOOST_CHECK_CLOSE(result.psi_g, 0.957, 10);
    BOOST_CHECK_CLOSE(result.d, 6319, 10);
}


BOOST_AUTO_TEST_CASE(ErrorThrow){
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

BOOST_AUTO_TEST_SUITE_END()

// all next tests using the round model
BOOST_AUTO_TEST_SUITE(test_k_four_thirds)

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    FourThirds el;
    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.958, 10);
    BOOST_CHECK_CLOSE(result.psi_g, 0.957, 10);
    BOOST_CHECK_CLOSE(result.d, 6319, 10);
    }

BOOST_AUTO_TEST_CASE(ErrorThrow){

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


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_average_P)

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    AverageP el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));
    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.958, 10);
    BOOST_CHECK_CLOSE(result.psi_g, 0.957, 10);
    BOOST_CHECK_CLOSE(result.d, 6319, 10);
    }


BOOST_AUTO_TEST_CASE(ErrorThrow){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    AverageP el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));

    float h_a = -8;
    float h_s = -3;
    float R = -15;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Test_AveragePAnalitical)

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    AveragePAnalytical el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));
    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.958, 10);
    BOOST_CHECK_CLOSE(result.psi_g, 0.957, 10);
    BOOST_CHECK_CLOSE(result.d, 6319, 10);
    }


BOOST_AUTO_TEST_CASE(ErrorThrow){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    AveragePAnalytical el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));

    float h_a = -8;
    float h_s = -3;
    float R = -15;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Test_AverageKAnalitical)

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    AverageKAnalytical el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));
    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.958, 10);
    BOOST_CHECK_CLOSE(result.psi_g, 0.957, 10);
    BOOST_CHECK_CLOSE(result.d, 6319, 10);
    }

BOOST_AUTO_TEST_CASE(ErrorThrow){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    AverageKAnalytical el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));

    float h_a = -8;
    float h_s = -3;
    float R = -15;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Test_AverageK)

BOOST_AUTO_TEST_CASE(ReturnCorrectAnswer) {

    AverageK el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));
    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;

    calculate_answer result = el.calculate(h_a, h_s, R);

    BOOST_CHECK_CLOSE(result.psi_d, 0.958, 10);
    BOOST_CHECK_CLOSE(result.psi_g, 0.957, 10);
    BOOST_CHECK_CLOSE(result.d, 6319, 10);
    }

BOOST_AUTO_TEST_CASE(ErrorThrow){

    std::ostringstream oss;
    std::streambuf* oldCerrBuffer = std::cerr.rdbuf(oss.rdbuf());

    AverageK el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));

    float h_a = -8;
    float h_s = -3;
    float R = -15;
    calculate_answer result = el.calculate(h_a, h_s, R);
    std::cerr.rdbuf(oldCerrBuffer);
    std::string errorMsg = oss.str();

    BOOST_CHECK(errorMsg.find("incorrect values supplied") != std::string::npos);
    }

BOOST_AUTO_TEST_SUITE_END()

//Reverse calculate from one model to another

BOOST_AUTO_TEST_SUITE(ReverseTask)

BOOST_AUTO_TEST_CASE(GeometricLine_GeometricLine){
    GeometricLine el1;
    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;
    float h_s_near = h_s - h_s*0.5;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el1.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, h_s_near, 1);
}

BOOST_AUTO_TEST_CASE(AverageP_AverageP){
    AverageP el;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el.SetAtmosphere(std::move(model));

    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;

    calculate_answer res = el.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_near = h_s - h_s*0.5;
    float h_s_guess = el.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 1000, 1);
}

BOOST_AUTO_TEST_CASE(AveragePAnalytical_AveragePAnalytical){
    AveragePAnalytical el1;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el1.SetAtmosphere(std::move(model));

    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;
    float h_s_near = h_s - h_s*0.5;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el1.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 1000, 1);
}

BOOST_AUTO_TEST_CASE(AverageKAnalitical_AverageKAnalitical){
    AverageKAnalytical el1;
    std::unique_ptr<AtmosphericModel> model(new ExponentialModel());
    el1.SetAtmosphere(std::move(model));

    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;
    float h_s_near = h_s - h_s*0.5;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el1.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 1000, 1);
}

BOOST_AUTO_TEST_CASE(FourThirds_FourThirds){
    FourThirds el1;

    float h_a = 10000;
    float h_s = 1000;
    float R = 11000;
    float h_s_near = h_s - h_s*0.5;
    calculate_answer res = el1.calculate(h_a, h_s, R);
    float psi_d = res.psi_d;
    float h_s_guess = el1.reverse(h_a, h_s_near, R, psi_d);
    BOOST_CHECK_CLOSE(h_s_guess, 1000, 1);
}

BOOST_AUTO_TEST_SUITE_END()

