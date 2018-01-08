//
// Created by User on 008 08.01.18.
//

#include "shared_ptr.h"

namespace my{
    template <class T>
    shared_ptr<T>::shared_ptr() {
        counter = new int(0);
        ptr = nullptr;
    }

    template <class T>
    shared_ptr<T>::shared_ptr(T *ptr) {
        counter = new int(1);
        this->ptr = ptr;
    }

    template <class T>
    shared_ptr<T>::shared_ptr(const shared_ptr<T> &other) {
        this->counter = other.counter;
        *(this->counter)++;
        this->ptr = other.ptr;
    }

    template <class T>
    shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T> &other) {
        if (this == &other) return *this;

        *(this->counter)--;
        if (*(this->counter) <= 0) {
            delete this->ptr;
            delete this->counter;
        }

        this->counter = other.counter;
        *(this->counter)++;
        this->ptr = other.ptr;
    }

    template <class T>
    shared_ptr<T>::~shared_ptr() {
        *(counter)--;
        if (*(counter) <= 0) {
            delete ptr;
            delete counter;
        }
    }

    template <class T>
    bool shared_ptr<T>::operator==(const shared_ptr<T> &other)const {
        return (this->ptr == other.ptr);
    }

    template <class T>
    bool shared_ptr<T>::operator!=(const shared_ptr<T> &other)const {
        return (this->ptr != other.ptr);
    }

    template <class T>
    T& shared_ptr<T>::operator*() {
        return *ptr;
    }

    template <class T>
    T* shared_ptr<T>::operator->() {
        return ptr;
    }
}