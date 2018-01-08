//
// Created by User on 021 21.12.17.
//

#include "Parser.h"

std::map<std::string, Worker*> workers;

void Parser::init_workers() {
    workers["readfile"] = new Readfile();
    workers["writefile"] = new Writefile();
    workers["grep"] = new Grep();
    workers["sort"] = new Sort();
    workers["replace"] = new Replace();
    workers["dump"] = new Dump();
}

void Parser::delete_workers() {
    for(auto a: workers){
        delete a.second;
    }
}

std::list<Block*>* Parser::parse(std::ifstream &file) {

    std::map<int, Block*>* blocks = get_blocks(file);

    return get_flow(file, blocks);
}

std::map<int, Block*>* Parser::get_blocks(std::ifstream &file) {
    using namespace std;

    map<int, Block*>* out = new map<int, Block*>;
    string buf;
    getline(file, buf);
    int i = 0;
    for (i; i < buf.length(); ++i) {
        if (buf[i] == ' ' || buf [i] == '#' || buf[i] == '\t') break;
    }
    buf.resize(i);
    i = 0;
    if (buf != "desc") throw FlowExcept("wrong descriptor list opening");

    while(true){
        int id = 0;
        getline(file, buf);
        if (buf[0] == 'c' && buf[1] == 's' && buf[2] == 'e' && buf[3] == 'd') break;

        string block_buf;
        for (i = 0; i < buf.length(); ++i) {
            if (buf[i] == ' ' || buf[i] == '#') break;
        }
        block_buf = buf.substr(0, i);
        if (!block_buf.length()) continue;

        for (int j = 0; j < block_buf.length(); ++j) {
            char n = (block_buf.c_str())[i];
            //if (block_buf[i] < 48 || block_buf[i] > 57) throw FlowExcept("wrong block initialisation");
        }
        id = atoi(block_buf.c_str());

        if (i >= (buf.length() - 3) || buf[i + 1] != '=' || buf[i + 2] != ' ') throw FlowExcept("wrong block initialisation");

        i += 3;
        int m = i;
        for (i; i < buf.length(); ++i) {
            char n = buf[i];
            if (buf[i] == ' ' || buf[i] == '#') break;
        }
        block_buf = buf.substr(m, i - m);

        auto iter = workers.find(block_buf);
        if (iter == workers.end()) throw FlowExcept("wrong block initialisation");
        Worker* worker = workers[block_buf];


        if (i < buf.length() - 1) i++;
        m = i;
        for (i; i < buf.length(); i++) {
            if (buf[i] == '#') break;
        }
        block_buf = buf.substr(m, i - m);

        Block* block = new Block;
        block->params = block_buf;
        block->worker = worker;

        (*out)[id] = block;
    }

    return out;
}

std::list<Block*>* Parser::get_flow(std::ifstream &file, std::map<int, Block*>* blocks) {
    using namespace std;

    auto out = new list<Block*>;
    string list_buf;
    getline(file, list_buf);
    int i = 0;
    for (i; i < list_buf.length(); ++i) {
        if (list_buf[i] == '#') break;
    }
    list_buf.resize(i);
    i = 0;

    while(i < list_buf.size()){
        string id_buf;
        int m = i;
        while(list_buf[i] != ' ' && i != list_buf.length()) i++;
        id_buf.resize(i - m);
        for (int k = 0; k < i - m; ++k) {
            id_buf[k] = list_buf[m + k];
        }

        for (int j = 0; j < id_buf.length(); ++j) {
            if (id_buf[j] < '0' || id_buf[j] > '9') throw FlowExcept("wrong flow initialisation");
        }
        int id = atoi(id_buf.c_str());

        auto iter = blocks->find(id);
        if (iter == blocks->end()) throw FlowExcept("wrong flow initialisation");
        auto block = (*blocks)[id];
        (*out).push_back(block);

        if((i < list_buf.length() - 3) && (list_buf[i] != ' ' || list_buf[i + 1] != '-' || list_buf[i + 2] != '>' || list_buf[i + 3] != ' ')) throw FlowExcept("wrong flow initialisation");

        i += 4;
    }

    return out;
}