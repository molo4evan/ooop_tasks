#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Game.h"

int main(int argc, char* argv[]) {
    Game g;
    g.play();
    //testing::InitGoogleTest(&argc, argv);
    return 0;//RUN_ALL_TESTS();
}