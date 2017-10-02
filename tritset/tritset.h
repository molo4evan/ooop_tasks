//
// Created by User on 026 26.09.17.
//

#ifndef TRITSET_TRITSET_H
#define TRITSET_TRITSET_H

#include <vector>
#include "utilites.h"
class Trit_pointer;

typedef unsigned int uint;
using namespace std;

class Tritset {
private:
    uint* set;
    uint set_size;
    uint start_size;
    uint last_set_trit;
public:
    Tritset();
    explicit Tritset(uint);
    ~Tritset();
    uint capacity();
    uint* getSet();
    void setSet(uint*);

    void setCapacity(uint);
    void setLastTrit(uint);
    uint getLastTrit();
    Trit_pointer& operator [](uint);
    Trit getTrit(uint);
    void printSet();
    uint getAccuratePos(uint);
    void shrink();
};

#endif //TRITSET_TRITSET_H
