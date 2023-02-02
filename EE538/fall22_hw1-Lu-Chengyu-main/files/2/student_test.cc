#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write some test cases for each function.
//-----------------------------------------------------------------------------
TEST(IsPrime ,test1){
    int input = 0;
    bool actual1 = IsPrime(input);
    bool output = false;
    EXPECT_EQ(output, actual1);
}

TEST(IsPrime ,test2){
    int input = 2;
    bool actual2 = IsPrime(input);
    bool output = true;
    EXPECT_EQ(output, actual2);
}

TEST(Reverse ,test3){
    int input = 3;
    bool actual3 = IsPrime(input);
    bool output = true;
    EXPECT_EQ(output, actual3);
}

TEST(Reverse ,test4){
    int input = 100;
    bool actual4 = IsPrime(input);
    bool output = false;
    EXPECT_EQ(output, actual4);
}