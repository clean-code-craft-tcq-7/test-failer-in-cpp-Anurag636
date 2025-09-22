#include "gtest/gtest.h"
#include <stdio.h>

extern "C" {
    int testTshirtSize();
    int testPrintColorMap();
    int testWeatherReport();
}

TEST(TShirt, Size) {
    int result = testTshirtSize();
    EXPECT_TRUE(result) << "T-shirt size test failed";
}

TEST(ColorMap, Print) {
    int result = testPrintColorMap();
    EXPECT_TRUE(result) << "Color map alignment test failed";
}

TEST(WeatherReport, Report) {
    int result = testWeatherReport();
    EXPECT_TRUE(result) << "Weather report test failed";
}