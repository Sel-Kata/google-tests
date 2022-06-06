#include "src/lib/polynom.hpp"
#include <iostream>
#include <vector>
#include "gtest/gtest.h"

TEST(Polynomal_Should, Return_Polynimal){
    int first = 4;
    int second = 3;

    double *koef;
    double *koef2;

    koef = new double[first + 1];
    for (int i = 0; i <= first; i++) {
        if (i == 0) {
            koef[i] = 10;
        } else {
            koef[i] = i * 2;
        }
    }
    Polynom<double> intemp(first, koef);
    std::string actual = intemp.print(first, koef);
    std::string expected = "8x^4 + 6x^3 + 4x^2 + 2x^1 + :";
    EXPECT_EQ(expected, actual);
}
TEST(Polynomal2_Should, Return_Polynimal2){
    int first = 3;

    double *koef;
    double *koef2;

    koef = new double[first + 1];
    for (int i = 0; i <= first; i++) {
        if (i == 0) {
            koef[i] = 10;
        } else {
            koef[i] = i * 2;
        }
    }
    Polynom<double> intemp(first, koef);
    std::string actual = intemp.print(first, koef);
    std::string expected = "6x^3 + 4x^2 + 2x^1 + :";
    EXPECT_EQ(expected, actual);
}
TEST(Polynomal3_Should, Return_Polynimal3){
    int first = 3;

    double *koef;
    double *koef2;

     koef = new double[first + 1];
    koef[0]=0;
    koef[1]=0;
    koef[2]=4;
    koef[3]=5;
    Polynom<double> intemp(first, koef);
    std::string actual = intemp.print(first, koef);
    std::string expected = "5x^3 + 4x^2";
    EXPECT_EQ(expected, actual);
}
