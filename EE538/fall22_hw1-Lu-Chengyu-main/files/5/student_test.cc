#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write some test cases for each function.
//-----------------------------------------------------------------------------
TEST(ClimbStairs ,test1){
    int input = -9;
    int actual1 = ClimbStairs(input);
    int output = -1;
    EXPECT_EQ(output, actual1);
}

TEST(CountNumberOfSpaces ,test2){
    int input = 0;
    int actual2 = ClimbStairs(input);
    int output = 0;
    EXPECT_EQ(output, actual2);
}

TEST(Reverse ,test3){
    int input = 3;
    int actual3 = ClimbStairs(input);
    int output = 4;
    EXPECT_EQ(output, actual3);
}

TEST(CountNumberOfSpaces ,test4){
    int input = 20;
    int actual4 = ClimbStairs(input);
    int output = 121415;
    EXPECT_EQ(output, actual4);
}