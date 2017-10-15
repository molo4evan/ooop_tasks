//
// Created by User on 015 15.10.17.
//

#include "Trit.h"

Trit::Trit() {
    trit = Trit_num::Unknown;
};

Trit::Trit(Trit_num) {
    this->trit = trit;
}

bool Trit::operator==(Trit_num t) {
    return trit == t;
}

bool Trit::operator!=(Trit_num t) {
    return trit != t;
}

Trit_num Trit::getTrit() {
    return trit;
}