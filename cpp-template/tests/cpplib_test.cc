#include "/Users/selihovkinaekaterina/cpp-template/src/lib/polynom.hpp"
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
        //std::cout<<"Koef["<<i*2;
        if (i == 0) {
            koef[i] = 10;
        } else {
            koef[i] = i * 2;
        }
    }
    Polynom<double> intemp(first, koef);
    std::string actual = intemp.print(coef);
    std::string expected = "8x^4 + 6x^3 + 4x^2 + 2x^1";
    EXPECT_EQ(expected, actual);
}
