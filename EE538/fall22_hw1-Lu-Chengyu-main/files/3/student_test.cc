#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write some test cases for each function.
//-----------------------------------------------------------------------------
TEST(CountNumberOfSpaces ,test1){
    std::string input = "'000'";
    int actual1 = CountNumberOfSpaces(input);
    int output = 0;
    EXPECT_EQ(output, actual1);
}

TEST(CountNumberOfSpaces ,test2){
    std::string input = "   ";
    int actual2 = CountNumberOfSpaces(input);
    int output = 3;
    EXPECT_EQ(output, actual2);
}

TEST(Reverse ,test3){
    std::string input = "dfafa  hjosidjhoi  daag";
    int actual3 = CountNumberOfSpaces(input);
    int output = 4;
    EXPECT_EQ(output, actual3);
}

TEST(CountNumberOfSpaces ,test4){
    std::string input = " 10 02344232ezsfdaa tgr ";
    int actual4 = CountNumberOfSpaces(input);
    int output = 4;
    EXPECT_EQ(output, actual4);
}