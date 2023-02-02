#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------
TEST(UniqueVectorNotBySet ,test1){
    std::vector<int> input = {1, 2, 2, 4};
    UniqueVectorNotBySet(input);
    std::vector<int> output = {1, 2, 4};
    EXPECT_EQ(output, input);
}

TEST(UniqueVectorNotBySet ,test2){
    std::vector<int> input = {};
    UniqueVectorNotBySet(input);
    std::vector<int> output = {};
    EXPECT_EQ(output, input);
}

TEST(UniqueVectorBySet ,test3){
    std::vector<int> input = {1, 2, 2, 4};
    UniqueVectorBySet(input);
    std::vector<int> output = {1, 2, 4};
    EXPECT_EQ(output, input);
}

TEST(UniqueVectorBySet ,test4){
    std::vector<int> input = {};
    UniqueVectorBySet(input);
    std::vector<int> output = {};
    EXPECT_EQ(output, input);
}

TEST(IntersectVectors ,test5){
    std::vector<int> input1 = {1, 2, 2, 4};
    std::vector<int> input2 = {1, 2, 3, 4, 5, 6};
    std::vector<int> actual = IntersectVectors(input1, input2);
    std::vector<int> output = {1, 2, 4};
    EXPECT_EQ(output, actual);
}

TEST(IntersectVectors ,test6){
    std::vector<int> input1 = {1, 2, 2, 4};
    std::vector<int> input2 = {5, 6, 7, 8};
    std::vector<int> actual = IntersectVectors(input1, input2);
    std::vector<int> output = {};
    EXPECT_EQ(output, actual);
}