//
// Created by User on 026 26.09.17.
//

#ifndef TRITSET_UTILITES_H
#define TRITSET_UTILITES_H

#include <iostream>

enum Trit { Unknown = 0, False = 1, True = 2};
typedef unsigned int uint;
const uint TRIT_SIZE = 2;
const uint BYTE_SIZE = 8;

void print_trit(Trit);
void assign(uint*, uint);
uint* resize(uint*, uint, uint);
#endif //TRITSET_UTILITES_H
