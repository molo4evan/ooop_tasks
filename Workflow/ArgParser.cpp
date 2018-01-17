//
// Created by User on 026 26.12.17.
//

#include "ArgParser.h"

std::string WordParser::parse(std::string &params) {
    int i = 0;
    for (i; i < params.length(); ++i) {
        if (params[i] == ' ' || params[i] == '\t') break;
    }
    return params.substr(0, i);
}

void WordsParser::parse(std::string &params, std::string &word1, std::string &word2) {
    int i = 0;
    for (i; i < params.length(); ++i) {
        if (params[i] == ' ' || params[i] == '\t') break;
    }
    word1 = params.substr(0, i);

    while(i < params.length() && (params[i] == ' ' || params[i] == '\t')) i++;
    if (i >= params.length()) throw FlowExcept("wrong command arguments");

    int m = i;
    for (i; i < params.length(); ++i) {
        if (params[i] == ' ' || params[i] == '\t') break;
    }
    word2 = params.substr(m, i - m);
}