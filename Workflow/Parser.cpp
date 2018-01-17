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

block_list* Parser::parse(std::ifstream &file) {

    block_map* blocks = get_blocks(file);

    return get_flow(file, blocks);
}

block_map* Parser::get_blocks(std::ifstream &file) {
    using namespace std;

    block_map* out = new block_map;
    string buf;
    getline(file, buf);
    buf.resize(4);
    if (buf != "desc") throw FlowExcept("wrong descriptor list initialisation");

    while(true){
        int id = 0;
        getline(file, buf);
        if (buf.substr(0, 4) == "csed") break;
        string block_buf;

        int i = 0;
        while(i < buf.length() && (buf[i]== ' ' || buf[i] == '\t')) i++;
        if (i >= buf.length()) continue;

        int k = i;
        for (i; i < buf.length(); ++i) {
            if (buf[i] == ' ' || buf[i] == '#' || buf[i] == '\t') break;
        }
        if (i - k == 0) continue;

        block_buf = buf.substr(k, i - k);
        if (!block_buf.length()) continue;

        for (char j : block_buf) {
            if (j < '0' || j > '9') throw FlowExcept("wrong block initialisation");
        }
        id = atoi(block_buf.c_str());

        while (i < buf.length() && (buf[i] == ' ' || buf[i] == '\t')) i++;
        if (i >= (buf.length()) || buf[i] != '=') throw FlowExcept("wrong block initialisation");
        i++;
        while (i < buf.length() && (buf[i] == ' ' || buf[i] == '\t')) i++;

        int m = i;
        for (i; i < buf.length(); ++i) {
            if (buf[i] == ' ' || buf[i] == '#') break;
        }
        if (i - m == 0) throw FlowExcept("wrong block initialisation");

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

        my::shared_ptr<Block> block;
        block->params = block_buf;
        block->worker = worker;

        (*out)[id] = block;
    }

    return out;
}

block_list* Parser::get_flow(std::ifstream &file, block_map* blocks) {
    using namespace std;

    auto out = new block_list;
    string list_buf;
    {
        getline(file, list_buf);
    } while (list_buf.empty() && !file.eof());
    if (list_buf.empty()) throw FlowExcept("no flow");

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

        for (char j : id_buf) {
            if (j < '0' || j > '9') throw FlowExcept("wrong flow initialisation");
        }
        int id = atoi(id_buf.c_str());

        auto iter = blocks->find(id);
        if (iter == blocks->end()) throw FlowExcept("wrong flow initialisation");
        auto block = (*blocks)[id];
        (*out).push_back(block);

        while (i < list_buf.length() && (list_buf[i] == ' ' || list_buf[i] == '\t')) i++;
        if (i < list_buf.length() && list_buf[i] == '#') break;
        if (i < list_buf.length() - 1 && list_buf.substr(i, 2) != "->") throw FlowExcept("wrong flow initialisation");
        i += 2;
        while (i < list_buf.length() && (list_buf[i] == ' ' || list_buf[i] == '\t')) i++;
        if (i >= list_buf.length()) break;
    }

    delete blocks;
    return out;
}