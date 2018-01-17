//
// Created by User on 008 08.01.18.
//

#ifndef WORKFLOW_SHARED_PTR_H
#define WORKFLOW_SHARED_PTR_H

namespace my {
    template<class T>
    class shared_ptr {
    private:
        int *counter;
        T *ptr;
    public:
        shared_ptr();
        explicit shared_ptr(T *);
        shared_ptr(const shared_ptr&);
        ~shared_ptr();
        T &operator*();
        T *operator->();
        shared_ptr& operator=(const shared_ptr&);
        bool operator==(const shared_ptr &)const;
        bool operator!=(const shared_ptr &)const;
    };

    template <class T>
    shared_ptr<T>::shared_ptr() {
        counter = new int(1);
        ptr = new T;
    }

    template <class T>
    shared_ptr<T>::shared_ptr(T *ptr) {
        counter = new int(1);
        this->ptr = ptr;
    }

    template <class T>
    shared_ptr<T>::shared_ptr(const shared_ptr<T> &other) {
        this->counter = other.counter;
        *(this->counter) += 1;
        this->ptr = other.ptr;
    }

    template <class T>
    shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T> &other) {
        if (this == &other) return *this;

        *(this->counter) -= 1;
        if (*(this->counter) == 0) {
            delete this->ptr;
            delete this->counter;
        }

        this->counter = other.counter;
        *(this->counter) += 1;
        this->ptr = other.ptr;
    }

    template <class T>
    shared_ptr<T>::~shared_ptr() {
        *(counter) -= 1;
        if (*(counter) <= 0) {
            delete ptr;
            ptr = nullptr;
            delete counter;
            counter = nullptr;
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

#endif //WORKFLOW_SHARED_PTR_H
