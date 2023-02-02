#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------
TEST(CountCharacters ,test1){
    std::string input1 = "This is a test";
    std::vector<char> input2 = {'t','h'};
    int actual = CountCharacters(input1, input2);
    int output = 4;
    EXPECT_EQ(output, actual);
}

TEST(CountCharacters ,test2){
    std::string input1 = "This is a test";
    std::vector<char> input2 = {};
    int actual = CountCharacters(input1, input2);
    int output = 0;
    EXPECT_EQ(output, actual);
}

TEST(CountCharacters ,test3){
    std::string input1 = "This is a test";
    std::vector<char> input2 = {'T','H'};
    int actual = CountCharacters(input1, input2);
    int output = 4;
    EXPECT_EQ(output, actual);
}