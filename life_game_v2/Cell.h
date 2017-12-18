//
// Created by User on 014 14.11.17.
//

#ifndef LIFE_GAME_CELL_H
#define LIFE_GAME_CELL_H
#include <iostream>

class Cell {
private:
    bool is_alive;
    bool neighbours[8];
public:
    Cell();
    void set_cell(bool);
    bool get_cell();
    void calc_state();
    void print();
    void set_neighbours(bool*);
};


#endif //LIFE_GAME_CELL_H