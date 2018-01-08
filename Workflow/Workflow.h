//
// Created by User on 021 21.12.17.
//

#ifndef WORKFLOW_WORKFLOW_H
#define WORKFLOW_WORKFLOW_H
#include "Executor.h"
#include "Parser.h"

class Workflow {
private:
    std::string file;
    Executor* executor;
    Parser* parser;
public:
    Workflow() = delete;
    explicit Workflow(const std::string&);
    ~Workflow();
    void handle();
};


#endif //WORKFLOW_WORKFLOW_H
