//
// Created by User on 026 26.12.17.
//

#include "ArgParser.h"

std::string FileParser::parse(std::string &params) {
    int i = 0;
    for (i; i < params.length(); ++i) {
        if (params[i] == ' ') break;
    }
    return params.substr(0, i);
}

std::string WordParser::parse(std::string &params) {
    int i = 0;
    for (i; i < params.length(); ++i) {
        if (params[i] == ' ') break;
    }
    return params.substr(0, i);
}

void WordsParser::parse(std::string &params, std::string &word1, std::string &word2) {
    int i = 0;
    for (i; i < params.length(); ++i) {
        if (params[i] == ' ') break;
    }
    word1 = params.substr(0, i);

    if (i >= params.length() - 1) throw FlowExcept("wrong command arguments");

    if (params[i] != ' ') throw FlowExcept("wrong command arguments");
    i++;

    int m = i;
    for (i; i < params.length(); ++i) {
        if (params[i] == ' ') break;
    }
    word2 = params.substr(m, i);
}