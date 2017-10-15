//
// Created by User on 015 15.10.17.
//

#include "Tritset.h"

Tritset::Reference::Reference() = default;

Tritset::Reference::Reference(uint array_pos, uint int_pos, Tritset* tritset) {
    this->array_pos = array_pos;
    this->int_pos = int_pos;
    this->tritset = tritset;
}

void Tritset::Reference::reallocate(){
    uint needed_set_size = array_pos + 1;
    uint double_start_set_size = tritset->set_size * 2;
    uint new_set_size;
    if(needed_set_size > double_start_set_size) new_set_size = needed_set_size;
    else new_set_size = double_start_set_size;

    tritset->resize(new_set_size);
}

Trit_num Tritset::Reference::operator=(Trit_num trit) {
    if (array_pos >= tritset->set_size){
        if (trit == Unknown) {
            tritset->last_set_trit = 0;
            return trit;
        }
        else reallocate();
    }

    if (trit == Unknown) tritset->last_set_trit = 0;
    else tritset->last_set_trit = (array_pos * BYTE_SIZE * TRIT_SIZE) + int_pos;
    if (tritset->last_set_trit > tritset->last_trit) tritset->last_trit = tritset->last_set_trit;

    uint shift = BYTE_SIZE * sizeof(uint) - TRIT_SIZE * (int_pos + 1);
    auto void_mask = static_cast<uint>(~(0b11 << shift));

    tritset->set[array_pos] &= void_mask;

    uint trit_mask = trit << shift;
    tritset->set[array_pos] |= trit_mask;
    return trit;
}

Trit_num Tritset::Reference::operator~(){
    if (array_pos >= tritset->set_size) return Unknown;

    uint shift = BYTE_SIZE * sizeof(uint) - TRIT_SIZE * (int_pos + 1);

    uint get_mask = static_cast<uint>(0b11 << shift);

    uint trit = (tritset->set[array_pos] & get_mask) >> shift;
    if (trit == Unknown) return Unknown;
    Trit_num untrit = static_cast<Trit_num>(0b11 & ~trit);

    return untrit;
}

Trit_num Tritset::Reference::operator&(Reference trit2_ref){
    Trit_num trit1 = tritset->getTrit(array_pos * BYTE_SIZE * TRIT_SIZE + int_pos);

    Trit_num trit2 = trit2_ref.tritset->getTrit(array_pos * BYTE_SIZE * TRIT_SIZE + int_pos);

    if (trit1 == False || trit2 == False) return False;
    else if (trit1 == True && trit2 == True) return True;
    else return Unknown;
}

Trit_num Tritset::Reference::operator&(Trit_num trit2){
    Trit_num trit1 = tritset->getTrit(array_pos * BYTE_SIZE * TRIT_SIZE + int_pos);

    if (trit1 == False || trit2 == False) return False;
    else if (trit1 == True && trit2 == True) return True;
    else return Unknown;
}

Trit_num Tritset::Reference::operator|(Reference trit2_ref){
    Trit_num trit1 = tritset->getTrit(array_pos * BYTE_SIZE * TRIT_SIZE + int_pos);

    Trit_num trit2 = trit2_ref.tritset->getTrit(array_pos * BYTE_SIZE * TRIT_SIZE + int_pos);

    if (trit1 == False && trit2 == False) return False;
    else if (trit1 == True || trit2 == True) return True;
    else return Unknown;
}

Trit_num Tritset::Reference::operator|(Trit_num trit2){
    Trit_num trit1 = tritset->getTrit(array_pos * BYTE_SIZE * TRIT_SIZE + int_pos);

    if (trit1 == False && trit2 == False) return False;
    else if (trit1 == True || trit2 == True) return True;
    else return Unknown;
}

bool Tritset::Reference::operator==(Reference trit2_ref){
    Trit_num trit1 = tritset->getTrit(array_pos * BYTE_SIZE * TRIT_SIZE + int_pos);

    Trit_num trit2 = trit2_ref.tritset->getTrit(array_pos * BYTE_SIZE * TRIT_SIZE + int_pos);

    return trit1 == trit2;
}

bool Tritset::Reference::operator==(Trit_num trit2){
    Trit_num trit1 = tritset->getTrit(array_pos * BYTE_SIZE * TRIT_SIZE + int_pos);

    return trit1 == trit2;
}

bool Tritset::Reference::operator!=(Reference trit2_ref){
    Trit_num trit1 = tritset->getTrit(array_pos * BYTE_SIZE * TRIT_SIZE + int_pos);

    Trit_num trit2 = trit2_ref.tritset->getTrit(array_pos * BYTE_SIZE * TRIT_SIZE + int_pos);

    return trit1 != trit2;
}

bool Tritset::Reference::operator!=(Trit_num trit2){
    Trit_num trit1 = tritset->getTrit(array_pos * BYTE_SIZE * TRIT_SIZE + int_pos);

    return trit1 != trit2;
}

std::ostream& operator<<(std::ostream& os, const Tritset::Reference& trit_ref){
    Trit_num trit = trit_ref.tritset->getTrit(trit_ref.array_pos * BYTE_SIZE * TRIT_SIZE + trit_ref.int_pos);

        if (trit == Unknown) os << "Unknown";
        else if (trit == False) os << "False";
        else if (trit == True) os << "True";

    return os;
}