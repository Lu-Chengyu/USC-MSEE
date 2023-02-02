#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------
TEST(Concatenate ,test1){
    int input1[] = {1, 2};
    int input2 = 2;
    int input3[] = {2, 3, 4};
    int input4 = 3;
    int* actual = Concatenate(input1, input2, input3, input4);
    int output[] = {1, 2, 2, 3, 4};
    for(int i = 0; i<input2+input4;++i){
        EXPECT_EQ(output[i], actual[i]);
    }
    delete [] actual;
}

TEST(Concatenate ,test2){
    int input1[] = {};
    int input2 = 0;
    int input3[] = {2, 3, 4};
    int input4 = 3;
    int* actual = Concatenate(input1, input2, input3, input4);
    int output[] = {2, 3, 4};
    for(int i = 0; i<input2+input4;++i){
        EXPECT_EQ(output[i], actual[i]);
    }
    delete [] actual;
}

TEST(Concatenate ,test3){
    int input3[] = {};
    int input4 = 0;
    int input1[] = {2, 3, 4};
    int input2 = 3;
    int* actual = Concatenate(input1, input2, input3, input4);
    int output[] = {2, 3, 4};
    for(int i = 0; i<input2+input4;++i){
        EXPECT_EQ(output[i], actual[i]);
    }
    delete [] actual;
}

TEST(Concatenate ,test4){
    std::vector<int> input1 = {1, 2};
    std::vector<int> input2 = {2, 3, 4};
    std::vector<int> actual = Concatenate(input1, input2);
    std::vector<int> output = {1, 2, 2, 3, 4};
    EXPECT_EQ(output, actual);
}

TEST(Concatenate ,test5){
    std::vector<int> input1 = {};
    std::vector<int> input2 = {};
    std::vector<int> actual = Concatenate(input1, input2);
    std::vector<int> output = {};
    EXPECT_EQ(output, actual);
}