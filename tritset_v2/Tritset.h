//
// Created by User on 015 15.10.17.
//

#ifndef TRITSET_V2_TRITSET_H
#define TRITSET_V2_TRITSET_H

#include "utilites.h"
#include "Trit.h"
#include <iostream>
#include <unordered_map>

class Tritset {
public:
    class Reference {
    private:
        size_t array_pos;
        uint int_pos;
        Tritset* tritset;

        void reallocate();
        friend Trit_num operator&(const Trit_num&, const Tritset::Reference&);
        friend Trit_num operator|(const Trit_num&, const Tritset::Reference&);
        friend bool operator==(const Trit_num&, Tritset::Reference);
        friend bool operator!=(const Trit_num&, Tritset::Reference);
        friend std::ostream& operator<<(std::ostream& os, const Tritset::Reference& trit_ref);
    public:
        Reference(uint, uint, Tritset*);
        Reference(uint, uint, const Tritset*);
        Trit_num operator=(const Trit_num&);
        Trit_num operator=(const Reference&);
        Trit_num operator~()const;
        Trit_num operator&(Reference)const;
        Trit_num operator&(const Trit_num&)const;
        Trit_num operator|(Reference)const;
        Trit_num operator|(const Trit_num&)const;
        bool operator==(Reference)const;
        bool operator==(const Trit_num&)const;
        bool operator!=(Reference)const;
        bool operator!=(const Trit_num&)const;
        Tritset* getTritset() const;
        uint getIntPos() const;
        size_t getArrayPos() const;
        void setIntPos(const uint);
        void setArrayPos(const size_t);
    };

    Tritset();
    explicit Tritset(uint);
    Tritset(const Tritset&);
    ~Tritset();
    uint capacity()const;
    void shrink();
    uint cardinality(Trit_num)const;
    std::unordered_map<uint, uint> cardinality()const;
    void trim(uint);
    uint length()const;
    void printSet()const;

    const Reference operator[](uint)const;
    Reference operator[](uint);
    Tritset& operator=(const Tritset&);
    Tritset operator&(const Tritset&)const;
    Tritset operator|(const Tritset&)const;
    Tritset operator~()const;
    bool operator==(const Tritset&)const;
    bool operator!=(const Tritset&)const;

    class InputIterator: public std::iterator<std::input_iterator_tag, Reference> {
        friend class Tritset;
    private:
        Reference ref;

         explicit InputIterator(Tritset::Reference);
    public:
        InputIterator(const InputIterator&);

        bool operator!=(InputIterator const&) const;
        bool operator==(InputIterator const&) const;
        Trit_num operator*() const;
        InputIterator&operator++();
        friend std::ostream& operator<<(std::ostream&, const InputIterator);
    };

    typedef InputIterator iterator;

    iterator begin();
    iterator end();

private:
    uint* set;
    uint set_size;
    uint start_set_size;
    uint last_set_trit;
    uint last_trit;

    void resize(uint);
    Trit_num getTrit(uint)const;
    friend std::ostream& operator<<(std::ostream& os, const Tritset& tritset);

    friend Trit_num operator&(const Trit_num&, const Tritset::Reference&);
    friend Trit_num operator|(const Trit_num&, const Tritset::Reference&);
    friend bool operator==(const Trit_num&, Tritset::Reference);
    friend bool operator!=(const Trit_num&, Tritset::Reference);
    friend std::ostream& operator<<(std::ostream& os, const Tritset::Reference& trit_ref);
};


#endif //TRITSET_V2_TRITSET_H
