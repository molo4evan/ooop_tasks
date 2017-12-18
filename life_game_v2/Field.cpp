//
// Created by User on 014 14.11.17.
//

#include "Field.h"
Field::Field() {
    cells = new Cell*[10];
    for (int i = 0; i < 10; ++i) {
        cells[i] = new Cell[10];
        for (int j = 0; j < 10; ++j) {
            cells[i][j].set_cell(false);
        }
    }
    x = 10;
    y = 10;
}

Field::Field(const int size) {
    cells = new Cell*[size];
    for (int i = 0; i < size; ++i) {
        cells[i] = new Cell[size];
        for (int j = 0; j < size; ++j) {
            cells[i][j].set_cell(false);
        }
    }
    x = size;
    y = size;
}

Field::Field(const int x, const int y) {
    cells = new Cell*[y];
    for (int i = 0; i < y; ++i) {
        cells[i] = new Cell[x];
        for (int j = 0; j < x; ++j) {
            cells[i][j].set_cell(false);
        }
    }
    this->x = x;
    this->y = y;
}

Field::Field(const Field &other) {
    cells = new Cell*[other.get_y()];
    for (int i = 0; i < other.get_y(); ++i) {
        cells[i] = new Cell[other.get_x()];
        for (int j = 0; j < other.get_x(); ++j) {
            cells[i][j].set_cell(false);
        }
    }
    x = other.get_x();
    y = other.get_y();
}

Field::~Field() {
    for (int i = 0; i < y; i++) {
        delete[] cells[i];
    }
    delete[] cells;
}

void Field::get_neighbours(unsigned int i, unsigned int j, bool* arr) {
    int k = 0, a, b, l, m;
    if (i == 0 && j == 0) {
        for (int n = 0; n < 3; ++n) {
            for (int q = 0; q < 3; ++q) {
                if (n == 1 && q == 1) continue;
                arr[k] = cells[(x - 1 + n) % x][(y - 1 + q) % y].get_cell();
                k++;
            }
        }
        return;
    }

    for (l = static_cast<int>(i) - 1; l <= static_cast<int>(i) + 1; l++) {
        for (m = static_cast<int>(j) - 1; m <= static_cast<int>(j) + 1; m++) {
            if (l == i && m == j) continue;

            if (l < 0) a = l + y;
            else if (l >= y) a = l % y;
            else a = l;

            if (m < 0) b = m + x;
            else if (m >= x) b = m % x;
            else b = m;

            arr[k] = cells[a][b].get_cell();
            k++;
        }
    }
}

void Field::recalculate() {
    bool neigh[8];
    for (int k = 0; k < 8; ++k) {
        neigh[k] = false;
    }
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            this->get_neighbours(i, j, neigh);
            cells[i][j].set_neighbours(neigh);
        }
    }
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            cells[i][j].calc_state();
        }
    }
}

void Field::print() {
    using namespace std;
    cout << endl << "     *----";
    for (int i = 0; i < x; i++) cout << "---";
    cout << '*' << endl << "     " << "|   |";
    char let = 'A';
    for (int i = 0; i < x; i++) {
        if (let == '[') let = 'a';
        cout << ' ' << let << ' ';
        let++;
    }
    cout << '|' << endl << "     " << "|---+";
    for (int i = 0; i < x; i++) cout << "---";
    cout << '|' << endl << "     ";
    int num = 0;
    for (int i = 0; i < y; i++) {
        if (num < 10) cout << "| " << num << " |";
        else if (num < 100) cout << "| " << num << "|";
        else cout << "|" << num << "|";
        for (int j = 0; j < x; j++) {
            cout << ' ';
            cells[i][j].print();
            cout << ' ';
        }
        cout << '|' << endl << "     ";
        num++;
    }
    cout << "*----";
    for (int i = 0; i < x; i++) cout << "---";
    cout << '*' << endl << endl;
}

void Field::set_cell(unsigned int x, unsigned int y) {
    cells[y][x].set_cell(true);
}

bool Field::get_cell(unsigned int x, unsigned int y) const{
    return cells[y][x].get_cell();
}

void Field::clear_cell(unsigned int x, unsigned int y) {
    cells[y][x].set_cell(false);
}

void Field::clear() {
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            clear_cell(i, j);
        }
    }
}

unsigned int Field::get_x() const{
    return x;
}

unsigned int Field::get_y() const{
    return y;
}

void Field::resize(unsigned int x, unsigned int y) {
    for (int l = 0; l < this->y; ++l) {
        Cell* tmp = new Cell[x];
        if (x < this->x) {
            for (int i = 0; i < x; ++i) {
                tmp[i] = cells[l][i];
            }
        }
        else {
            for (int i = 0; i < this->x; ++i) {
                tmp[i] = cells[l][i];
            }
            for (int j = this->x; j < x; ++j) {
                tmp[j].set_cell(false);
            }
        }
        Cell* for_del = cells[l];
        cells[l] = tmp;
        delete[] for_del;
    }
    Cell** new_a = new Cell*[y];
    if (y <= this->y) {
        for (int i = 0; i < y; ++i) {
            new_a[i] = cells[i];
        }
    }
    else {
        for (int i = 0; i < this->y; ++i) {
            new_a[i] = cells[i];
        }
        for (int j = this->y; j < y; ++j) {
            new_a[j] = new Cell[x];
            for (int i = 0; i < x; ++i) {
                new_a[j][i].set_cell(false);
            }
        }
    }
    Cell** mfd = cells;
    cells = new_a;
    delete[] mfd;

    this->x = x;
    this->y = y;
}

Field& Field::operator=(const Field& other) {
    if (this == &other) return *this;
    this->resize(other.x, other.y);
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            this->cells[i][j] = other.cells[i][j];
        }
    }
    return *this;
}

bool Field::operator==(const Field &other) {
    if (this == &other) return true;
    if (x != other.x || y != other.y) return false;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            if (get_cell(i, j) != other.get_cell(i, j)) return false;
        }
    }
    return true;
}