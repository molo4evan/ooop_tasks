//
// Created by User on 021 21.12.17.
//

#ifndef WORKFLOW_PARSER_H
#define WORKFLOW_PARSER_H
#include <map>
#include <list>
#include "Worker.h"

class Parser {
private:
    std::map<int, Block*>* get_blocks(std::ifstream&);
    std::list<Block*>* get_flow(std::ifstream&, std::map<int, Block*>*);
public:
    static void init_workers();
    static void delete_workers();
    std::list<Block*>* parse(std::ifstream&);
};

#endif //WORKFLOW_PARSER_H
