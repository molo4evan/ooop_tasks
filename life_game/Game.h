//
// Created by User on 014 14.11.17.
//

#ifndef LIFE_GAME_GAME_H
#define LIFE_GAME_GAME_H

#include "Field.h"
#include "game_except/main_except.h"
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <windows.h>
#include <conio.h>


class Game {
private:
    Field* field;
    Field* backuped_field;
    bool backed;
    unsigned long steps;

    void init();
    void say_hello();
    void say_bye();
    void show_field();
    void parse_cmd(std::string&, std::string&);
    void handle_cmd(std::string&);

    class Executor {
    private:
        std::string cmd;
        std::string tail;
        Game* game;

        void get_coords(std::string&, int*, int*);
        void get_size(std::string&, int*, int*);
        void step(std::string&);
        void load(std::string&);
        void store(std::string&);
        void autoplay(std::string&);
        void help();
    public:
        Executor() = delete;
        explicit Executor(const std::string&, Game*);
        Executor(const std::string&, const std::string&, Game*);
        void exec_cmd();
    };
public:
    Game();
    ~Game();
    void play();
};


#endif //LIFE_GAME_GAME_H
