#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Game.h"

namespace{
    class Fiest: public testing::Test{
    public:
        Field f;
        Fiest(){
            f = Field();
        }
    };

    class Cest:public testing::Test{
    public:
        Cell c;
        Cest(){
            c = Cell();
        }
    };
}

TEST_F(Cest, set_get){
    ASSERT_EQ(c.get_cell(), false);
    c.set_cell(true);
    ASSERT_EQ(c.get_cell(), true);
    c.set_cell(false);
    ASSERT_EQ(c.get_cell(), false);
}

TEST_F(Cest, calc){
    bool arr[8];
    for (int i = 0; i < 8; ++i) arr[i] = false;

    c.set_cell(true);
    c.set_neighbours(arr);
    c.calc_state();
    ASSERT_EQ(c.get_cell(), false);

    for (int j = 0; j < 4; ++j) arr[j] = true;
    c.set_cell(true);
    c.set_neighbours(arr);
    c.calc_state();
    ASSERT_EQ(c.get_cell(), false);

    arr[3] = false;
    c.set_cell(true);
    c.set_neighbours(arr);
    c.calc_state();
    ASSERT_EQ(c.get_cell(), true);

    c.set_cell(false);
    c.set_neighbours(arr);
    c.calc_state();
    ASSERT_EQ(c.get_cell(), true);

    arr[5] = true;
    c.set_cell(false);
    c.set_neighbours(arr);
    c.calc_state();
    ASSERT_EQ(c.get_cell(), false);
}


TEST_F(Fiest, constructing){
    ASSERT_EQ(f.get_x(), 10);
    ASSERT_EQ(f.get_y(), 10);
    Field f1 = Field(5);
    ASSERT_EQ(f1.get_x(), 5);
    ASSERT_EQ(f1.get_y(), 5);
    Field f2 = Field(12, 15);
    ASSERT_EQ(f2.get_x(), 12);
    ASSERT_EQ(f2.get_y(), 15);
}

TEST_F(Fiest, mod_cells){
    f.set_cell(5, 7);
    ASSERT_EQ(f.get_cell(5, 7), true);
    f.clear_cell(5, 7);
    ASSERT_EQ(f.get_cell(5, 7), false);
    for (int i = 0; i < f.get_x(); ++i) {
        for (int j = 0; j < f.get_y(); ++j) {
            f.set_cell(i, j);
        }
    }
    f.clear();
    for (int i = 0; i < f.get_x(); ++i) {
        for (int j = 0; j < f.get_y(); ++j) {
            ASSERT_EQ(f.get_cell(i, j), false);
        }
    }
}

TEST_F(Fiest, recalc){
    f.set_cell(5, 8);
    f.set_cell(5, 9);
    f.set_cell(5, 0);
    f.recalculate();
    ASSERT_EQ(f.get_cell(4, 9), true);

    f.clear();
    f.set_cell(5, 0);
    f.set_cell(6, 0);
    f.set_cell(7, 0);
    f.recalculate();
    ASSERT_EQ(f.get_cell(6, 9), true);
}

TEST_F(Fiest, assignment){
    srand(time(NULL));
    int x, y;
    for (int i = 0; i < 30; ++i) {
        x = rand() % f.get_x();
        y = rand() % f.get_y();
        f.set_cell(x, y);
    }

    Field f1 = f;
    ASSERT_EQ(f1.get_x(), f.get_x());
    ASSERT_EQ(f1.get_y(), f.get_y());
    for (int i = 0; i < f.get_x(); ++i) {
        for (int j = 0; j < f.get_y(); ++j) {
            ASSERT_EQ(f1.get_cell(i, j), f.get_cell(i, j));
        }
    }

    Field f2 = Field(3, 5);
    f2 = f;
    ASSERT_EQ(f2.get_x(), f.get_x());
    ASSERT_EQ(f2.get_y(), f.get_y());
    for (int i = 0; i < f.get_x(); ++i) {
        for (int j = 0; j < f.get_y(); ++j) {
            ASSERT_EQ(f2.get_cell(i, j), f.get_cell(i, j));
        }
    }

    Field f3 = Field(15, 20);
    f3 = f;
    ASSERT_EQ(f3.get_x(), f.get_x());
    ASSERT_EQ(f3.get_y(), f.get_y());
    for (int i = 0; i < f.get_x(); ++i) {
        for (int j = 0; j < f.get_y(); ++j) {
            ASSERT_EQ(f3.get_cell(i, j), f.get_cell(i, j));
        }
    }
}

TEST_F(Fiest, resize){
    f.resize(13, 28);
    ASSERT_EQ(f.get_x(), 13);
    ASSERT_EQ(f.get_y(), 28);

    f.resize(3, 8);
    ASSERT_EQ(f.get_x(), 3);
    ASSERT_EQ(f.get_y(), 8);
}

TEST_F(Fiest, compare){
    Field f1 = f;
    ASSERT_EQ(f == f1, true);
    f1.resize(f.get_x(), f.get_y() + 1);
    ASSERT_EQ(f == f1, false);
    f1 = f;
    f1.resize(f.get_x() + 1, f.get_y());
    ASSERT_EQ(f == f1, false);
    f1 = f;
    f1.set_cell(0, 0);
    ASSERT_EQ(f == f1, false);
    f1.clear();
    ASSERT_EQ(f == f1, true);
}