//
// Created by User on 015 15.10.17.
//

#include "Tritset.h"
#include <iostream>

Tritset::Tritset() {
    set = nullptr;
    set_size = 0;
    start_set_size = 0;
    last_set_trit = 0;
    last_trit = 0;
}

Tritset::Tritset(uint count) {
    double tmp_count = (static_cast<double>(count) * TRIT_SIZE / BYTE_SIZE / sizeof(uint));
    uint modulo;
    (tmp_count - static_cast<uint>(tmp_count)) == 0 ? modulo = 0 : modulo = 1;

    set_size = static_cast<uint>(tmp_count) + modulo;
    set = new uint[set_size];
    assign(set, set_size);
    start_set_size = set_size;
    last_set_trit = 0;
    last_trit = 0;
}

Tritset::~Tritset() {
    delete[] set;
    set = nullptr;
    set_size = 0;
}

uint Tritset::capacity() {
    return set_size * BYTE_SIZE * TRIT_SIZE;
}

void Tritset::shrink() {

    double tmp_count = (static_cast<double>(last_set_trit + 1) * TRIT_SIZE / BYTE_SIZE / sizeof(uint));
    uint modulo;
    (tmp_count - static_cast<uint>(tmp_count)) == 0 ? modulo = 0 : modulo = 1;

    auto last_set_size = static_cast<uint>(tmp_count) + modulo;

    last_set_size > start_set_size ? resize(last_set_size) : resize(start_set_size);
}

void Tritset::resize(uint new_size) {
    uint* new_arr = new uint[new_size];
    assign(new_arr, new_size);

    uint copy_size = set_size < new_size ? set_size : new_size;
    for (int i = 0; i < copy_size; ++i) {
        new_arr[i] = set[i];
    }
    delete[] set;
    set = new_arr;
    set_size = new_size;
}

Tritset::Reference Tritset::operator[](uint position) {
    auto array_pos = static_cast<uint>(position * TRIT_SIZE / BYTE_SIZE / sizeof(uint));
    auto int_pos = position % ((BYTE_SIZE / TRIT_SIZE) * sizeof(uint));

    Reference tmp(array_pos, int_pos, this);
    return tmp;
}

Trit_num Tritset::getTrit(uint full_pos){
    auto cell = static_cast<uint>(full_pos * TRIT_SIZE / BYTE_SIZE / sizeof(uint));
    uint trit_pos = full_pos % ((BYTE_SIZE / TRIT_SIZE) * sizeof(uint));
    uint int_pos = set[cell];

    uint shift = BYTE_SIZE * sizeof(uint) - TRIT_SIZE * (trit_pos + 1);
    auto t_out = static_cast<Trit_num>((int_pos >> shift) & 0b11);
    return t_out;
}

void Tritset::printSet() {
    for (uint i = 0; i <= last_trit; ++i) {
        Trit_num t = getTrit(i);
        std::cout << t << " ";
    }
    std::cout << std::endl;
}

Tritset& Tritset::operator=(Tritset set){
    if (set_size < set.set_size) resize(set.set_size);
    for (int i = 0; i < set.set_size; ++i) {
        (*this)[i] = set[i];
    }
}

Tritset Tritset::operator&(Tritset& set2){
    uint new_set_size = 0;
    uint new_last_trit = 0;

    if(this->last_trit > set2.last_trit){
        new_set_size = this->set_size;
        new_last_trit = this->last_trit;
    } else{
        new_set_size = set2.set_size;
        new_last_trit = set2.last_trit;
    }

    Tritset new_set(new_set_size);
    for (int i = 0; i <= new_last_trit; i++){
        new_set[i] = (*this)[i] & set2[i];                        //????????????????
    }
    return new_set;
}

Tritset Tritset::operator|(Tritset& set2){
    uint new_set_size = 0;
    uint new_last_trit = 0;

    if(this->last_trit > set2.last_trit){
        new_set_size = this->set_size;
        new_last_trit = this->last_trit;
    } else{
        new_set_size = set2.set_size;
        new_last_trit = set2.last_trit;
    }

    Tritset new_set(new_set_size);
    for (int i = 0; i <= new_last_trit; i++){
        new_set[i] = (*this)[i] | set2[i];                        //????????????????
    }
    return new_set;
}

Tritset Tritset::operator~(){
    Tritset new_set(set_size);
    for (int i = 0; i <= last_trit; i++){
        new_set[i] = ~(*this)[i];
    }
    return new_set;
}

bool Tritset::operator==(Tritset& set2){
    if (this->last_trit != set2.last_trit) return false;
    for (int i = 0; i < this->last_trit; ++i) {
        if ((*this)[i] != set2[i]) return false;
    }
    return true;
}

bool Tritset::operator!=(Tritset& set2){
    if (this->last_trit != set2.last_trit) return true;
    for (int i = 0; i < this->last_trit; ++i) {
        if ((*this)[i] != set2[i]) return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, Tritset& tritset){
    for (int i = 0; i < tritset.last_trit; ++i) {
        os << tritset[i] << " ";
    }
    os << tritset[tritset.last_trit];
    return os;
}