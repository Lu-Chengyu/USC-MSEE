#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------
TEST(MyVector ,test1){
    class MyVector vector;
    int size_ = 0;
    ErrorCode error_= ErrorCode::kNoError;
    EXPECT_EQ(vector.get_error(), error_);
    EXPECT_EQ(vector.size(), size_);
    vector.~MyVector();
}

TEST(MyVector ,test2){
    class MyVector vector(5);
    int size_ = 5;
    ErrorCode error_= ErrorCode::kNoError;
    EXPECT_EQ(vector.get_error(), error_);
    EXPECT_EQ(vector.size(), size_);
    vector.~MyVector();
}

TEST(MyVector ,test3){
    class MyVector vector;
    vector.insert(1,-1);
    vector.insert(2,0);
    vector.insert(3,1);
    vector.insert(4,2);
    vector.insert(5,3);
    class MyVector vector1(vector);
    int size_ = 5;
    EXPECT_EQ(vector.size(), size_);
    EXPECT_EQ(vector1.size(), size_);
    for(int i = 0; i<5; ++i){
        EXPECT_EQ(vector.at(i), vector1.at(i));
    }
    EXPECT_EQ(vector.find(3), 2);
    vector.push_back(6);
    EXPECT_EQ(vector.at(5), 6);
    EXPECT_EQ(vector.at(4), 5);
    EXPECT_EQ(vector.pop_back() , 6);
    vector.push_front(0);
    EXPECT_EQ(vector.at(0), 0);
    EXPECT_EQ(vector.at(1), 1);
    EXPECT_EQ(vector.pop_front() , 0);
    vector.~MyVector();
    vector1.~MyVector();
}