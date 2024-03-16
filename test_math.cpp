#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>

#include "RefractionModel.cpp"

// Функция для проверки приближенного равенства двух чисел с плавающей точкой
bool floatEqual(float a, float b, float epsilon = 0.0001) {
    return std::abs(a - b) < epsilon;
}

BOOST_AUTO_TEST_CASE(test_calculate_line) { // тест для плоской земли
    // Создаем объект вашего класса
    GeometricLine line;

    // Параметры для расчета
    float h_a = 10.0;
    float h_s = 20.0;
    float R = 63.0;

    // Выполняем расчет
    std::vector<float> result = line.calculate(h_a, h_s, R);

    // Проверяем результаты
    BOOST_TEST(floatEqual(result[0], 0.159409));
    BOOST_TEST(floatEqual(result[1], 0.1594));
    BOOST_TEST(floatEqual(result[2], 62.1826));
}

BOOST_AUTO_TEST_CASE(test_calculate_Round) { // тест с учетом коэф. преломления = 4/3 вызовом FourThird
    RefractionModel* modelPtr;
    GeometricRound* roundPtr;
    EffectiveRadius* el;
    FourThirds el_;
    el = &el_;


    // Параметры для расчета
    float h_a = 10.0;
    float h_s = 5.0;
    float R = 20.0;

    std::vector<float> result = el -> calculate(h_a, h_s, R);

    // Проверяем результаты
    BOOST_TEST(floatEqual(result[0], 0.5236));
    BOOST_TEST(floatEqual(result[1], 0.523597));
    BOOST_TEST(floatEqual(result[2], 17.4681));
}

