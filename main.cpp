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

    first = 3;

    koef = new double[first + 1];
    koef[0]=0;
    koef[1]=0;
    koef[2]=4;
    koef[3]=5;
    Polynom<double> intemp(first, koef);
    std::cout <<intemp.print(first, koef);
    //std::cout <<intemp.print2(first, koef);
    //std::cout << intemp;
}
