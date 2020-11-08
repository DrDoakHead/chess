#include "../chessProgram/Position.h"
#include "gtest/gtest.h"

class TestPosition public testing

TEST_F(Position, constructors) 
{
    Position pos1;
    EXPECT_NO_THROW(Position pos2(2, 5));
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}