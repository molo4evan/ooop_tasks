//
// Created by User on 015 15.10.17.
//

#ifndef TRITSET_V2_TRITSET_H
#define TRITSET_V2_TRITSET_H

#include "utilites.h"
#include "Trit.h"
#include <iostream>

class Tritset {
private:
    uint* set;
    uint set_size;
    uint start_set_size;
    uint last_set_trit;
    uint last_trit;

    void resize(uint);
    Trit_num getTrit(uint);

public:
    class Reference {
    private:
        uint array_pos;
        uint int_pos;
        Tritset* tritset;

        void reallocate();
    public:
        Reference();
        Reference(uint, uint, Tritset*);
        Trit_num operator=(Trit_num);
        Trit_num operator~();
        Trit_num operator&(Reference);
        Trit_num operator&(Trit_num);
        Trit_num operator|(Reference);
        Trit_num operator|(Trit_num);
        bool operator==(Reference);
        bool operator==(Trit_num);
        bool operator!=(Reference);
        bool operator!=(Trit_num);
        friend std::ostream& operator<<(std::ostream& os, const Tritset::Reference& trit_ref);

    };

    Tritset();
    explicit Tritset(uint);
    ~Tritset();
    uint capacity();
    void shrink();
    Reference operator[](uint);
    void printSet();
    friend std::ostream& operator<<(std::ostream& os, const Tritset::Reference& trit_ref);
    friend std::ostream& operator<<(std::ostream& os, Tritset& tritset);
    Tritset& operator=(Tritset);
    Tritset operator&(Tritset&);
    Tritset operator|(Tritset&);
    Tritset operator~();
    bool operator==(Tritset&);
    bool operator!=(Tritset&);
};


#endif //TRITSET_V2_TRITSET_H
