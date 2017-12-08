//
// Created by User on 003 03.12.17.
//

#include "Game.h"
#include <windows.h>
using namespace std;

Game::Executor::Executor(const std::string &c, Game* g) {
    cmd = c;
    tail = "";
    game = g;
}

Game::Executor::Executor(const std::string &c, const std::string &t, Game* g) {
    cmd = c;
    tail = t;
    game = g;
}

void Game::Executor::get_size(std::string &input, int* arg1, int* arg2) {
    string buf;
    int cnt = 0;
    while (input[cnt] != ' ') {
        buf.push_back(input[cnt]);
        cnt++;
    }
    if (!buf.length()) throw Args_except();
    for (char i : buf) {
        if (i < '0' || i > '9') throw Args_except(buf);
    }
    *arg1 = atoi(buf.c_str());
    if (*arg1 > 58) throw Args_except(buf);

    cnt++;
    buf = "";
    while (input[cnt] != ' ') {
        buf.push_back(input[cnt]);
        cnt++;
    }
    if (!buf.length()) throw Args_except();
    for (char i : buf) {
        if (i < '0' || i > '9') throw Args_except(buf);
    }
    *arg2 = atoi(buf.c_str());
    if (*arg2 > 999) throw Args_except(buf);
}

void Game::Executor::get_coords(std::string &input, int* arg1, int* arg2) {
    string buf;
    int cnt;

    string exc_str(input);
    exc_str.resize(1);
    if (input.length() < 2) throw Args_except();
    if (input[0] < 'A' || (input[0] > 'Z' && input[0] < 'a') || input[0] > 'z') throw Args_except(exc_str);

    if (input[0] >= 'a') *arg1 = input[0] - 'a' + 26;
    else *arg1 = input[0] - 'A';
    if (*arg1 > game->field->get_x()) throw Args_except(exc_str);
    cnt = 1;
    while (input[cnt] != ' ') {
        buf.push_back(input[cnt]);
        cnt++;
    }
    for (char i : buf) {
        if (i < '0' || i > '9') throw Args_except(buf);
    }
    *arg2 = atoi(buf.c_str());
    if (*arg2 > game->field->get_y()) throw Args_except(buf);
}

void Game::Executor::exec_cmd() {
    int arg1 = 0, arg2 = 0;

    bool empty = true;
    for (char i : cmd) {
        if (i != '\n' && i != ' ' && i != '\t') {
            empty = false;
            break;
        }
    }
    if (empty) return;

    if (cmd == "exit") throw Exit_except();
    else if (cmd == "reset") {
        game->field->clear();
        game->steps = 0;
        game->backed = false;
    }
    else if (cmd == "set") {
        get_coords(tail, &arg1, &arg2);
        game->field->set_cell(arg1, arg2);
    }
    else if (cmd == "clear") {
        get_coords(tail, &arg1, &arg2);
        game->field->clear_cell(arg1, arg2);
    }
    else if (cmd == "step") {
        step(tail);
    }
    else if (cmd == "back") {
        if (game->backed) throw Back_except();
        Field* tmp = game->field;
        game->field = game->backuped_field;
        game->backuped_field = tmp;
        game->backed = true;
        game->steps--;
    }
    else if (cmd == "store") {
        store(tail);
    }
    else if (cmd == "load") {
        load(tail);
    }
    else if (cmd == "autoplay") {
        autoplay(tail);
    }
    else if (cmd == "resize") {
        get_size(tail, &arg1, &arg2);
        game->field->resize(arg1, arg2);
    }
    else if (cmd == "help") {
        help();
    }
    else throw Cmd_except(cmd);
}

void Game::Executor::step(std::string &input) {
    string buf;
    int cnt = 0, steps = 0;
    while (input[cnt] != ' ') {
        buf.push_back(input[cnt]);
        cnt++;
    }
    for (char i : buf) {
        if (i < '0' || i > '9') throw Args_except(buf);
    }
    steps = atoi(buf.c_str());
    for (int i = 0; i < steps; ++i) {
        *(game->backuped_field) = *(game->field);
        game->field->recalculate();
        game->steps++;
    }
    game->backed = false;
}

void Game::Executor::store(std::string &file) {
    int cnt = 0;
    while (file[cnt] != ' ' && cnt < file.length()) cnt++;
    file.resize(cnt);
    ofstream out(file);
    out << game->field->get_x() << endl;
    out << game->field->get_y() << endl;
    for (int i = 0; i < game->field->get_y(); ++i) {
        for (int j = 0; j < game->field->get_x(); ++j) {
            out << game->field->get_cell(j, i);
        }
        out << endl;
    }
}

void Game::Executor::load(string& file) {
    int cnt = 0, x = 0, y = 0;
    while (file[cnt] != ' ' && cnt < file.length()) cnt++;
    file.resize(cnt);
    ifstream in(file);
    if (in.fail()) throw File_except(file, File_except::name);
    char c;
    char str[10];
    for (int m = 0; m < 10; ++m) {
        str[m] = 1;
    }
    in.getline(str, 10, '\n');
    bool wrong_length = true;
    for (int l = 0; l < 3; ++l) {
        if (str[0] == 0) break;
        if (str[l] == 0) {
            wrong_length = false;
            break;
        }
    }
    if (wrong_length) throw File_except(str, File_except::size_format);
    int k = 0;
    while (str[k] != 0) {
        if (str[k] < '0' || str[k] > '9') throw File_except(str, File_except::size_format);
        k++;
    }
    int field_x = atoi(str);
    for (int m = 0; m < 10; ++m) {
        str[m] = 1;
    }
    in.getline(str, 3);
    wrong_length = true;
    for (int l = 0; l < 3; ++l) {
        if (str[0] == 0) break;
        if (str[l] == 0) {
            wrong_length = false;
            break;
        }
    }
    if (wrong_length) throw File_except(str, File_except::size_format);
    k = 0;
    while (str[k] != 0) {
        if (str[k] < '0' || str[k] > '9') throw File_except(str, File_except::size_format);
        k++;
    }
    int field_y = atoi(str);
    game->field->clear();
    game->field->resize(field_x, field_y);
    for (int j = 0; j < game->field->get_y(); ++j) {
        for (int i = 0; i < game->field->get_x(); ++i) {
            in.get(c);
            if (in.eof()) throw File_except(str, File_except::field_format, true, i, j);
            if (c != '0' && c != '1') throw File_except(str, File_except::field_format, true, i, j);
            if (c == '1') game->field->set_cell(i, j);
        }
        in.get(c);
    }
    game->steps = 0;
    game->backed = false;
}

void Game::Executor::autoplay(std::string &in) {
    int cnt = 0;
    while (in[cnt] != ' ' && cnt < in.length()) cnt++;
    in.resize(cnt);
    for (int i = 0; i < cnt; ++i) {
        if (in[i] < '0' || in[i]> '9') throw Delay_except(in);
    }
    int delay = atoi(in.c_str());
    if (delay == 0) throw Delay_except(in);
    game->backed = false;

    while (true) {
        system("cls");
        if (kbhit()) {
            break;
        }
        if (*(game->backuped_field) == *(game->field)) throw Loop_except();
        *(game->backuped_field) = *(game->field);
        game->field->recalculate();
        game->steps++;
        cout << "Step: " << game->steps << endl;
        game->field->print();
        cout << "Press any key to stop autoplay" << endl;
        DWORD start = GetTickCount();
        DWORD end = start;
        DWORD time = (end - start);
        while (time < delay) {
            end = GetTickCount();
            time = (end - start);
        }
    }
}

void Game::Executor::help() {
    system("cls");
    cout << endl;
    cout << "   Following comands avaliable:" << endl << endl;
    cout << "      exit - quites from game" << endl << endl;
    cout << "      reset - clears the field" << endl << endl;
    cout << "      set [letter_x][number_y] - sets cell on chosen coordinates as alive" << endl << endl;
    cout << "      clear [letter_x][number_y] - sets cell on chosen coordinates as dead" << endl << endl;
    cout << "      step [number_steps] - plays \"number\" steps in game" << endl << endl;
    cout << "      back - goes to previous step. Avaliable once at time, you sholud do some steps to do it one more time!" << endl << endl;
    cout << "      store [filename] - saves actual field state to chosen file in the specific format" << endl << endl;
    cout << "      load [filename] - loads field state from the file in the specific format" << endl << endl;
    cout << "      autoplay [number_delay] - plays automatically with the \"number\" delay in ms" << endl << endl;
    cout << "      resize [number_x] [number_y] - resizes the field to written size" << endl << endl;
    cout << "      help - shows this help =)" << endl << endl << endl << endl;
    system("pause");
}