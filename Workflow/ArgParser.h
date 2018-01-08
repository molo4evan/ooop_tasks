//
// Created by User on 026 26.12.17.
//

#ifndef WORKFLOW_ARGPARSER_H
#define WORKFLOW_ARGPARSER_H

#include <string>
#include "FlowExcept.h"

class FileParser{
public:
    std::string parse(std::string&);
};

class WordParser{
public:
    std::string parse(std::string&);
};

class WordsParser{
public:
    void parse(std::string&, std::string&, std::string&);
};

#endif //WORKFLOW_ARGPARSER_H
