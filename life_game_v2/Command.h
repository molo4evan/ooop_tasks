//
// Created by User on 009 09.12.17.
//

#ifndef LIFE_GAME_COMMAND_H
#define LIFE_GAME_COMMAND_H
#include "Game.h"



class Exit: public Game::Executor::Command{
public:
    Exit(): Command(){}
    virtual void exec( std::string&, Game*) ;
};

class Set: public Game::Executor::Command{
public:
    Set(): Command(){}
    virtual void exec( std::string&, Game*) ;
};

class Clear: public Game::Executor::Command{
public:
    Clear(): Command(){}
    virtual void exec( std::string&, Game*) ;
};

class Step: public Game::Executor::Command{
public:
    Step(): Command(){}
    virtual void exec( std::string&, Game*) ;
};

class Back: public Game::Executor::Command{
public:
    Back(): Command(){}
    virtual void exec( std::string&, Game*) ;
};

class Store: public Game::Executor::Command{
public:
    Store(): Command(){}
    virtual void exec( std::string&, Game*) ;
};

class Load: public Game::Executor::Command{
public:
    Load(): Command(){}
    virtual void exec( std::string&, Game*) ;
};

class Autoplay: public Game::Executor::Command{
public:
    Autoplay(): Command(){}
    virtual void exec( std::string&, Game*) ;
};

class Resize: public Game::Executor::Command{
public:
    Resize(): Command(){}
    virtual void exec( std::string&, Game*) ;
};

class Help: public Game::Executor::Command{
public:
    Help(): Command(){}
    virtual void exec( std::string&, Game*) ;
};
#endif //LIFE_GAME_COMMAND_H
