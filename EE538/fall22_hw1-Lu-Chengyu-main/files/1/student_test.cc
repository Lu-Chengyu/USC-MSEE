#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write some test cases for each function.
//-----------------------------------------------------------------------------
TEST(Reverse ,test1){
    std::vector<int> input = {};
    std::vector<int> actual1 = Reverse(input);
    std::vector<int> output = {};
    EXPECT_EQ(output, actual1);
}

TEST(Reverse ,test2){
    std::vector<int> input = {1, 2, 3};
    std::vector<int> actual2 = Reverse(input);
    std::vector<int> output = {3, 2, 1};
    EXPECT_EQ(output, actual2);
}

TEST(Reverse ,test3){
    std::vector<int> input = {0};
    std::vector<int> actual3 = Reverse(input);
    std::vector<int> output = {0};
    EXPECT_EQ(output, actual3);
}

TEST(PlusOne ,test1){
    std::vector<int> input = {0};
    std::vector<int> actual1 = PlusOne(input);
    std::vector<int> output = {1};
    EXPECT_EQ(output, actual1);
}

TEST(PlusOne ,test2){
    std::vector<int> input = {1, 2, 3};
    std::vector<int> actual2 = PlusOne(input);
    std::vector<int> output = {1, 2, 4};
    EXPECT_EQ(output, actual2);
}

TEST(PlusOne ,test3){
    std::vector<int> input = {0};
    std::vector<int> actual3 = PlusOne(input);
    std::vector<int> output = {1};
    EXPECT_EQ(output, actual3);
}

TEST(PlusOne ,test4){
    std::vector<int> input = {11, 2, 3};
    std::vector<int> actual4 = PlusOne(input);
    std::vector<int> output = {-1};
    EXPECT_EQ(output, actual4);
}

TEST(PlusOne ,test5){
    std::vector<int> input = {9, 9, 9};
    std::vector<int> actual5 = PlusOne(input);
    std::vector<int> output = {1, 0, 0, 0};
    EXPECT_EQ(output, actual5);
}

TEST(PlusOne ,test6){
    std::vector<int> input = {1, 9, 9};
    std::vector<int> actual6 = PlusOne(input);
    std::vector<int> output = { 2, 0, 0};
    EXPECT_EQ(output, actual6);
}

TEST(PlusOne ,test7){
    std::vector<int> input = {};
    std::vector<int> actual7 = PlusOne(input);
    std::vector<int> output = {};
    EXPECT_EQ(output, actual7);
}