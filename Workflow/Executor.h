//
// Created by User on 021 21.12.17.
//

#ifndef WORKFLOW_EXECUTOR_H
#define WORKFLOW_EXECUTOR_H
#include <list>
#include "Worker.h"
#include "shared_ptr.h"

typedef std::list<my::shared_ptr<Block>> block_list;

class Executor {
private:
    std::vector<std::string>* text;
public:
    Executor();
    void exec(block_list*);
};


#endif //WORKFLOW_EXECUTOR_H
