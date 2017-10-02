//
// Created by User on 001 01.10.17.
//
#include "utilites.h"

void print_trit(Trit t) {
    if (t == Unknown) std::cout << "Unknown(0) ";
    else if (t == False) std::cout << "False(1) ";
    else if (t == True) std::cout << "True(2) ";
}

void assign(uint* array, uint array_size){
    for (uint i = 0; i < array_size; i++) {
        array[i] = 0;
    }
}

uint* resize(uint* arr, uint old_size, uint new_size){
    uint* new_arr = new uint[new_size];
    assign(new_arr, new_size);

    uint copy_size = old_size < new_size ? old_size : new_size;
    for (int i = 0; i < copy_size; ++i) {
        new_arr[i] = arr[i];
    }
    delete[] arr;
    return new_arr;
}