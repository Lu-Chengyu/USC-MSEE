#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write several test cases for each function.
// Make sure you cover all corner cases!
//-----------------------------------------------------------------------------
TEST(IndexOfFirstSpace ,test1){
    std::string input1 = "This is a test";
    int actual = IndexOfFirstSpace(input1);
    int output = 4;
    EXPECT_EQ(output, actual);
}

TEST(IndexOfFirstSpace ,test2){
    std::string input1 = "Thisisatest";
    int actual = IndexOfFirstSpace(input1);
    int output = -1;
    EXPECT_EQ(output, actual);
}

TEST(IndexOfFirstSpace ,test3){
    std::string input1 = "";
    int actual = IndexOfFirstSpace(input1);
    int output = -1;
    EXPECT_EQ(output, actual);
}

TEST(SeparateFirstAndLastNames ,test1){
    std::string input1 = "This is a test";
    std::string input2 = "This is a test";
    std::string input3 = "This is a test";
    SeparateFirstAndLastNames(input1, input2, input3);
    std::string output1 = "This";
    std::string output2 = "is a test";
    EXPECT_EQ(output1, input2);
    EXPECT_EQ(output2, input3);
}

TEST(SeparateFirstAndLastNames ,test2){
    std::string input1 = "";
    std::string input2 = "";
    std::string input3 = "";
    SeparateFirstAndLastNames(input1, input2, input3);
    std::string output1 = "";
    std::string output2 = "";
    EXPECT_EQ(output1, input2);
    EXPECT_EQ(output2, input3);
}

TEST(SeparateFirstAndLastNames ,test3){
    std::string input1 = "Thisisatest";
    std::string input2 = "This is a test";
    std::string input3 = "This is a test";
    SeparateFirstAndLastNames(input1, input2, input3);
    std::string output1 = "Thisisatest";
    std::string output2 = "This is a test";
    EXPECT_EQ(output1, input2);
    EXPECT_EQ(output2, input3);
}

TEST(NumberOfVowels ,test1){
    std::string input1 = "This is A test";
    int actual = NumberOfVowels(input1);
    int output = 4;
    EXPECT_EQ(output, actual);
}

TEST(NumberOfVowels ,test2){
    std::string input1 = "Thsstst";
    int actual = NumberOfVowels(input1);
    int output = 0;
    EXPECT_EQ(output, actual);
}

TEST(NumberOfVowels ,test3){
    std::string input1 = "";
    int actual = NumberOfVowels(input1);
    int output =0;
    EXPECT_EQ(output, actual);
}

TEST(NumberOfConsonants ,test1){
    std::string input1 = "This is A test";
    int actual = NumberOfConsonants(input1);
    int output = 7;
    EXPECT_EQ(output, actual);
}

TEST(NumberOfConsonants ,test2){
    std::string input1 = "Thsstst";
    int actual = NumberOfConsonants(input1);
    int output = 7;
    EXPECT_EQ(output, actual);
}

TEST(NumberOfConsonants ,test3){
    std::string input1 = "";
    int actual = NumberOfConsonants(input1);
    int output =0;
    EXPECT_EQ(output, actual);
}

TEST(Reverse ,test1){
    std::string input1 = "This is A test";
    int actual = Reverse(input1);
    std::string output = "tset A si sihT";
    EXPECT_EQ(output, input1);
}

TEST(Reverse ,test2){
    std::string input1 = "Thsstst";
    int actual = Reverse(input1);
    std::string output = "tstsshT";
    EXPECT_EQ(output, input1);
}

TEST(Reverse ,test3){
    std::string input1 = "";
    int actual = Reverse(input1);
    std::string output = "";
    EXPECT_EQ(output, input1);
}