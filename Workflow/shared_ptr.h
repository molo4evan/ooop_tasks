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
        shared_ptr &operator=(shared_ptr &);
        bool operator==(const shared_ptr &)const;
        bool operator!=(const shared_ptr &)const;
    };
}

#endif //WORKFLOW_SHARED_PTR_H
