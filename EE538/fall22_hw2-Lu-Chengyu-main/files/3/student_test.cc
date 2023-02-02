#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------
TEST(Calculate ,test1){
    int input1 = 2;
    int input2 = 3;
    Operation input3 = Operation::kAdd;
    float actual = Calculate(input1, input2, input3);
    float output = 5.0;
    EXPECT_EQ(output, actual);
}

TEST(Calculate ,test2){
    int input1 = 2;
    int input2 = 3;
    Operation input3 = Operation::kSubtract;
    float actual = Calculate(input1, input2, input3);
    float output = -1.0;
    EXPECT_EQ(output, actual);
}

TEST(Calculate ,test3){
    int input1 = 3;
    int input2 = 2;
    Operation input3 = Operation::kDivision;
    float actual = Calculate(input1, input2, input3);
    float output = 1.5;
    EXPECT_EQ(output, actual);
}

TEST(Calculate ,test4){
    int input1 = 2;
    int input2 = 3;
    Operation input3 = Operation::kMultiplication;
    float actual = Calculate(input1, input2, input3);
    float output = 6.0;
    EXPECT_EQ(output, actual);
}

TEST(Calculate ,test5){
    int input1 = 2;
    int input2 = 3;
    Operation input3 = Operation::kBitwise_AND;
    float actual = Calculate(input1, input2, input3);
    float output = 2.0;
    EXPECT_EQ(output, actual);
}

TEST(Calculate ,test6){
    int input1 = 2;
    int input2 = 3;
    Operation input3 = Operation::kBitwise_OR;
    float actual = Calculate(input1, input2, input3);
    float output = 3.0;
    EXPECT_EQ(output, actual);
}

TEST(Calculate ,test7){
    int input1 = 2;
    int input2 = 3;
    Operation input3 = Operation::kBitwise_XOR;
    float actual = Calculate(input1, input2, input3);
    float output = 1.0;
    EXPECT_EQ(output, actual);
}

TEST(Calculate ,test8){
    int input1 = 2;
    int input2 = 3;
    Operation input3 = Operation::kShift_right;
    float actual = Calculate(input1, input2, input3);
    float output = 0.0;
    EXPECT_EQ(output, actual);
}

TEST(Calculate ,test9){
    int input1 = 2;
    int input2 = 3;
    Operation input3 = Operation::kShift_left;
    float actual = Calculate(input1, input2, input3);
    float output = 16.0;
    EXPECT_EQ(output, actual);
}