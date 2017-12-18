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
#include <unordered_map>

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
public:
    class Executor {
    public:
        Executor() = delete;
        Executor(const std::string&, const std::string&, Game*);
        void exec_cmd();
        static void init_list();

        class Command {
        protected:
            std::string tail;
            Game* game;
            int arg1, arg2;

            void init(std::string&, Game*);
            void get_coords();
            void get_size();
        public:
            Command() = default;
            virtual ~Command() = default;
            virtual void exec(std::string&, Game*){int i = 10;};
        };
    private:
        std::string cmd;
        std::string tail;
        Game* game;
    };

    Game();
    ~Game();
    void play();
    Field* get_field();
    void set_field(Field*);
    Field* get_backuped_field();
    void set_backuped_field(Field*);
    unsigned int get_steps();
    void inc_steps();
    void dec_steps();
    void reset_steps();
    bool get_backed();
    void set_backed(bool);
};

static std::unordered_map<std::string, Game::Executor::Command> cmd_list;


#endif //LIFE_GAME_GAME_H
