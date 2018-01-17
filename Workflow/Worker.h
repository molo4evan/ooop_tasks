//
// Created by User on 021 21.12.17.
//

#ifndef WORKFLOW_WORKER_H
#define WORKFLOW_WORKER_H
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "ArgParser.h"
#include "FlowExcept.h"

class Worker {
public:
    Worker() = default;
    virtual ~Worker() = default;
    virtual std::vector<std::string>* exec(std::string&, std::vector<std::string>*) = 0;
};

class Block{
public:
    Worker* worker;
    std::string params;
    Block() = default;
    Block(Worker*, std::string&);
    //bool operator<(Block& other){return (this->worker < other.worker);}
};

class Readfile: public Worker{
private:
    std::ifstream file;
public:
    std::vector<std::string>* exec(std::string&, std::vector<std::string>*) override;
};

class Writefile: public Worker{
private:
    std::ofstream file;
public:
    std::vector<std::string>* exec(std::string&, std::vector<std::string>*) override;
};

class Grep: public Worker{
public:
    std::vector<std::string>* exec(std::string&, std::vector<std::string>*) override;
};

class Sort: public Worker{
public:
    std::vector<std::string>* exec(std::string&, std::vector<std::string>*) override;
};

class Replace: public Worker{
public:
    std::vector<std::string>* exec(std::string&, std::vector<std::string>*) override;
};

class Dump: public Worker{
private:
    std::ofstream file;
public:
    std::vector<std::string>* exec(std::string&, std::vector<std::string>*) override;
};

#endif //WORKFLOW_WORKER_H
