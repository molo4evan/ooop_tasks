//
// Created by User on 003 03.12.17.
//

#include "Command.h"
using namespace std;

Game::Executor::Executor(const std::string &c, const std::string &t, Game* g) {
    cmd = c;
    tail = t;
    game = g;
}

void Game::Executor::init_list(){
    cmd_list = {
            {"exit", Exit()},
            {"set", Set()},
            {"clear", Clear()},
            {"step", Step()},
            {"back", Back()},
            {"store", Store()},
            {"load", Load()},
            {"autoplay", Autoplay()},
            {"resize", Resize()},
            {"help", Help()}
    };
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

    auto smth = cmd_list.find(cmd);
    if (smth == cmd_list.end()) throw Cmd_except(cmd);
    else {
        Command command = cmd_list[cmd];
        command.exec(tail, game);
    }

}
