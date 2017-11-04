//
// Created by User on 015 15.10.17.
//

#include "Trit.h"

Trit::Trit() {
    trit = Trit_num::Unknown;
};

Trit::Trit(const Trit_num trit) {
    this->trit = trit;
}

Trit::Trit(const Trit& t) {
    this->trit = t.trit;
}

Trit::operator Trit_num()const {
    return trit;
}

Trit::operator unsigned int()const {
    return static_cast<uint>(trit);
}

Trit& Trit::operator=(const Trit_num t){
    trit = t;
}

Trit& Trit::operator=(const Trit& t){
    this->trit = t.trit;
}

bool Trit::operator==(const Trit_num t)const {
    return trit == t;
}

bool Trit::operator==(const Trit &t) const {
    return this->trit == t.trit;
}

bool Trit::operator!=(const Trit_num t)const {
    return trit != t;
}

bool Trit::operator!=(const Trit &t) const {
    return this->trit != t.trit;
}

Trit_num Trit::operator&(const Trit_num t)const {
    if (trit == False || t == False) return False;
    else if (trit == True && t == True) return True;
    else return Unknown;
}

Trit_num Trit::operator&(const Trit& t)const{
    Trit_num trit1 = this->trit, trit2 = t.trit;

    if (trit1 == False || trit2 == False) return False;
    else if (trit1 == True && trit2 == True) return True;
    else return Unknown;
}

Trit_num Trit::operator|(const Trit_num t)const{
    if (trit == False && t == False) return False;
    else if (trit == True || t == True) return True;
    else return Unknown;
}

Trit_num Trit::operator|(const Trit& t)const {
    Trit_num trit1 = this->trit, trit2 = t.trit;

    if (trit1 == False && trit2 == False) return False;
    else if (trit1 == True || trit2 == True) return True;
    else return Unknown;
}
Trit_num Trit::operator~()const {
    if (trit == Unknown) return trit;
    else return static_cast<Trit_num>(0b11 & ~trit);
}