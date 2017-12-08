//
// Created by User on 014 14.11.17.
//
#include "Game.h"

using namespace std;

Game::Game() {
    backed = false;
    steps = 0;
}

Game::~Game() {
    delete field;
}

void Game::init() {
    this->backuped_field = new Field;
    int x = 0, y = 0, i = 0;
    string s, buf;
    Field* field;
    system("cls");
    while (true) {
        i = 0;
        buf.clear();
        cout << "Input field size (format \"size\" or \"x y\"(x <= 58, y <= 999)), or skip: ";
        getline(cin, s);

        bool empty = true;
        for (char c : s) {
            if (c != ' ' && c != '\t') {
                empty = false;
                break;
            }
        }
        if (empty) {
            field = new Field;
            this->field = field;
            return;
        }

        s.push_back(' ');
        try {
            for (char j : s) {
                if (j != ' ') buf.push_back(j);
                else {
                    for (char k : buf) {
                        if (k < '0' || k > '9') {
                            throw string();
                        };
                    }
                    if (i == 0) {
                        x = atoi(buf.c_str());
                    }
                    else {
                        y = atoi(buf.c_str());
                        break;
                    }
                    buf.clear();
                    i++;
                }
            }
        }
        catch (string&) {
            system("cls");
            cout << endl << "             Incorrect size" << endl << endl;
            continue;
        }
        if (x > 52 || x < 1 || y > 999 || y < 1) {
            system("cls");
            cout << endl << "             Incorrect size" << endl << endl;
            continue;
        }

        if (i == 1) field = new Field(x);
        else field = new Field(x, y);
        break;
    }
    this->field = field;
}

void Game::say_hello() {
    system("cls");
    cout << endl << endl << endl << endl << endl;
    cout << "                           Hi there, let me present u my little \"Life\" Game." << endl;
    cout << "                               To see command list, type \"help\"." << endl;
    cout << "           U can also load some patterns from the folder \"Patterns\", unexpecting, huh?" << endl;
    cout << "                                           Have fun!" << endl;
    cout << endl << endl;
    system("pause");
}

void Game::say_bye() {
    system("cls");
    cout << endl << endl << endl << endl << endl;
    cout << "                                     Thank u 4 playing," << endl;
    cout << "                                        see ya later!" << endl;
    cout << endl << endl;
    system("pause");
}

void Game::show_field() {
    system("cls");
    cout << "Step: " << steps << endl;
    field->print();
}




void Game::parse_cmd(std::string &in, std::string &cmd) {
    int i = 0, k = 0;

    in.push_back(' ');
    while (in[i] == ' ' || in[i] == '\t') i++;


    for (i; in[i] != ' ' && i < in.length(); i++) cmd.push_back(in[i]);

    for (int j = i + 1; j < in.length(); ++j) {
        in[k] = in[j];
        k++;
    }
    in.resize(k);
}

void Game::handle_cmd(std::string &input) {
    string cmd;
    parse_cmd(input, cmd);
    Executor exec(cmd, input, this);
    exec.exec_cmd();
    show_field();
}

void Game::play() {
    init();
    say_hello();
    string instr, cmd;
    vector<int> args;
    show_field();
    while (true) {
        cout << "Enter your command: ";
        getline(cin, instr);
        try {
            handle_cmd(instr);
        }
        catch (Exit_except) {
            break;
        }
        catch (Cmd_except& cmd) {
            show_field();
            cmd.print_msg();
            continue;
        }
        catch (Args_except& arg) {
            show_field();
            arg.print_msg();
            continue;
        }
        catch (File_except& file) {
            if (file.load) field->clear();
            show_field();
            file.print_msg();
            continue;
        }
        catch (Delay_except& del) {
            show_field();
            del.print_msg();
            continue;
        }
        catch (Back_except& back) {
            show_field();
            back.print_msg();
            continue;
        }
        catch (Loop_except& loop){
            show_field();
            loop.print_msg();
            continue;
        }
        catch (Main_except& exc) {
            show_field();
            exc.print_msg();
            continue;
        }
    }
    say_bye();
}