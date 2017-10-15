//
// Created by User on 015 15.10.17.
//

#ifndef TRITSET_V2_TRIT_H
#define TRITSET_V2_TRIT_H

#include "utilites.h"

class Trit {
private:
    Trit_num trit;
public:
    Trit();
    Trit(Trit_num);
    Trit_num getTrit();
    bool operator==(Trit_num);
    bool operator!=(Trit_num);
};


#endif //TRITSET_V2_TRIT_H
