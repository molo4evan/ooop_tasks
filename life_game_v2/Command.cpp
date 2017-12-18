//
// Created by User on 009 09.12.17.
//

#include "Game.h"
#include "Command.h"
#include "game_except/main_except.h"

using namespace std;

void Game::Executor::Command::get_coords() {
    string buf;
    int cnt;

    string exc_str(tail);
    exc_str.resize(1);
    if (tail.length() < 2) throw Args_except();
    if (tail[0] < 'A' || (tail[0] > 'Z' && tail[0] < 'a') || tail[0] > 'z') throw Args_except(exc_str);

    if (tail[0] >= 'a') arg1 = tail[0] - 'a' + 26;
    else arg1 = tail[0] - 'A';
    if (arg1 > game->get_field()->get_x()) throw Args_except(exc_str);
    cnt = 1;
    while (tail[cnt] != ' ') {
        buf.push_back(tail[cnt]);
        cnt++;
    }
    for (char i : buf) {
        if (i < '0' || i > '9') throw Args_except(buf);
    }
    arg2 = atoi(buf.c_str());
    if (arg2 > game->get_field()->get_y()) throw Args_except(buf);
}

void Game::Executor::Command::get_size() {
    string buf;
    int cnt = 0;
    while (tail[cnt] != ' ') {
        buf.push_back(tail[cnt]);
        cnt++;
    }
    if (!buf.length()) throw Args_except();
    for (char i : buf) {
        if (i < '0' || i > '9') throw Args_except(buf);
    }
    arg1 = atoi(buf.c_str());
    if (arg1 > 58) throw Args_except(buf);

    cnt++;
    buf = "";
    while (tail[cnt] != ' ') {
        buf.push_back(tail[cnt]);
        cnt++;
    }
    if (!buf.length()) throw Args_except();
    for (char i : buf) {
        if (i < '0' || i > '9') throw Args_except(buf);
    }
    arg2 = atoi(buf.c_str());
    if (arg2 > 999) throw Args_except(buf);
}

void Game::Executor::Command::init(string& t, Game* g){
    game = g;
    tail = t;
}

void Exit::exec( string& t, Game* g)  {
    throw Exit_except();
}

void Set::exec( string& t, Game* g)  {
    init(t, g);
    get_coords();
    g->get_field()->set_cell(arg1, arg2);
}

void Clear::exec( string& t, Game* g)  {
    init(t, g);
    get_coords();
    game->get_field()->clear_cell(arg1, arg2);
}

void Step::exec( string& t, Game* g)  {
    init(t, g);
    string buf;
    int cnt = 0, steps = 0;
    while (tail[cnt] != ' ') {
        buf.push_back(tail[cnt]);
        cnt++;
    }
    for (char i : buf) {
        if (i < '0' || i > '9') throw Args_except(buf);
    }
    steps = atoi(buf.c_str());
    for (int i = 0; i < steps; ++i) {
        *(game->get_backuped_field()) = *(game->get_field());
        game->get_field()->recalculate();
        game->inc_steps();
    }
    game->set_backed(false);
}

void Back::exec( string& t, Game* g)  {
    init(t, g);
    if (game->get_backed()) throw Back_except();
    Field* tmp = game->get_field();
    game->set_field(game->get_backuped_field());
    game->set_backuped_field(tmp);
    game->set_backed(true);
    game->dec_steps();
}

void Store::exec( string& t, Game* g)  {
    init(t, g);
    int cnt = 0;
    while (tail[cnt] != ' ' && cnt < tail.length()) cnt++;
    tail.resize(cnt);
    ofstream out(tail);
    out << game->get_field()->get_x() << endl;
    out << game->get_field()->get_y() << endl;
    for (int i = 0; i < game->get_field()->get_y(); ++i) {
        for (int j = 0; j < game->get_field()->get_x(); ++j) {
            out << game->get_field()->get_cell(j, i);
        }
        out << endl;
    }
}

void Load::exec( string& t, Game* g)  {
    init(t, g);
    int cnt = 0, x = 0, y = 0;
    while (tail[cnt] != ' ' && cnt < tail.length()) cnt++;
    tail.resize(cnt);
    ifstream in(tail);
    if (in.fail()) throw File_except(tail, File_except::name);
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
    game->get_field()->clear();
    game->get_field()->resize(field_x, field_y);
    for (int j = 0; j < game->get_field()->get_y(); ++j) {
        for (int i = 0; i < game->get_field()->get_x(); ++i) {
            in.get(c);
            if (in.eof()) throw File_except(str, File_except::field_format, true, i, j);
            if (c != '0' && c != '1') throw File_except(str, File_except::field_format, true, i, j);
            if (c == '1') game->get_field()->set_cell(i, j);
        }
        in.get(c);
    }
    game->reset_steps();
    game->set_backed(false);
}

void Autoplay::exec( string& t, Game* g)  {
    init(t, g);
    int cnt = 0;
    while (tail[cnt] != ' ' && cnt < tail.length()) cnt++;
    tail.resize(cnt);
    for (int i = 0; i < cnt; ++i) {
        if (tail[i] < '0' || tail[i]> '9') throw Delay_except(tail);
    }
    int delay = atoi(tail.c_str());
    if (delay == 0) throw Delay_except(tail);
    game->set_backed(false);

    while (true) {
        system("cls");
        if (kbhit()) {
            break;
        }
        if (*(game->get_backuped_field()) == *(game->get_field())) throw Loop_except();
        *(game->get_backuped_field()) = *(game->get_field());
        game->get_field()->recalculate();
        game->inc_steps();
        cout << "Step: " << game->get_steps() << endl;
        game->get_field()->print();
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

void Resize::exec( string& t, Game* g)  {
    init(t, g);
    get_size();
    game->get_field()->resize(arg1, arg2);
}

void Help::exec( string& t, Game* g)  {
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
    cout << "      load [filename] - loads field state from the file in the specific format. Write only the filename." << endl << endl;
    cout << "      list - shows the avaliable patterns from the \"Patterns\" folder" << endl << endl;
    cout << "      autoplay [number_delay] - plays automatically with the \"number\" delay in ms" << endl << endl;
    cout << "      resize [number_x] [number_y] - resizes the field to written size" << endl << endl;
    cout << "      help - shows this help =)" << endl << endl << endl << endl;
    system("pause");
}