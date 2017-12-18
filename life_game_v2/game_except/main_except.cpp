//
// Created by User on 026 26.11.17.
//

#include "main_except.h"

Main_except::Main_except() {
    err_arg = "";
}

Main_except::Main_except(const std::string &err_line) {
    err_arg = err_line;
}

void Main_except::print_msg() {
    if (err_arg.empty()) std::cout << "Sorry, there is some unclassified error." << std::endl;
    else std::cout << "Sorry, there is some unclassified error in here: " << err_arg << std::endl;
}


void Cmd_except::print_msg() {
    if (err_arg.empty()) std::cout << "Error: wrong command." << std::endl;
    else std::cout << "ERROR. Wrong command: " << err_arg << std::endl;
}


void Args_except::print_msg() {
    if (err_arg.empty()) std::cout << "Error: too few arguments." << std::endl;
    else std::cout << "ERROR. Wrong command argument: " << err_arg << std::endl;
}


File_except::File_except(): Main_except() {
    state = none;
}

File_except::File_except(const std::string &text): Main_except(text) {
    state = none;
}

File_except::File_except(const std::string &text, Case state, bool isl, int x, int y): Main_except(text) {
    this->state = state;
    load = isl;
    this->x = x;
    this->y = y;
}

void File_except::print_msg() {
    if (state == none) std::cout << "ERROR: wrong file format." << std::endl;
    else if (state == name) std::cout << "ERROR. Wrong file name: " << err_arg << std::endl;
    else if (state == size_format) std::cout << "ERROR. Wrong size format: " << err_arg << std::endl;
    else if (state == field_format) std::cout << "ERROR. Wrong field filling format in position " << x << " " << y << std::endl;
}


void Delay_except::print_msg() {
    if (err_arg.empty()) std::cout << "ERROR: wrong delay." << std::endl;
    else std::cout << "ERROR: wrong delay: " << std::endl << err_arg << std::endl;
}

void Back_except::print_msg() {
    std::cout << "ERROR: you already got backuped state." << std::endl;
}

void Loop_except::print_msg() {
    std::cout << "Actually, your life was looped." << std::endl;
}