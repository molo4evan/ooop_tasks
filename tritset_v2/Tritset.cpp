//
// Created by User on 015 15.10.17.
//

#include "Tritset.h"

Tritset::Tritset() {
    set = nullptr;
    set_size = 0;
    start_set_size = 0;
    last_set_trit = 0;
    last_trit = 0;
}

Tritset::Tritset(const uint count) {
    uint tmp_count = (count * TRIT_SIZE) / (BYTE_SIZE * sizeof(uint));
    uint modulo;
    ((count * TRIT_SIZE) % (BYTE_SIZE * sizeof(uint))) == 0 ? modulo = 0 : modulo = 1;

    set_size = tmp_count + modulo;
    set = new uint[set_size];
    assign(set, set_size);
    start_set_size = set_size;
    last_set_trit = 0;
    last_trit = 0;
}

Tritset::Tritset(const Tritset& set){
    set_size = set.set_size;
    start_set_size = set_size;
    last_trit = 0;
    last_set_trit = 0;
    this->set = new uint[set_size];
    for (int i = 0; i < set_size; ++i) {
        this->set[i] = set.set[i];
    }
}

Tritset::~Tritset() {
    delete[] set;
    set = nullptr;
    set_size = 0;
}

uint Tritset::capacity()const {
    return set_size;
}

void Tritset::shrink() {
    uint tmp_count = ((last_set_trit + 1) * TRIT_SIZE) / (BYTE_SIZE * sizeof(uint));
    uint modulo;
    (((last_set_trit + 1) * TRIT_SIZE) % (BYTE_SIZE * sizeof(uint))) == 0 ? modulo = 0 : modulo = 1;

    auto last_set_size = tmp_count + modulo;

    last_set_size > start_set_size ? resize(last_set_size) : resize(start_set_size);
}

uint Tritset::cardinality(Trit_num trit)const {
    uint count = 0;
    for (int i = 0; i <= last_trit; ++i) {
        if ((*this)[i] == trit) ++count;
    }
    return count;
}

std::unordered_map<uint, uint> Tritset::cardinality()const {
    std::unordered_map<uint, uint> map({{0, 0}, {1, 0}, {2, 0}});
    for (int i = 0; i <= last_trit; ++i) {
        if ((*this)[i] == Unknown) map[Unknown]++;
        if ((*this)[i] == False) map[False]++;
        if ((*this)[i] == True) map[True]++;
    }
    return map;
};

void Tritset::trim(uint lastIndex){
    for (int i = lastIndex + 1; i <= last_trit; ++i) {
        (*this)[i] = Unknown;
    }
    last_trit = lastIndex;
    last_set_trit = lastIndex;
    shrink();
}

uint Tritset::length()const {
    return last_trit + 1;
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

Tritset::Reference Tritset::operator[](uint position){
    auto array_pos = (position * TRIT_SIZE) / (BYTE_SIZE * sizeof(uint));
    auto int_pos = position % ((BYTE_SIZE / TRIT_SIZE) * sizeof(uint));
    Reference tmp(array_pos, int_pos, const_cast<const Tritset*>(this));
    return tmp;
}

const Tritset::Reference Tritset::operator[](uint position)const {
    auto array_pos = (position * TRIT_SIZE) / (BYTE_SIZE * sizeof(uint));
    auto int_pos = position % ((BYTE_SIZE / TRIT_SIZE) * sizeof(uint));
    const Reference tmp(array_pos, int_pos, this);
    return tmp;
}

Trit_num Tritset::getTrit(const uint full_pos)const {
    auto cell = (full_pos * TRIT_SIZE) / (BYTE_SIZE * sizeof(uint));
    uint trit_pos = full_pos % ((BYTE_SIZE / TRIT_SIZE) * sizeof(uint));

    if (cell >= set_size) return Unknown;

    uint int_pos = set[cell];

    uint shift = BYTE_SIZE * sizeof(uint) - TRIT_SIZE * (trit_pos + 1);
    auto t_out = static_cast<Trit_num>((int_pos >> shift) & 0b11);
    return t_out;
}

void Tritset::printSet()const {
    for (uint i = 0; i <= last_trit; ++i) {
        Trit_num t = getTrit(i);
        std::cout << t << " ";
    }
    std::cout << std::endl;
}

Tritset& Tritset::operator=(const Tritset& set){
    if ((*this) == set) return (*this);
    if (set_size < set.set_size) resize(set.set_size);
    for (int i = 0; i < set.set_size; ++i) {
        (*this)[i] = set[i];
    }
    set_size = set.set_size;
    last_trit = set.last_trit;
    last_set_trit = last_trit;
}

Tritset Tritset::operator&(const Tritset& set2)const {
    uint new_set_size = 0;
    uint new_last_trit = 0;

    if(this->last_trit > set2.last_trit){
        new_set_size = this->set_size;
        new_last_trit = this->last_trit;
    } else{
        new_set_size = set2.set_size;
        new_last_trit = set2.last_trit;
    }

    Tritset new_set(new_set_size * TRIT_SIZE * BYTE_SIZE);
    for (int i = 0; i <= new_last_trit; i++){
        new_set[i] = (*this)[i] & set2[i];
    }
    return new_set;
}

Tritset Tritset::operator|(const Tritset& set2)const {
    uint new_set_size = 0;
    uint new_last_trit = 0;

    if(this->last_trit > set2.last_trit){
        new_set_size = this->set_size;
        new_last_trit = this->last_trit;
    } else{
        new_set_size = set2.set_size;
        new_last_trit = set2.last_trit;
    }

    Tritset new_set(new_set_size * TRIT_SIZE * BYTE_SIZE);
    for (int i = 0; i <= new_last_trit; i++){
        new_set[i] = (*this)[i] | set2[i];
    }
    return new_set;
}

Tritset Tritset::operator~()const {
    Tritset new_set(set_size * TRIT_SIZE * BYTE_SIZE);
    for (int i = 0; i <= last_trit; i++){
        new_set[i] = ~(*this)[i];
    }
    return new_set;
}

bool Tritset::operator==(const Tritset& set2)const {
    if (this->last_trit != set2.last_trit || this->set_size != set2.set_size) return false;
    for (int i = 0; i < this->last_trit; ++i) {
        if ((*this)[i] != set2[i]) return false;
    }
    return true;
}

bool Tritset::operator!=(const Tritset& set2)const {
    if (this->last_trit != set2.last_trit) return true;
    for (int i = 0; i < this->last_trit; ++i) {
        if ((*this)[i] != set2[i]) return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Tritset& tritset){
    for (int i = 0; i < tritset.last_trit; ++i) {
        os << tritset[i] << " ";
    }
    os << tritset[tritset.last_trit];
    return os;
}

Tritset::iterator Tritset::begin(){
    return iterator((*this)[0]);
}

Tritset::iterator Tritset::end(){
    return iterator((*this)[last_trit + 1]);
}