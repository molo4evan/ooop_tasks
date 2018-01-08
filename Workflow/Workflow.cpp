//
// Created by User on 021 21.12.17.
//

#include "Workflow.h"

Workflow::Workflow(const std::string &f) {
    file = f;
    executor = new Executor;
    parser = new Parser;
    parser->init_workers();
}

Workflow::~Workflow() {
    parser->delete_workers();
    delete executor;
    delete parser;
}

void Workflow::handle() {
    using namespace std;

    ifstream config(file);

    try {
        block_list* flow = parser->parse(config);
        executor->exec(flow);
    }

    catch (FlowExcept& exc){
        exc.printMsg();
        return;
    }
    //TODO: here can b ur exceptions
}