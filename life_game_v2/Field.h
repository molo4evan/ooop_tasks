//
// Created by User on 014 14.11.17.
//

#ifndef LIFE_GAME_FIELD_H
#define LIFE_GAME_FIELD_H

#include "Cell.h"

class Field {
private:
    Cell** cells;
    unsigned int x;
    unsigned int y;

    void get_neighbours(unsigned int, unsigned int, bool*);
public:
    Field();
    explicit Field(int);
    Field(int, int);
    Field(const Field&);
    ~Field();
    void recalculate();
    void print();
    void set_cell(unsigned int, unsigned int);
    bool get_cell(unsigned int, unsigned int) const;
    void clear();
    void clear_cell(unsigned int, unsigned int);
    unsigned int get_x() const;
    unsigned int get_y() const;
    void resize(unsigned int, unsigned int);
    Field& operator=(const Field&);
    bool operator==(const Field&);
};


#endif //LIFE_GAME_FIELD_H