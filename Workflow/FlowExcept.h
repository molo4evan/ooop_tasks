//
// Created by User on 007 07.01.18.
//

#ifndef WORKFLOW_FLOWEXCEPT_H
#define WORKFLOW_FLOWEXCEPT_H
#include <string>
#include <iostream>

class FlowExcept {
private:
    std::string message;
public:
    FlowExcept() = delete;
    FlowExcept(std::string&&);
    void printMsg();
};


#endif //WORKFLOW_FLOWEXCEPT_H
