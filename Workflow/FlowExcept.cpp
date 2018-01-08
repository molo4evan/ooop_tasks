//
// Created by User on 007 07.01.18.
//

#include "FlowExcept.h"

FlowExcept::FlowExcept(std::string &&str) {
    message = str;
}

void FlowExcept::printMsg() {
    std::cout << "ERROR: " << message << "!" << std::endl;
}