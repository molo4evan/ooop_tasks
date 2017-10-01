//
// Created by User on 026 26.09.17.
//

#ifndef TRITSET_TRIT_POINTER_H
#define TRITSET_TRIT_POINTER_H
#include <vector>
#include "utilites.h"
using namespace std;
class Tritset;

class Trit_pointer {
private:
    uint full_pos;
    Tritset* set;
    uint set_size;
    void reallocate();
    uint* getAccuratePos(uint*);
public:
    Trit_pointer(uint, Tritset*);
    Trit_pointer(uint, Tritset*, uint);
    Trit operator =(Trit);
};


#endif //TRITSET_TRIT_POINTER_H
