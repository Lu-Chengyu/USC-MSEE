#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------
TEST(SwapByPointer ,test1){
    float x =10;
    float y=15;
    float* input1 = &x;
    float* input2 = &y;
    SwapByPointer(input1, input2);
    float actual1 =15;
    float actual2 =10;
    EXPECT_EQ(x, actual1);
    EXPECT_EQ(y, actual2);
}

TEST(SwapByPointer ,test2){
    float x =10;
    float y=10;
    float* input1 = &x;
    float* input2 = &y;
    SwapByPointer(input1, input2);
    float actual1 =10;
    float actual2 =10;
    EXPECT_EQ(x, actual1);
    EXPECT_EQ(y, actual2);
}

TEST(SwapByReference ,test3){
    float x =10;
    float y=15;
    SwapByReference(x, y);
    float actual1 =15;
    float actual2 =10;
    EXPECT_EQ(x, actual1);
    EXPECT_EQ(y, actual2);
}

TEST(SwapByReference ,test4){
    float x =10;
    float y=10;
    SwapByReference(x, y);
    float actual1 =10;
    float actual2 =10;
    EXPECT_EQ(x, actual1);
    EXPECT_EQ(y, actual2);
}