//
// Created by User on 001 01.10.17.
//
#include "utilites.h"

void print_trit(Trit t) {
    if (t == Unknown) std::cout << "Unknown(0) ";
    else if (t == False) std::cout << "False(1) ";
    else if (t == True) std::cout << "True(2) ";
}