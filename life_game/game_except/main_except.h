//
// Created by User on 026 26.11.17.
//

#ifndef LIFE_GAME_MAIN_EXCEPT_H
#define LIFE_GAME_MAIN_EXCEPT_H

#include <string>
#include <iostream>

class Main_except {
protected:
    std::string err_arg;
public:
    Main_except();
    explicit Main_except(const std::string&);
    virtual ~Main_except() = default;
    virtual void print_msg();
};

class Cmd_except: public Main_except{
public:
    Cmd_except(): Main_except(){}
    explicit Cmd_except(const std::string &msg): Main_except(msg){}
    void print_msg();
};

class Args_except: public Main_except{
public:
    Args_except(): Main_except(){}
    explicit Args_except(const std::string &msg): Main_except(msg){}
    void print_msg();
};

class File_except: public Main_except{
public:
    bool load;
    enum Case{none, name, size_format, field_format};
    File_except();
    explicit File_except(const std::string&);
    File_except(const std::string&, Case, bool isl = false, int x = 0, int y = 0);
    void print_msg();
private:
    Case state;
    int x;
    int y;
};

class Delay_except: public Main_except{
public:
    Delay_except(): Main_except(){}
    explicit Delay_except(const std::string &msg): Main_except(msg){}
    void print_msg();
};

class Back_except: public Main_except{
public:
    Back_except(): Main_except(){}
    void print_msg();
};

class Loop_except: public Main_except{
public:
    Loop_except(): Main_except(){}
    void print_msg();
};

class Exit_except{
public:
    Exit_except() = default;
};

#endif //LIFE_GAME_MAIN_EXCEPT_H
