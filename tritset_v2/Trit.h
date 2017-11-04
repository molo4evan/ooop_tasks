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
    Trit(const Trit&);
    operator Trit_num()const;
    operator unsigned int()const;
    Trit& operator=(Trit_num);
    Trit& operator=(const Trit&);
    bool operator==(Trit_num)const;
    bool operator==(const Trit&)const;
    bool operator!=(Trit_num)const;
    bool operator!=(const Trit&)const;
    Trit_num operator&(Trit_num)const;
    Trit_num operator&(const Trit&)const;
    Trit_num operator|(Trit_num)const;
    Trit_num operator|(const Trit&)const;
    Trit_num operator~()const;

};


#endif //TRITSET_V2_TRIT_H
