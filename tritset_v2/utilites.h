//
// Created by User on 015 15.10.17.
//

#ifndef TRITSET_V2_UTILITES_H
#define TRITSET_V2_UTILITES_H

typedef unsigned int uint;

enum Trit_num {Unknown = 0, False = 1, True = 2};

const uint BYTE_SIZE = 8;
const uint TRIT_SIZE = 2;

void assign(uint* arr, uint size);
#endif //TRITSET_V2_UTILITES_H
