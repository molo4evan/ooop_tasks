//
// Created by User on 022 22.10.17.
//

#include "Tritset.h"

Tritset::InputIterator::InputIterator(Tritset::Reference ref1) : ref(ref1){}

Tritset::InputIterator::InputIterator(const Tritset::InputIterator &iter): ref(iter.ref) {}

bool Tritset::InputIterator::operator!=(InputIterator const &iter) const {
    return !(this->ref.getTritset() == iter.ref.getTritset() && this->ref.getArrayPos() == iter.ref.getArrayPos() && this->ref.getIntPos() == iter.ref.getIntPos());
}

bool Tritset::InputIterator::operator==(InputIterator const &iter) const {
    return (this->ref.getTritset() == iter.ref.getTritset() && this->ref.getArrayPos() == iter.ref.getArrayPos() && this->ref.getIntPos() == iter.ref.getIntPos());
}

Trit_num Tritset::InputIterator::operator*()const {
    Trit_num trit = ref.getTritset()->getTrit(ref.getArrayPos() * BYTE_SIZE * TRIT_SIZE + ref.getIntPos());
    return trit;
}

Tritset::InputIterator& Tritset::InputIterator::operator++() {
    ref.setIntPos(ref.getIntPos() + 1);
    if (ref.getIntPos() == (sizeof(uint) * BYTE_SIZE / TRIT_SIZE)){
        ref.setIntPos(0);
        ref.setArrayPos(ref.getArrayPos() + 1);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Tritset::InputIterator a){
    os << a.ref << " ";
    return os;
}