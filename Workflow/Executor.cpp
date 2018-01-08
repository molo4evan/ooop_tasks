//
// Created by User on 021 21.12.17.
//

#include "Executor.h"

void Executor::exec(std::list<Block*> *flow) {
    for (auto block: (*flow)){
        std::string p = block->params;
        text = block->worker->exec(p, text);
    }
    //delete[] flow;                //TODO: working version (shared_ptr?)
}