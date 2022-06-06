#include <iostream>
#include <cmath>
#include <vector>
#include <memory.h>
#include "polynom.hpp"


int main() {

    int first = 0;
    int second = 0;

    double *koef;
    double *koef2;

    first = 4;
    second = 3;

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
    std::cout << intemp;
}