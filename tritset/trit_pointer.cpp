//
// Created by User on 026 26.09.17.
//

#include "trit_pointer.h"
#include "tritset.h"

Trit_pointer::Trit_pointer(uint pos, Tritset* set) {
    this->full_pos = pos;
    this->set = set;
    this->set_size = 0;
}

Trit_pointer::Trit_pointer(uint pos, Tritset* set, uint set_size) {
    this->full_pos = pos;
    this->set = set;
    this->set_size = set_size;
}

void Trit_pointer::reallocate() {
    uint needed_set_size = this->full_pos * TRIT_SIZE / BYTE_SIZE / sizeof(uint);
    uint double_start_set_size = this->set_size * 2;
    uint new_set_size;
    needed_set_size > double_start_set_size ? (new_set_size = needed_set_size) : (new_set_size = double_start_set_size);

    vector<uint> *old_vector = this->set->getSet();
    old_vector->resize(new_set_size, 0);

    set->setCapacity(new_set_size);
}

uint* Trit_pointer::getAccuratePos(uint* trit_pos){
    auto cell = static_cast<uint>(full_pos * TRIT_SIZE / BYTE_SIZE / sizeof(uint));
    *trit_pos = full_pos % ((BYTE_SIZE / TRIT_SIZE) * sizeof(uint));
    uint* int_pos = set->getSet()->data() + cell * sizeof(uint);
    return int_pos;
}

Trit Trit_pointer::operator =(Trit trit) {
    if (set_size != 0){        //it means position is more then tritset size
        if (trit == Unknown){
            return trit;
        }
        else {
            this->reallocate();
        }
    }

    set->setLastTrit(full_pos);

    uint trit_pos = 0;
    uint* int_pos = nullptr;
    int_pos = this->getAccuratePos(&trit_pos);

    uint shift = BYTE_SIZE * sizeof(uint) - TRIT_SIZE * (trit_pos - 1);
    auto void_mask = static_cast<uint>(~(0b11 << shift));

    *int_pos &= void_mask;

    uint trit_mask = trit << shift;
    *int_pos |= trit_mask;
    delete this;
    return trit;
}