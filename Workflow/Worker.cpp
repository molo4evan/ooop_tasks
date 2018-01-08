//
// Created by User on 021 21.12.17.
//

#include "Worker.h"

using namespace std;

Block::Block(Worker *w, std::string &p) {
    worker = w;
    params = p;
}

std::vector<std::string>* Readfile::exec(std::string& params, std::vector<std::string>*) {
    FileParser ap;
    string name = ap.parse(params);
    file.open(name);
    if (!file.is_open()) throw FlowExcept("file opening error");

    string str;
    vector<string>* text = new vector<string>;
    while (!file.eof()){
        getline(file, str);
        (*text).push_back(str);
    }
    file.close();
    return text;
}

std::vector<std::string>* Writefile::exec(std::string& params, std::vector<std::string>* text) {
    FileParser ap;
    string name = ap.parse(params);
    file.open(name);
    if (!file.is_open()) throw FlowExcept("file opening error");

    for (int i = 0; i < text->size() - 1; i++) {
        file << (*text)[i] << endl;
    }
    file << (*text)[text->size() - 1];
    file.close();
    delete text;
    return nullptr;
}

std::vector<std::string>* Grep::exec(std::string& params, std::vector<std::string>* text) {
    WordParser ap;
    string word = ap.parse(params);

    vector<string>* new_text = new vector<string>;
    for (int i = 0; i < text->size(); i++){
        if ((*text)[i].find(word) != string::npos) (*new_text).push_back((*text)[i]);
    }

    delete text;
    return new_text;
}

std::vector<std::string>* Sort::exec(std::string&, std::vector<std::string>* text) {
    for (int i = (*text).size() - 1; i > 1; --i) {
        for (int j = 0; j < i; ++j) {
            if ((*text)[j] > (*text)[j + 1]) {
                string tmp = (*text)[j];
                (*text)[j] = (*text)[j + 1];
                (*text)[j + 1] = tmp;
            }
        }
    }
    return text;
}

std::vector<std::string>* Replace::exec(std::string& params, std::vector<std::string>* text) {
    WordsParser ap;
    string old_str, new_str;
    ap.parse(params, old_str, new_str);

    for (int i = 0; i < text->size(); i++){
        size_t pos = (*text)[i].find(old_str);
        if (pos == string::npos) continue;
        (*text)[i].replace(pos, old_str.length(), new_str);

    }

    return text;
}

std::vector<std::string>* Dump::exec(std::string& params, std::vector<std::string>* text) {
    FileParser ap;
    string name = ap.parse(params);
    file.open(name);
    if (!file.is_open()) throw FlowExcept("file opening error");

    for (int i = 0; i < text->size() - 1; i++) {
        file << (*text)[i] << endl;
    }
    file << (*text)[text->size() - 1];
    file.close();
    return text;
}