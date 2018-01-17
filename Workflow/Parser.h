//
// Created by User on 021 21.12.17.
//

#ifndef WORKFLOW_PARSER_H
#define WORKFLOW_PARSER_H
#include <map>
#include <list>
#include <iostream>
#include "Worker.h"
#include "shared_ptr.h"

typedef std::map<int, my::shared_ptr<Block>> block_map;
typedef std::list<my::shared_ptr<Block>> block_list;

class Parser {
private:
    block_map* get_blocks(std::ifstream&);
    block_list* get_flow(std::ifstream&, block_map*);
public:
    static void init_workers();
    static void delete_workers();
    block_list* parse(std::ifstream&);
};

#endif //WORKFLOW_PARSER_H
