//
// Created by User on 021 21.12.17.
//

#include "Executor.h"

void Executor::exec(block_list *flow) {
    for (auto block: (*flow)){
        std::string p = block->params;
        text = block->worker->exec(p, text);
    }
    delete flow;
}