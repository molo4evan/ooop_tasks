//
// Created by User on 026 26.09.17.
//
#include "tritset.h"
#include "trit_pointer.h"

Tritset::Tritset(){
    this->set_size = 0;
    this->set = nullptr;
    this->start_size = 0;
    this->last_set_trit = 0;
}

Tritset::Tritset(uint count){
    double tmp_count = (static_cast<double>(count) * TRIT_SIZE / BYTE_SIZE / sizeof(uint));
    uint modulo;
    (tmp_count - static_cast<uint>(tmp_count)) == 0 ? modulo = 0 : modulo = 1;

    this->set_size = static_cast<uint>(tmp_count) + modulo;
    this->set = new vector<uint>(set_size);
    this->start_size = count;
    this->last_set_trit = 0;
}

Tritset::~Tritset(){
    delete set;
}

uint Tritset::capacity(){
    return this->set_size;
}

vector<uint>* Tritset::getSet() {
    return this->set;
}

void Tritset::setCapacity(uint size) {
    this->set_size = size;
}

void Tritset::setLastTrit(uint position) {

    if (this->last_set_trit < position) this->last_set_trit = position;
}

uint Tritset::getLastTrit() {
    return last_set_trit;
}

Trit_pointer& Tritset::operator [](uint position){
    Trit_pointer* trit_pointer;

    double tmp_count = (static_cast<double>(position + 1) * TRIT_SIZE / BYTE_SIZE / sizeof(uint));
    uint modulo;
    (tmp_count - static_cast<uint>(tmp_count)) == 0 ? modulo = 0 : modulo = 1;

    uint real_needed_capacity = static_cast<uint>(tmp_count) + modulo;

    if (real_needed_capacity > this->capacity()){
        trit_pointer = new Trit_pointer(position, this, this->capacity());
    }
    else {
        trit_pointer = new Trit_pointer(position, this);
    }

    return *trit_pointer;
}

Trit Tritset::getTrit(uint full_pos){
    auto cell = static_cast<uint>(full_pos * TRIT_SIZE / BYTE_SIZE / sizeof(uint));
    uint trit_pos = full_pos % ((BYTE_SIZE / TRIT_SIZE) * sizeof(uint));
    uint *int_pos = this->getSet()->data() + cell * sizeof(uint);

    uint shift = BYTE_SIZE * sizeof(uint) - TRIT_SIZE * (trit_pos - 1);
    auto t_out = static_cast<Trit>((*int_pos >> shift) & 0b11);
    return t_out;
}

void Tritset::printSet() {
    for (uint i = 0; i <= this->getLastTrit(); ++i) {
        Trit t = this->getTrit(i);                      //!!!!!!!!!!!!!!!!!
        print_trit(t);
    }
    cout << endl;
}
