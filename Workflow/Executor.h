//
// Created by User on 021 21.12.17.
//

#ifndef WORKFLOW_EXECUTOR_H
#define WORKFLOW_EXECUTOR_H
#include <list>
#include "Worker.h"

class Executor {
private:
    std::vector<std::string>* text;
public:
    void exec(std::list<Block*>*);
};


#endif //WORKFLOW_EXECUTOR_H
