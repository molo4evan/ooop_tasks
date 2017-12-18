//
// Created by User on 014 14.11.17.
//

#include "Cell.h"
Cell::Cell() {
    for (int i = 0; i < 8; ++i) {
        neighbours[i] = false;
    }
}

void Cell::set_cell(const bool state) {
    is_alive = state;
}

bool Cell::get_cell() {
    return is_alive;
}

void Cell::set_neighbours(bool *neig) {
    for (int i = 0; i < 8; ++i) {
        neighbours[i] = neig[i];
    }
}

void Cell::calc_state() {
    int alive_neighbours = 0;
    for (int i = 0; i < 8; ++i) {
        if (neighbours[i]) alive_neighbours++;
    }
    if (is_alive) {
        if (alive_neighbours < 2 || alive_neighbours > 3) is_alive = false;
    }
    else if (!is_alive) {
        if (alive_neighbours == 3) is_alive = true;
    }
}

void Cell::print() {
    if (is_alive) std::cout << '0';
    else std::cout << '.';
}