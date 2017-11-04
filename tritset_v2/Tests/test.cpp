//
// Created by User on 030 30.10.17.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Tritset.h"

using testing::Eq;

namespace{
    class ClassDeclaration: public testing::Test{
    public:
        Tritset set;
        Tritset set1;
        size_t allocLength;
        ClassDeclaration(){
            set = Tritset(1000);
            set1 = Tritset(2000);
            allocLength = set.capacity();
        }
    };
}

TEST_F(ClassDeclaration, reserving){
    ASSERT_GE(allocLength, 1000*2/8/ sizeof(uint));
}

TEST_F(ClassDeclaration, noAlocation){
    set[1000000000] = Unknown;
    ASSERT_EQ(allocLength, set.capacity());

}

TEST_F(ClassDeclaration, FalseNoAlloc){
    ASSERT_EQ(set[2000000000]==True, false);
    ASSERT_EQ(allocLength, set.capacity());
}

TEST_F(ClassDeclaration, Allocation){
    set[1000000000] = True;
    ASSERT_LT(allocLength, set.capacity());
}

TEST_F(ClassDeclaration, noMemOps){
    set[1000000000] = True;
    allocLength = set.capacity();
    set[1000000000] = Unknown;
    set[1000000] = False;
    ASSERT_EQ(allocLength, set.capacity());
}

TEST_F(ClassDeclaration, shrink){
    set[1000000000] = True;
    allocLength = set.capacity();
    set[1000000000] = Unknown;
    set.shrink();
    ASSERT_GT(allocLength, set.capacity());
}

TEST_F(ClassDeclaration, ops){
    set[999] = True;
    set1[1999] = False;
    Tritset set2 = set & set1;
    ASSERT_EQ(set2.capacity(), set1.capacity());
    Tritset set3 = set | set1;
    ASSERT_EQ(set3.capacity(), set1.capacity());
    Tritset set4 = ~set1;
    ASSERT_EQ(set4.capacity(), set1.capacity());
}

TEST_F(ClassDeclaration, trim){
    set1[1999] = True;
    allocLength = set1.capacity();
    set1.trim(50);
    ASSERT_LT(set1.capacity(), allocLength);
}

TEST_F(ClassDeclaration, lenth){
    set[999] = True;
    ASSERT_EQ(set.length(), 1000);
}

TEST_F(ClassDeclaration, card_1){
    set[0] = True;
    set[1] = True;
    set[2] = True;
    set[3] = True;
    set[4] = True;
    set[5] = False;
    set[6] = False;
    set[7] = False;
    set[8] = False;
    set[9] = False;
    set[10] = False;
    set[999] = True;
    ASSERT_EQ(set.cardinality(True), 6);
    ASSERT_EQ(set.cardinality(False), 6);
    ASSERT_EQ(set.cardinality(Unknown), set.length() - 12);
}

TEST_F(ClassDeclaration, card_all){
    set[0] = True;
    set[1] = True;
    set[2] = True;
    set[3] = True;
    set[4] = True;
    set[5] = False;
    set[6] = False;
    set[7] = False;
    set[8] = False;
    set[9] = False;
    set[10] = False;
    set[999] = True;
    std::unordered_map<uint, uint> map = set.cardinality();
    ASSERT_EQ(map[True], 6);
    ASSERT_EQ(map[False], 6);
    ASSERT_EQ(map[Unknown], set.length() - 12);
}

TEST_F(ClassDeclaration, iter){
    set[0] = True;
    set[1] = True;
    set[2] = True;
    set[3] = True;
    set[4] = True;
    set[5] = False;
    set[6] = False;
    set[7] = False;
    set[8] = False;
    set[9] = False;
    set[10] = False;
    set[999] = True;
    int i = 0;
    for (Tritset::iterator a = set.begin();  a != set.end(); ++a) {
        ASSERT_EQ(*a, set[i]);
        ++i;
    }
}